// This file was automatically generated by protocompiler
// DO NOT EDIT!
// Compiled from SecDbBackupRecoverySet.proto

#import <Foundation/Foundation.h>
#import <ProtocolBuffer/PBCodable.h>

#ifdef __cplusplus
#define SECDBBACKUPBAGIDENTITY_FUNCTION extern "C"
#else
#define SECDBBACKUPBAGIDENTITY_FUNCTION extern
#endif

/** Maintain identity consistency by including this in key and bag messages */
@interface SecDbBackupBagIdentity : PBCodable <NSCopying>
{
    NSData *_baghash;
    NSData *_baguuid;
}


@property (nonatomic, readonly) BOOL hasBaguuid;
@property (nonatomic, retain) NSData *baguuid;

@property (nonatomic, readonly) BOOL hasBaghash;
@property (nonatomic, retain) NSData *baghash;

// Performs a shallow copy into other
- (void)copyTo:(SecDbBackupBagIdentity *)other;

// Performs a deep merge from other into self
// If set in other, singular values in self are replaced in self
// Singular composite values are recursively merged
// Repeated values from other are appended to repeated values in self
- (void)mergeFrom:(SecDbBackupBagIdentity *)other;

SECDBBACKUPBAGIDENTITY_FUNCTION BOOL SecDbBackupBagIdentityReadFrom(__unsafe_unretained SecDbBackupBagIdentity *self, __unsafe_unretained PBDataReader *reader);

@end

