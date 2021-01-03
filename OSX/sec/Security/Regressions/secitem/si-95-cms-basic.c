/*
 * Copyright (c) 2016 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#include "si-95-cms-basic.h"
#include "Security_regressions.h"

#include <AssertMacros.h>

#include <utilities/SecCFRelease.h>

#include <Security/SecBase.h>
#include <Security/SecImportExport.h>

#include <Security/SecIdentity.h>
#include <Security/SecPolicy.h>
#include <Security/SecItem.h>

#include <Security/SecCmsMessage.h>
#include <Security/SecCmsSignedData.h>
#include <Security/SecCmsContentInfo.h>
#include <Security/SecCmsSignerInfo.h>
#include <Security/SecCmsEncoder.h>
#include <Security/SecCmsDecoder.h>
#include <Security/SecCmsEnvelopedData.h>
#include <Security/SecCmsRecipientInfo.h>
#include <Security/SecAsn1Types.h>

#include <security_asn1/secerr.h>
#include <security_asn1/seccomon.h>

/* These tests are essentially the same as cms_01_basic in the OS X
 * libsecurity_cms_regressions. They are not unified into a single
 * test because libsecurity_smime diverges so much between the platforms
 * that unifying the tests makes every third line a TARGET macro.
 */

#define kNumberSetupTests 8
static CFDataRef setup_keychain(const uint8_t *p12, size_t p12_len, SecIdentityRef *identity, SecCertificateRef *cert) {
    CFDictionaryRef p12Options = NULL, item_dict = NULL, query_dict = NULL;
    CFArrayRef p12Items = NULL;
    CFStringRef p12Password = NULL;
    CFDataRef p12Data = NULL, identityPersistentRef = NULL;
    CFTypeRef keychainItems = NULL;

    /* load identity */
    ok(p12Password = CFStringCreateWithCString(NULL, "password", kCFStringEncodingASCII),
       "Create p12 password");
    require_action(p12Options = CFDictionaryCreate(NULL, (const void **)&kSecImportExportPassphrase,
                                       (const void **)&p12Password, 1,
                                       &kCFTypeDictionaryKeyCallBacks,
                                       &kCFTypeDictionaryValueCallBacks),
       errOut, fail("Create p12 options dictionary"));
    require_action(p12Data = CFDataCreate(NULL, p12, p12_len), errOut,
                   fail("Create p12 data"));
    ok_status(SecPKCS12Import(p12Data, p12Options, &p12Items),
              "import test identity");
    ok(item_dict = CFArrayGetValueAtIndex(p12Items, 0),
       "Get pkcs12 output");
    ok(*identity = (SecIdentityRef)CFRetainSafe(CFDictionaryGetValue(item_dict, kSecImportItemIdentity)),
       "Get identity from results");

    /* add identity to keychain because libsecurity_smime needs it there */
    const void *keys[] = { kSecValueRef, kSecReturnPersistentRef};
    const void *values[] = { *identity, kCFBooleanTrue };
    require_action(query_dict = CFDictionaryCreate(NULL, keys, values, 2,
                                                   &kCFTypeDictionaryKeyCallBacks,
                                                   &kCFTypeDictionaryValueCallBacks),
                   errOut, fail("Create SecItem query dictionary"));
    ok_status(SecItemAdd(query_dict, &keychainItems),
              "Add identity to keychain");
    is(CFGetTypeID(keychainItems), CFDataGetTypeID(),
       "Verify SecItem result type");
    ok(identityPersistentRef = (CFDataRef)CFRetainSafe(keychainItems),
       "Get persistent reference to identity");

    /* get the certificate */
    require_action(identity && *identity, errOut, fail("get identity failed"));
    ok_status(SecIdentityCopyCertificate(*identity, cert),
              "Copy certificate");

errOut:
    CFReleaseNull(p12Password);
    CFReleaseNull(p12Options);
    CFReleaseNull(p12Data);
    CFReleaseNull(p12Items);
    CFReleaseNull(query_dict);
    CFReleaseNull(keychainItems);
    return identityPersistentRef;
}

#define kNumberCleanupTests 1
static void cleanup_keychain(CFDataRef identityPersistenRef, SecIdentityRef identity, SecCertificateRef cert) {
    CFDictionaryRef query = NULL;
    require_action(query = CFDictionaryCreate(NULL, (const void**)&kSecValuePersistentRef,
                                              (const void**)&identityPersistenRef, 1,
                                              &kCFTypeDictionaryKeyCallBacks,
                                              &kCFTypeDictionaryValueCallBacks),
                   errOut, fail("Create SecItem dictionary"));
    ok_status(SecItemDelete(query),
              "Delete identity from keychain");

errOut:
    CFReleaseNull(query);
    CFReleaseNull(cert);
    CFReleaseNull(identity);
}

static OSStatus sign_please(SecIdentityRef identity, SECOidTag digestAlgTag, bool withAttrs, uint8_t *expected_output, size_t expected_len) {
    OSStatus status = SECFailure;
    SecCmsMessageRef cmsg = NULL;
    SecCmsSignedDataRef sigd = NULL;
    SecCmsContentInfoRef cinfo = NULL;
    SecCmsSignerInfoRef signerInfo = NULL;
    SecCmsEncoderRef encoder = NULL;
    CFMutableDataRef outCms = NULL;
    uint8_t string_to_sign[] = "This message is signed. Ain't it pretty?";

    /* setup the message */
    require_action_string(cmsg = SecCmsMessageCreate(), out,
                          status = errSecAllocate, "Failed to create message");
    require_action_string(sigd = SecCmsSignedDataCreate(cmsg), out,
                          status = errSecAllocate, "Failed to create signed data");
    require_action_string(cinfo = SecCmsMessageGetContentInfo(cmsg), out,
                          status = errSecParam, "Failed to get cms content info");
    require_noerr_string(status = SecCmsContentInfoSetContentSignedData(cinfo, sigd), out,
                         "Failed to set signed data into content info");
    require_action_string(cinfo = SecCmsSignedDataGetContentInfo(sigd), out,
                          status = errSecParam, "Failed to get content info from signed data");
    require_noerr_string(status = SecCmsContentInfoSetContentData(cinfo, NULL, false), out,
                         "Failed to set signed data content info");
    require_action_string(signerInfo = SecCmsSignerInfoCreate(sigd, identity, digestAlgTag), out,
                          status = errSecAllocate, "Failed to create signer info");
    require_noerr_string(status = SecCmsSignerInfoIncludeCerts(signerInfo, SecCmsCMCertOnly,
                                                               certUsageEmailSigner), out,
                         "Failed to put certs in signer info");

    if(withAttrs) {
        require_noerr_string(status = SecCmsSignerInfoAddSigningTime(signerInfo, 480000000.0), out,
                             "Couldn't add an attribute");
    }

    /* encode now */
    require_action_string(outCms = CFDataCreateMutable(NULL, 0), out,
                          status = errSecAllocate, "Failed to create cms data");
    require_noerr_string(status = SecCmsEncoderCreate(cmsg, NULL, NULL, outCms, NULL, NULL,
                                                      NULL, NULL, &encoder), out,
                         "Failed to create encoder");
    require_noerr_string(status = SecCmsEncoderUpdate(encoder, string_to_sign, sizeof(string_to_sign)), out,
                         "Failed to add data ");
    status = SecCmsEncoderFinish(encoder);
    encoder = NULL; // SecCmsEncoderFinish always frees the encoder but doesn't NULL it.
    require_noerr_quiet(status, out);

    /* verify the output matches expected results */
    if (expected_output) {
        require_action_string((CFIndex)expected_len == CFDataGetLength(outCms), out,
                              status = -1, "Output size differs from expected");
        require_noerr_action_string(memcmp(expected_output, CFDataGetBytePtr(outCms), expected_len), out,
                                    status = -1, "Output differs from expected");
    }

out:
    if (encoder) {
        SecCmsEncoderDestroy(encoder);
    }
    if (cmsg) {
        SecCmsMessageDestroy(cmsg);
    }
    CFReleaseNull(outCms);
    return status;

}

static OSStatus verify_please(SecKeychainRef keychain, uint8_t *data_to_verify, size_t length) {
    OSStatus status = SECFailure;
    SecCmsDecoderRef decoder = NULL;
    SecCmsMessageRef cmsg = NULL;
    SecCmsContentInfoRef cinfo = NULL;
    SecCmsSignedDataRef sigd = NULL;
    SecPolicyRef policy = NULL;
    SecTrustRef trust = NULL;

    if (!data_to_verify) {
        return errSecSuccess; // reasons...
    }

    require_noerr_string(status = SecCmsDecoderCreate(NULL, NULL, NULL, NULL,
                                                      NULL, NULL, &decoder), out,
                         "Failed to create decoder");
    require_noerr_string(status = SecCmsDecoderUpdate(decoder, data_to_verify, length), out,
                         "Failed to add data ");
    status = SecCmsDecoderFinish(decoder, &cmsg);
    decoder = NULL; // SecCmsDecoderFinish always frees the decoder
    require_noerr_quiet(status, out);

    require_action_string(cinfo = SecCmsMessageContentLevel(cmsg, 0), out,
                          status = errSecDecode, "Failed to get content info");
    require_action_string(SEC_OID_PKCS7_SIGNED_DATA == SecCmsContentInfoGetContentTypeTag(cinfo), out,
                          status = errSecDecode, "Content type was pkcs7 signed data");
    require_action_string(sigd = (SecCmsSignedDataRef)SecCmsContentInfoGetContent(cinfo), out,
                          status = errSecDecode, "Failed to get signed data");
    require_action_string(policy = SecPolicyCreateBasicX509(), out,
                          status = errSecAllocate, "Failed to create basic policy");
    status = SecCmsSignedDataVerifySignerInfo(sigd, 0, keychain, policy, &trust);

out:
    if (decoder) {
        SecCmsDecoderDestroy(decoder);
    }
    if (cmsg) {
        SecCmsMessageDestroy(cmsg);
    }
    CFReleaseNull(policy);
    CFReleaseNull(trust);
    return status;
}

static uint8_t *invalidate_signature(uint8_t *cms_data, size_t length) {
    if (!cms_data || !length || (length < 10)) {
        return NULL;
    }
    uint8_t *invalid_cms = NULL;

    invalid_cms = malloc(length);
    if (invalid_cms) {
        memcpy(invalid_cms, cms_data, length);
        /* This modifies the signature part of the test cms binaries */
        invalid_cms[length - 10] = 0x00;
    }

    return invalid_cms;
}

static OSStatus invalidate_and_verify(SecKeychainRef kc, uint8_t *cms_data, size_t length) {
    OSStatus status = SECFailure;
    uint8_t *invalid_cms_data = NULL;

    if (!cms_data) {
        return SECFailure; // reasons...
    }

    require_action_string(invalid_cms_data = invalidate_signature(cms_data, length), out,
                          status = errSecAllocate, "Unable to allocate buffer for invalid cms data");
    status = verify_please(kc, invalid_cms_data, length);

out:
    if (invalid_cms_data) {
        free(invalid_cms_data);
    }
    return status;
}

/* forward declaration */
static OSStatus decrypt_please(const uint8_t *data_to_decrypt, size_t length);

static OSStatus encrypt_please(SecCertificateRef recipient, SECOidTag encAlg, int keysize) {
    OSStatus status = SECFailure;
    SecCmsMessageRef cmsg = NULL;
    SecCmsEnvelopedDataRef envd = NULL;
    SecCmsContentInfoRef cinfo = NULL;
    SecCmsRecipientInfoRef rinfo = NULL;
    SecCmsEncoderRef encoder = NULL;
    CFMutableDataRef outCms = NULL;

    const uint8_t data_to_encrypt[] = "This data is encrypted. Is cool, no?";

    /* set up the message */
    require_action_string(cmsg = SecCmsMessageCreate(), out,
                          status = errSecAllocate, "Failed to create message");
    require_action_string(envd = SecCmsEnvelopedDataCreate(cmsg, encAlg, keysize), out,
                          status = errSecAllocate, "Failed to create enveloped data");
    require_action_string(cinfo = SecCmsMessageGetContentInfo(cmsg), out,
                          status = errSecParam, "Failed to get content info from cms message");
    require_noerr_string(status = SecCmsContentInfoSetContentEnvelopedData(cinfo, envd), out,
                         "Failed to set enveloped data in cms message");
    require_action_string(cinfo = SecCmsEnvelopedDataGetContentInfo(envd), out,
                          status = errSecParam, "Failed to get content info from enveloped data");
    require_noerr_string(status = SecCmsContentInfoSetContentData(cinfo, NULL, false), out,
                         "Failed to set data type in envelope");
    require_action_string(rinfo = SecCmsRecipientInfoCreate(envd, recipient), out,
                          status = errSecAllocate, "Failed to create recipient info");

    /* encode the message */
    require_action_string(outCms = CFDataCreateMutable(NULL, 0), out,
                          status = errSecAllocate, "Failed to create cms data");
    require_noerr_string(status = SecCmsEncoderCreate(cmsg, NULL, NULL, outCms, NULL, NULL,
                                                      NULL, NULL, &encoder), out,
                         "Failed to create encoder");
    require_noerr_string(status = SecCmsEncoderUpdate(encoder, data_to_encrypt, sizeof(data_to_encrypt)), out,
                         "Failed to update encoder with data");
    status = SecCmsEncoderFinish(encoder);
    encoder = NULL; // SecCmsEncoderFinish always frees the encoder but doesn't NULL it.
    require_noerr_quiet(status, out);

    require_noerr_string(status = decrypt_please(CFDataGetBytePtr(outCms), CFDataGetLength(outCms)), out,
                         "Failed to decrypt the data we just encrypted");

out:
    if (encoder) {
        SecCmsEncoderDestroy(encoder);
    }
    if (cmsg) {
        SecCmsMessageDestroy(cmsg);
    }
    CFReleaseNull(outCms);
    return status;
}

static OSStatus decrypt_please(const uint8_t *data_to_decrypt, size_t length) {
    OSStatus status = SECFailure;
    SecCmsDecoderRef decoder = NULL;
    SecCmsMessageRef cmsg = NULL;
    const SecAsn1Item *content = NULL;
    const uint8_t encrypted_string[] = "This data is encrypted. Is cool, no?";

    require_noerr_string(status = SecCmsDecoderCreate(NULL, NULL, NULL, NULL, NULL,
                                                      NULL, &decoder), out,
                         "Failed to create decoder");
    require_noerr_string(status = SecCmsDecoderUpdate(decoder, data_to_decrypt, length), out,
                         "Failed to add data ");
    status = SecCmsDecoderFinish(decoder, &cmsg);
    decoder = NULL; // SecCmsDecoderFinish always frees the decoder
    require_noerr_quiet(status, out);
    require_action_string(content = SecCmsMessageGetContent(cmsg), out,
                          status = errSecDecode, "Unable to get message contents");

    /* verify the output matches expected results */
    require_action_string(sizeof(encrypted_string) == content->Length, out,
                          status = -1, "Output size differs from expected");
    require_noerr_action_string(memcmp(encrypted_string, content->Data, content->Length), out,
                                status = -1, "Output differs from expected");

out:
    if (cmsg) {
        SecCmsMessageDestroy(cmsg);
    }
    return status;
}

/* Signing with attributes goes through a different code path than signing without,
 * so we need to test both. */
#define kNumberSignTests 10
static void sign_tests(SecIdentityRef identity, bool isRSA) {

    /* no attributes */
    is(sign_please(identity, SEC_OID_MD5, false, NULL, 0),
       SEC_ERROR_INVALID_ALGORITHM, "Signed with MD5. Not cool.");
    is(sign_please(identity, SEC_OID_SHA1, false, (isRSA) ? rsa_sha1 : NULL,
                   (isRSA) ? sizeof(rsa_sha1) : 0),
       errSecSuccess, "Signed with SHA-1");
    is(sign_please(identity, SEC_OID_SHA256, false, (isRSA) ? new_sig_alg_rsa_sha256 : NULL,
                   (isRSA) ? sizeof(rsa_sha256) : 0),
       errSecSuccess, "Signed with SHA-256");
    is(sign_please(identity, SEC_OID_SHA384, false, NULL, 0), errSecSuccess, "Signed with SHA-384");
    is(sign_please(identity, SEC_OID_SHA512, false, NULL, 0), errSecSuccess, "Signed with SHA-512");

    /* with attributes */
    is(sign_please(identity, SEC_OID_MD5, true, NULL, 0),
       SEC_ERROR_INVALID_ALGORITHM, "Signed with MD5 and attributes. Not cool.");
    is(sign_please(identity, SEC_OID_SHA1, true, (isRSA) ? rsa_sha1_attr : NULL,
                   (isRSA) ? sizeof(rsa_sha1_attr) : 0),
       errSecSuccess, "Signed with SHA-1 and attributes");
    is(sign_please(identity, SEC_OID_SHA256, true, (isRSA) ? rsa_sha256_attr : NULL,
                   (isRSA) ? sizeof(rsa_sha256_attr) : 0),
       errSecSuccess, "Signed with SHA-256 and attributes");
    is(sign_please(identity, SEC_OID_SHA384, true, NULL, 0),
       errSecSuccess, "Signed with SHA-384 and attributes");
    is(sign_please(identity, SEC_OID_SHA512, true, NULL, 0),
       errSecSuccess, "Signed with SHA-512 and attributes");
}

/* Verifying with attributes goes through a different code path than verifying without,
 * so we need to test both. */
#define kNumberVerifyTests 13
static void verify_tests(SecKeychainRef kc, bool isRsa) {
    /* no attributes */
    is(verify_please(kc, (isRsa) ? rsa_md5 : ec_md5,
                     (isRsa) ? sizeof(rsa_md5) : sizeof(ec_md5)),
       (isRsa) ? errSecSuccess : SECFailure, "Verify MD5, no attributes");
    is(verify_please(kc, (isRsa) ? rsa_sha1 : ec_sha1,
                     (isRsa) ? sizeof(rsa_sha1) : sizeof(ec_sha1)),
       errSecSuccess, "Verify SHA1, no attributes");
    is(verify_please(kc, (isRsa) ? rsa_sha256 : ec_sha256,
                     (isRsa) ? sizeof(rsa_sha256) : sizeof(ec_sha256)),
       errSecSuccess, "Verify SHA256, no attributes");

    /* with attributes */
    is(verify_please(kc, (isRsa) ? rsa_md5_attr : NULL,
                     (isRsa) ? sizeof(rsa_md5_attr) : 0),
       errSecSuccess, "Verify MD5, with attributes");
    is(verify_please(kc, (isRsa) ? rsa_sha1_attr : ec_sha1_attr,
                     (isRsa) ? sizeof(rsa_sha1_attr) : sizeof(ec_sha1_attr)),
       errSecSuccess, "Verify SHA1, with attributes");
    is(verify_please(kc, (isRsa) ? rsa_sha256_attr : ec_sha256_attr,
                     (isRsa) ? sizeof(rsa_sha256_attr) : sizeof(ec_sha256_attr)),
       errSecSuccess, "Verify SHA256, with attributes");

    /***** Once more, with validation errors *****/

    /* no attributes */
    is(verify_please(kc, (isRsa) ? rsa_sinfo_unknown_digest : ec_sinfo_unknown_digest,
                     (isRsa) ? sizeof(rsa_sinfo_unknown_digest) : sizeof(ec_sinfo_unknown_digest)),
       errSecInvalidDigestAlgorithm, "Verify unknown digest OID in signer info");
    is(invalidate_and_verify(kc, (isRsa) ? rsa_md5 : ec_md5,
                             (isRsa) ? sizeof(rsa_md5) : sizeof(ec_md5)),
       SECFailure, "Verify invalid MD5, no attributes");
    is(invalidate_and_verify(kc, (isRsa) ? rsa_sha1 : ec_sha1,
                             (isRsa) ? sizeof(rsa_sha1) : sizeof(ec_sha1)),
       SECFailure, "Verify invalid SHA1, no attributes");
    is(invalidate_and_verify(kc, (isRsa) ? rsa_sha256 : ec_sha256,
                             (isRsa) ? sizeof(rsa_sha256) : sizeof(ec_sha256)),
       SECFailure, "Verify invalid SHA256, no attributes");

    /* with attributes */
    is(invalidate_and_verify(kc, (isRsa) ? rsa_md5_attr : NULL,
                             (isRsa) ? sizeof(rsa_md5_attr) : 0),
       SECFailure, "Verify invalid MD5, with attributes");
    is(invalidate_and_verify(kc, (isRsa) ? rsa_sha1_attr : ec_sha1_attr,
                             (isRsa) ? sizeof(rsa_sha1_attr) : sizeof(ec_sha1_attr)),
       SECFailure, "Verify invalid SHA1, with attributes");
    is(invalidate_and_verify(kc, (isRsa) ? rsa_sha256_attr : ec_sha256_attr,
                             (isRsa) ? sizeof(rsa_sha256_attr) : sizeof(ec_sha256_attr)),
       SECFailure, "Verify invalid SHA256, with attributes");
}

#define kNumberEncryptTests 5
static void encrypt_tests(SecCertificateRef certificate) {
    is(encrypt_please(certificate, SEC_OID_DES_EDE3_CBC, 192),
       errSecSuccess, "Encrypt with 3DES");
    is(encrypt_please(certificate, SEC_OID_RC2_CBC, 128),
       errSecDecode, "Encrypt with 128-bit RC2");
    is(encrypt_please(certificate, SEC_OID_AES_128_CBC, 128),
       errSecSuccess, "Encrypt with 128-bit AES");
    is(encrypt_please(certificate, SEC_OID_AES_192_CBC, 192),
       errSecSuccess, "Encrypt with 192-bit AES");
    is(encrypt_please(certificate, SEC_OID_AES_256_CBC, 256),
       errSecSuccess, "Encrypt with 256-bit AES");
}

#define kNumberDecryptTests 5
static void decrypt_tests(bool isRsa) {
    is(decrypt_please((isRsa) ? rsa_3DES : ec_3DES,
                      (isRsa) ? sizeof(rsa_3DES) : sizeof(ec_3DES)),
       errSecSuccess, "Decrypt 3DES");
    is(decrypt_please((isRsa) ? rsa_RC2 : ec_RC2,
                      (isRsa) ? sizeof(rsa_RC2) : sizeof(ec_RC2)),
       errSecDecode, "Decrypt 128-bit RC2");
    is(decrypt_please((isRsa) ? rsa_AES_128 : ec_AES_128,
                      (isRsa) ? sizeof(rsa_AES_128) : sizeof(ec_AES_128)),
       errSecSuccess, "Decrypt 128-bit AES");
    is(decrypt_please((isRsa) ? rsa_AES_192 : ec_AES_192,
                      (isRsa) ? sizeof(rsa_AES_192) : sizeof(ec_AES_192)),
       errSecSuccess, "Decrypt 192-bit AES");
    is(decrypt_please((isRsa) ? rsa_AES_256 : ec_AES_256,
                      (isRsa) ? sizeof(rsa_AES_256) : sizeof(ec_AES_256)),
       errSecSuccess, "Decrypt 256-bit AES");
}

int si_95_cms_basic(int argc, char *const *argv)
{
    plan_tests(2*(kNumberSetupTests + kNumberSignTests + kNumberVerifyTests +
                  kNumberEncryptTests + kNumberDecryptTests + kNumberCleanupTests));

    SecIdentityRef identity = NULL;
    SecCertificateRef certificate = NULL;
    CFDataRef persistentRef = NULL;

    /* SecKeychainRef's aren't a thing on iOS. But the SecCms SPI takes one as
     * an argument. It gets ignored down in the bowels of libsecurity_smime, so
     * it's safe to just pass NULL. */
    SecKeychainRef kc = NULL;

    /* RSA tests */
    persistentRef = setup_keychain(_rsa_identity, sizeof(_rsa_identity), &identity, &certificate);
    sign_tests(identity, true);
    verify_tests(kc, true);
    encrypt_tests(certificate);
    decrypt_tests(true);
    cleanup_keychain(persistentRef, identity, certificate);

    /* EC tests */
    persistentRef = setup_keychain(_ec_identity, sizeof(_ec_identity), &identity, &certificate);
    sign_tests(identity, false);
    verify_tests(kc, false);
    encrypt_tests(certificate);
    decrypt_tests(false);
    cleanup_keychain(persistentRef, identity, certificate);
    
    return 0;
}
