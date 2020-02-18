/*
 * Copyright (c) 2018 Apple Inc. All Rights Reserved.
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

#ifndef mockaks_h
#define mockaks_h

#import <libaks.h>

#if __has_include(<MobileKeyBag/MobileKeyBag.h>)
#include <MobileKeyBag/MobileKeyBag.h>
#else

typedef struct  __MKBKeyBagHandle* MKBKeyBagHandleRef;
int MKBKeyBagCreateWithData(CFDataRef keybagBlob, MKBKeyBagHandleRef* newHandle);

#define kMobileKeyBagDeviceIsLocked 1
#define kMobileKeyBagDeviceIsUnlocked 0

int MKBKeyBagUnlock(MKBKeyBagHandleRef keybag, CFDataRef passcode);
int MKBKeyBagGetAKSHandle(MKBKeyBagHandleRef keybag, int32_t *handle);
int MKBGetDeviceLockState(CFDictionaryRef options);
CF_RETURNS_RETAINED CFDictionaryRef MKBUserTypeDeviceMode(CFDictionaryRef options, CFErrorRef * error);
int MKBForegroundUserSessionID( CFErrorRef * error);

#define kMobileKeyBagSuccess (0)
#define kMobileKeyBagError (-1)
#define kMobileKeyBagDeviceLockedError (-2)
#define kMobileKeyBagInvalidSecretError (-3)
#define kMobileKeyBagExistsError                (-4)
#define kMobileKeyBagNoMemoryError    (-5)

#endif // <MobileKeyBag/MobileKeyBag.h>


#if __OBJC2__

@interface SecMockAKS : NSObject
@property (class) keybag_state_t keybag_state;

+ (bool)isLocked:(keyclass_t)key_class;
+ (bool)isSEPDown;
+ (bool)useGenerationCount;

+ (void)lockClassA_C;
+ (void)lockClassA;

+ (void)unlockAllClasses;

+ (void)reset;
@end

#endif // OBJC2

#endif /* mockaks_h */
