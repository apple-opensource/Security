//
//  PersistentState.m
//  Security
//
//  Created by J Osborne on 7/11/13.
//
//

#import "PersistentState.h"
#import <Foundation/Foundation.h>

@interface PersistentState()
-(NSURL*)urlForStorage;
@end

@implementation PersistentState

-(NSURL*)urlForStorage
{
    return [NSURL fileURLWithPath:@"/var/mobile/Library/Preferences/com.apple.security.CircleJoinRequested.plist" isDirectory:NO];
}

-(unsigned int)defaultPendingApplicationReminderAlertInterval
{
    return 24 * 60 * 60;
}

+(instancetype)loadFromStorage
{
    PersistentState *state = [[PersistentState alloc] init];
    if (!state) {
        return state;
    }
    
    NSError *error = nil;
    id plist = @{@"lastWritten": [NSDate distantPast]};
    
    NSData *stateData = [NSData dataWithContentsOfURL:[state urlForStorage] options:0 error:&error];
    if (!stateData) {
        NSLog(@"Can't read state data (p=%@, err=%@)", [state urlForStorage], error);
    } else {
        NSPropertyListFormat format;
        id plistTmp = [NSPropertyListSerialization propertyListWithData:stateData options: NSPropertyListMutableContainersAndLeaves format:&format error:&error];
        
        if (plistTmp == nil) {
            NSLog(@"Can't deserialize %@, e=%@", stateData, error);
        } else {
            plist = plistTmp;
        }
    }
    
    state.lastCircleStatus				= plist[@"lastCircleStatus"] ? [plist[@"lastCircleStatus"] intValue] : kSOSCCCircleAbsent;
    state.lastWritten     				= plist[@"lastWritten"];
	state.pendingApplicationReminder	= plist[@"pendingApplicationReminder"] ?: [NSDate distantFuture];
	state.applicationDate				= plist[@"applicationDate"]            ?: [NSDate distantPast];
    state.debugShowLeftReason			= plist[@"debugShowLeftReason"];
    state.pendingApplicationReminderAlertInterval	= plist[@"pendingApplicationReminderAlertInterval"] ?
 															[plist[@"pendingApplicationReminderAlertInterval"] unsignedIntValue] :
 															[state defaultPendingApplicationReminderAlertInterval];
    state.absentCircleWithNoReason		= plist[@"absentCircleWithNoReason"] ? [plist[@"absentCircleWithNoReason"] intValue] : NO;
    
    return state;
}

-(void)writeToStorage
{
    NSDictionary *plist = @{@"lastCircleStatus": [NSNumber numberWithInt:self.lastCircleStatus],
                            @"lastWritten": [NSDate date],
							@"pendingApplicationReminder": self.pendingApplicationReminder ?: [NSDate distantFuture],
							@"applicationDate": self.applicationDate ?: [NSDate distantPast],
                            @"pendingApplicationReminderAlertInterval": [NSNumber numberWithUnsignedInt:self.pendingApplicationReminderAlertInterval],
                            @"absentCircleWithNoReason": [NSNumber numberWithBool:self.absentCircleWithNoReason]};
    if (self.debugShowLeftReason) {
        NSMutableDictionary *tmp = [plist mutableCopy];
        tmp[@"debugShowLeftReason"] = self.debugShowLeftReason;
        plist =[tmp copy];
    }
    NSLog(@"writeToStorage plist=%@", plist);
    
    NSError *error = nil;
    NSData *stateData = [NSPropertyListSerialization dataWithPropertyList:plist format:NSPropertyListXMLFormat_v1_0 options:kCFPropertyListImmutable error:&error];
    if (!stateData) {
        NSLog(@"Can't serialize %@: %@", plist, error);
        return;
    }
    if (![stateData writeToURL:[self urlForStorage] options:NSDataWritingAtomic error:&error]) {
        NSLog(@"Can't write to %@, error=%@", [self urlForStorage], error);
    }
}

@end
