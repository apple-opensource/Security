// This file was automatically generated by protocompiler
// DO NOT EDIT!
// Compiled from OTEscrowRecord.proto

#import "OTEscrowRecord.h"
#import <ProtocolBuffer/PBConstants.h>
#import <ProtocolBuffer/PBHashUtil.h>
#import <ProtocolBuffer/PBDataReader.h>

#import "OTEscrowRecordMetadata.h"

#if !__has_feature(objc_arc)
# error This generated file depends on ARC but it is not enabled; turn on ARC, or use 'objc_use_arc' option to generate non-ARC code.
#endif

@implementation OTEscrowRecord

@synthesize creationDate = _creationDate;
- (void)setCreationDate:(uint64_t)v
{
    _has.creationDate = YES;
    _creationDate = v;
}
- (void)setHasCreationDate:(BOOL)f
{
    _has.creationDate = f;
}
- (BOOL)hasCreationDate
{
    return _has.creationDate != 0;
}
@synthesize remainingAttempts = _remainingAttempts;
- (void)setRemainingAttempts:(uint64_t)v
{
    _has.remainingAttempts = YES;
    _remainingAttempts = v;
}
- (void)setHasRemainingAttempts:(BOOL)f
{
    _has.remainingAttempts = f;
}
- (BOOL)hasRemainingAttempts
{
    return _has.remainingAttempts != 0;
}
- (BOOL)hasEscrowInformationMetadata
{
    return _escrowInformationMetadata != nil;
}
@synthesize escrowInformationMetadata = _escrowInformationMetadata;
- (BOOL)hasLabel
{
    return _label != nil;
}
@synthesize label = _label;
@synthesize silentAttemptAllowed = _silentAttemptAllowed;
- (void)setSilentAttemptAllowed:(uint64_t)v
{
    _has.silentAttemptAllowed = YES;
    _silentAttemptAllowed = v;
}
- (void)setHasSilentAttemptAllowed:(BOOL)f
{
    _has.silentAttemptAllowed = f;
}
- (BOOL)hasSilentAttemptAllowed
{
    return _has.silentAttemptAllowed != 0;
}
@synthesize recordStatus = _recordStatus;
- (OTEscrowRecord_RecordStatus)recordStatus
{
    return _has.recordStatus ? _recordStatus : OTEscrowRecord_RecordStatus_RECORD_STATUS_VALID;
}
- (void)setRecordStatus:(OTEscrowRecord_RecordStatus)v
{
    _has.recordStatus = YES;
    _recordStatus = v;
}
- (void)setHasRecordStatus:(BOOL)f
{
    _has.recordStatus = f;
}
- (BOOL)hasRecordStatus
{
    return _has.recordStatus != 0;
}
- (NSString *)recordStatusAsString:(OTEscrowRecord_RecordStatus)value
{
    return OTEscrowRecord_RecordStatusAsString(value);
}
- (OTEscrowRecord_RecordStatus)StringAsRecordStatus:(NSString *)str
{
    return StringAsOTEscrowRecord_RecordStatus(str);
}
- (BOOL)hasRecordId
{
    return _recordId != nil;
}
@synthesize recordId = _recordId;
@synthesize recoveryStatus = _recoveryStatus;
- (OTEscrowRecord_RecoveryStatus)recoveryStatus
{
    return _has.recoveryStatus ? _recoveryStatus : OTEscrowRecord_RecoveryStatus_RECOVERY_STATUS_VALID;
}
- (void)setRecoveryStatus:(OTEscrowRecord_RecoveryStatus)v
{
    _has.recoveryStatus = YES;
    _recoveryStatus = v;
}
- (void)setHasRecoveryStatus:(BOOL)f
{
    _has.recoveryStatus = f;
}
- (BOOL)hasRecoveryStatus
{
    return _has.recoveryStatus != 0;
}
- (NSString *)recoveryStatusAsString:(OTEscrowRecord_RecoveryStatus)value
{
    return OTEscrowRecord_RecoveryStatusAsString(value);
}
- (OTEscrowRecord_RecoveryStatus)StringAsRecoveryStatus:(NSString *)str
{
    return StringAsOTEscrowRecord_RecoveryStatus(str);
}
@synthesize coolOffEnd = _coolOffEnd;
- (void)setCoolOffEnd:(uint64_t)v
{
    _has.coolOffEnd = YES;
    _coolOffEnd = v;
}
- (void)setHasCoolOffEnd:(BOOL)f
{
    _has.coolOffEnd = f;
}
- (BOOL)hasCoolOffEnd
{
    return _has.coolOffEnd != 0;
}
- (BOOL)hasSerialNumber
{
    return _serialNumber != nil;
}
@synthesize serialNumber = _serialNumber;
@synthesize recordViability = _recordViability;
- (OTEscrowRecord_RecordViability)recordViability
{
    return _has.recordViability ? _recordViability : OTEscrowRecord_RecordViability_RECORD_VIABILITY_FULLY_VIABLE;
}
- (void)setRecordViability:(OTEscrowRecord_RecordViability)v
{
    _has.recordViability = YES;
    _recordViability = v;
}
- (void)setHasRecordViability:(BOOL)f
{
    _has.recordViability = f;
}
- (BOOL)hasRecordViability
{
    return _has.recordViability != 0;
}
- (NSString *)recordViabilityAsString:(OTEscrowRecord_RecordViability)value
{
    return OTEscrowRecord_RecordViabilityAsString(value);
}
- (OTEscrowRecord_RecordViability)StringAsRecordViability:(NSString *)str
{
    return StringAsOTEscrowRecord_RecordViability(str);
}
@synthesize viabilityStatus = _viabilityStatus;
- (OTEscrowRecord_SOSViability)viabilityStatus
{
    return _has.viabilityStatus ? _viabilityStatus : OTEscrowRecord_SOSViability_SOS_VIABLE_UNKNOWN;
}
- (void)setViabilityStatus:(OTEscrowRecord_SOSViability)v
{
    _has.viabilityStatus = YES;
    _viabilityStatus = v;
}
- (void)setHasViabilityStatus:(BOOL)f
{
    _has.viabilityStatus = f;
}
- (BOOL)hasViabilityStatus
{
    return _has.viabilityStatus != 0;
}
- (NSString *)viabilityStatusAsString:(OTEscrowRecord_SOSViability)value
{
    return OTEscrowRecord_SOSViabilityAsString(value);
}
- (OTEscrowRecord_SOSViability)StringAsViabilityStatus:(NSString *)str
{
    return StringAsOTEscrowRecord_SOSViability(str);
}
- (BOOL)hasFederationId
{
    return _federationId != nil;
}
@synthesize federationId = _federationId;
- (BOOL)hasExpectedFederationId
{
    return _expectedFederationId != nil;
}
@synthesize expectedFederationId = _expectedFederationId;

- (NSString *)description
{
    return [NSString stringWithFormat:@"%@ %@", [super description], [self dictionaryRepresentation]];
}

- (NSDictionary *)dictionaryRepresentation
{
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    if (self->_has.creationDate)
    {
        [dict setObject:[NSNumber numberWithUnsignedLongLong:self->_creationDate] forKey:@"creation_date"];
    }
    if (self->_has.remainingAttempts)
    {
        [dict setObject:[NSNumber numberWithUnsignedLongLong:self->_remainingAttempts] forKey:@"remaining_attempts"];
    }
    if (self->_escrowInformationMetadata)
    {
        [dict setObject:[_escrowInformationMetadata dictionaryRepresentation] forKey:@"escrow_information_metadata"];
    }
    if (self->_label)
    {
        [dict setObject:self->_label forKey:@"label"];
    }
    if (self->_has.silentAttemptAllowed)
    {
        [dict setObject:[NSNumber numberWithUnsignedLongLong:self->_silentAttemptAllowed] forKey:@"silent_attempt_allowed"];
    }
    if (self->_has.recordStatus)
    {
        [dict setObject:OTEscrowRecord_RecordStatusAsString(self->_recordStatus) forKey:@"record_status"];
    }
    if (self->_recordId)
    {
        [dict setObject:self->_recordId forKey:@"record_id"];
    }
    if (self->_has.recoveryStatus)
    {
        [dict setObject:OTEscrowRecord_RecoveryStatusAsString(self->_recoveryStatus) forKey:@"recovery_status"];
    }
    if (self->_has.coolOffEnd)
    {
        [dict setObject:[NSNumber numberWithUnsignedLongLong:self->_coolOffEnd] forKey:@"cool_off_end"];
    }
    if (self->_serialNumber)
    {
        [dict setObject:self->_serialNumber forKey:@"serial_number"];
    }
    if (self->_has.recordViability)
    {
        [dict setObject:OTEscrowRecord_RecordViabilityAsString(self->_recordViability) forKey:@"record_viability"];
    }
    if (self->_has.viabilityStatus)
    {
        [dict setObject:OTEscrowRecord_SOSViabilityAsString(self->_viabilityStatus) forKey:@"viability_status"];
    }
    if (self->_federationId)
    {
        [dict setObject:self->_federationId forKey:@"federation_id"];
    }
    if (self->_expectedFederationId)
    {
        [dict setObject:self->_expectedFederationId forKey:@"expected_federation_id"];
    }
    return dict;
}

BOOL OTEscrowRecordReadFrom(__unsafe_unretained OTEscrowRecord *self, __unsafe_unretained PBDataReader *reader) {
    while (PBReaderHasMoreData(reader)) {
        uint32_t tag = 0;
        uint8_t aType = 0;

        PBReaderReadTag32AndType(reader, &tag, &aType);

        if (PBReaderHasError(reader))
            break;

        if (aType == TYPE_END_GROUP) {
            break;
        }

        switch (tag) {

            case 1 /* creationDate */:
            {
                self->_has.creationDate = YES;
                self->_creationDate = PBReaderReadUint64(reader);
            }
            break;
            case 2 /* remainingAttempts */:
            {
                self->_has.remainingAttempts = YES;
                self->_remainingAttempts = PBReaderReadUint64(reader);
            }
            break;
            case 3 /* escrowInformationMetadata */:
            {
                OTEscrowRecordMetadata *new_escrowInformationMetadata = [[OTEscrowRecordMetadata alloc] init];
                self->_escrowInformationMetadata = new_escrowInformationMetadata;
                PBDataReaderMark mark_escrowInformationMetadata;
                BOOL markError = !PBReaderPlaceMark(reader, &mark_escrowInformationMetadata);
                if (markError)
                {
                    return NO;
                }
                BOOL inError = !OTEscrowRecordMetadataReadFrom(new_escrowInformationMetadata, reader);
                if (inError)
                {
                    return NO;
                }
                PBReaderRecallMark(reader, &mark_escrowInformationMetadata);
            }
            break;
            case 4 /* label */:
            {
                NSString *new_label = PBReaderReadString(reader);
                self->_label = new_label;
            }
            break;
            case 9 /* silentAttemptAllowed */:
            {
                self->_has.silentAttemptAllowed = YES;
                self->_silentAttemptAllowed = PBReaderReadUint64(reader);
            }
            break;
            case 10 /* recordStatus */:
            {
                self->_has.recordStatus = YES;
                self->_recordStatus = PBReaderReadInt32(reader);
            }
            break;
            case 11 /* recordId */:
            {
                NSString *new_recordId = PBReaderReadString(reader);
                self->_recordId = new_recordId;
            }
            break;
            case 12 /* recoveryStatus */:
            {
                self->_has.recoveryStatus = YES;
                self->_recoveryStatus = PBReaderReadInt32(reader);
            }
            break;
            case 13 /* coolOffEnd */:
            {
                self->_has.coolOffEnd = YES;
                self->_coolOffEnd = PBReaderReadUint64(reader);
            }
            break;
            case 14 /* serialNumber */:
            {
                NSString *new_serialNumber = PBReaderReadString(reader);
                self->_serialNumber = new_serialNumber;
            }
            break;
            case 15 /* recordViability */:
            {
                self->_has.recordViability = YES;
                self->_recordViability = PBReaderReadInt32(reader);
            }
            break;
            case 16 /* viabilityStatus */:
            {
                self->_has.viabilityStatus = YES;
                self->_viabilityStatus = PBReaderReadInt32(reader);
            }
            break;
            case 17 /* federationId */:
            {
                NSString *new_federationId = PBReaderReadString(reader);
                self->_federationId = new_federationId;
            }
            break;
            case 18 /* expectedFederationId */:
            {
                NSString *new_expectedFederationId = PBReaderReadString(reader);
                self->_expectedFederationId = new_expectedFederationId;
            }
            break;
            default:
                if (!PBReaderSkipValueWithTag(reader, tag, aType))
                    return NO;
                break;
        }
    }
    return !PBReaderHasError(reader);
}

- (BOOL)readFrom:(PBDataReader *)reader
{
    return OTEscrowRecordReadFrom(self, reader);
}
- (void)writeTo:(PBDataWriter *)writer
{
    /* creationDate */
    {
        if (self->_has.creationDate)
        {
            PBDataWriterWriteUint64Field(writer, self->_creationDate, 1);
        }
    }
    /* remainingAttempts */
    {
        if (self->_has.remainingAttempts)
        {
            PBDataWriterWriteUint64Field(writer, self->_remainingAttempts, 2);
        }
    }
    /* escrowInformationMetadata */
    {
        if (self->_escrowInformationMetadata != nil)
        {
            PBDataWriterWriteSubmessage(writer, self->_escrowInformationMetadata, 3);
        }
    }
    /* label */
    {
        if (self->_label)
        {
            PBDataWriterWriteStringField(writer, self->_label, 4);
        }
    }
    /* silentAttemptAllowed */
    {
        if (self->_has.silentAttemptAllowed)
        {
            PBDataWriterWriteUint64Field(writer, self->_silentAttemptAllowed, 9);
        }
    }
    /* recordStatus */
    {
        if (self->_has.recordStatus)
        {
            PBDataWriterWriteInt32Field(writer, self->_recordStatus, 10);
        }
    }
    /* recordId */
    {
        if (self->_recordId)
        {
            PBDataWriterWriteStringField(writer, self->_recordId, 11);
        }
    }
    /* recoveryStatus */
    {
        if (self->_has.recoveryStatus)
        {
            PBDataWriterWriteInt32Field(writer, self->_recoveryStatus, 12);
        }
    }
    /* coolOffEnd */
    {
        if (self->_has.coolOffEnd)
        {
            PBDataWriterWriteUint64Field(writer, self->_coolOffEnd, 13);
        }
    }
    /* serialNumber */
    {
        if (self->_serialNumber)
        {
            PBDataWriterWriteStringField(writer, self->_serialNumber, 14);
        }
    }
    /* recordViability */
    {
        if (self->_has.recordViability)
        {
            PBDataWriterWriteInt32Field(writer, self->_recordViability, 15);
        }
    }
    /* viabilityStatus */
    {
        if (self->_has.viabilityStatus)
        {
            PBDataWriterWriteInt32Field(writer, self->_viabilityStatus, 16);
        }
    }
    /* federationId */
    {
        if (self->_federationId)
        {
            PBDataWriterWriteStringField(writer, self->_federationId, 17);
        }
    }
    /* expectedFederationId */
    {
        if (self->_expectedFederationId)
        {
            PBDataWriterWriteStringField(writer, self->_expectedFederationId, 18);
        }
    }
}

- (void)copyTo:(OTEscrowRecord *)other
{
    if (self->_has.creationDate)
    {
        other->_creationDate = _creationDate;
        other->_has.creationDate = YES;
    }
    if (self->_has.remainingAttempts)
    {
        other->_remainingAttempts = _remainingAttempts;
        other->_has.remainingAttempts = YES;
    }
    if (_escrowInformationMetadata)
    {
        other.escrowInformationMetadata = _escrowInformationMetadata;
    }
    if (_label)
    {
        other.label = _label;
    }
    if (self->_has.silentAttemptAllowed)
    {
        other->_silentAttemptAllowed = _silentAttemptAllowed;
        other->_has.silentAttemptAllowed = YES;
    }
    if (self->_has.recordStatus)
    {
        other->_recordStatus = _recordStatus;
        other->_has.recordStatus = YES;
    }
    if (_recordId)
    {
        other.recordId = _recordId;
    }
    if (self->_has.recoveryStatus)
    {
        other->_recoveryStatus = _recoveryStatus;
        other->_has.recoveryStatus = YES;
    }
    if (self->_has.coolOffEnd)
    {
        other->_coolOffEnd = _coolOffEnd;
        other->_has.coolOffEnd = YES;
    }
    if (_serialNumber)
    {
        other.serialNumber = _serialNumber;
    }
    if (self->_has.recordViability)
    {
        other->_recordViability = _recordViability;
        other->_has.recordViability = YES;
    }
    if (self->_has.viabilityStatus)
    {
        other->_viabilityStatus = _viabilityStatus;
        other->_has.viabilityStatus = YES;
    }
    if (_federationId)
    {
        other.federationId = _federationId;
    }
    if (_expectedFederationId)
    {
        other.expectedFederationId = _expectedFederationId;
    }
}

- (id)copyWithZone:(NSZone *)zone
{
    OTEscrowRecord *copy = [[[self class] allocWithZone:zone] init];
    if (self->_has.creationDate)
    {
        copy->_creationDate = _creationDate;
        copy->_has.creationDate = YES;
    }
    if (self->_has.remainingAttempts)
    {
        copy->_remainingAttempts = _remainingAttempts;
        copy->_has.remainingAttempts = YES;
    }
    copy->_escrowInformationMetadata = [_escrowInformationMetadata copyWithZone:zone];
    copy->_label = [_label copyWithZone:zone];
    if (self->_has.silentAttemptAllowed)
    {
        copy->_silentAttemptAllowed = _silentAttemptAllowed;
        copy->_has.silentAttemptAllowed = YES;
    }
    if (self->_has.recordStatus)
    {
        copy->_recordStatus = _recordStatus;
        copy->_has.recordStatus = YES;
    }
    copy->_recordId = [_recordId copyWithZone:zone];
    if (self->_has.recoveryStatus)
    {
        copy->_recoveryStatus = _recoveryStatus;
        copy->_has.recoveryStatus = YES;
    }
    if (self->_has.coolOffEnd)
    {
        copy->_coolOffEnd = _coolOffEnd;
        copy->_has.coolOffEnd = YES;
    }
    copy->_serialNumber = [_serialNumber copyWithZone:zone];
    if (self->_has.recordViability)
    {
        copy->_recordViability = _recordViability;
        copy->_has.recordViability = YES;
    }
    if (self->_has.viabilityStatus)
    {
        copy->_viabilityStatus = _viabilityStatus;
        copy->_has.viabilityStatus = YES;
    }
    copy->_federationId = [_federationId copyWithZone:zone];
    copy->_expectedFederationId = [_expectedFederationId copyWithZone:zone];
    return copy;
}

- (BOOL)isEqual:(id)object
{
    OTEscrowRecord *other = (OTEscrowRecord *)object;
    return [other isMemberOfClass:[self class]]
    &&
    ((self->_has.creationDate && other->_has.creationDate && self->_creationDate == other->_creationDate) || (!self->_has.creationDate && !other->_has.creationDate))
    &&
    ((self->_has.remainingAttempts && other->_has.remainingAttempts && self->_remainingAttempts == other->_remainingAttempts) || (!self->_has.remainingAttempts && !other->_has.remainingAttempts))
    &&
    ((!self->_escrowInformationMetadata && !other->_escrowInformationMetadata) || [self->_escrowInformationMetadata isEqual:other->_escrowInformationMetadata])
    &&
    ((!self->_label && !other->_label) || [self->_label isEqual:other->_label])
    &&
    ((self->_has.silentAttemptAllowed && other->_has.silentAttemptAllowed && self->_silentAttemptAllowed == other->_silentAttemptAllowed) || (!self->_has.silentAttemptAllowed && !other->_has.silentAttemptAllowed))
    &&
    ((self->_has.recordStatus && other->_has.recordStatus && self->_recordStatus == other->_recordStatus) || (!self->_has.recordStatus && !other->_has.recordStatus))
    &&
    ((!self->_recordId && !other->_recordId) || [self->_recordId isEqual:other->_recordId])
    &&
    ((self->_has.recoveryStatus && other->_has.recoveryStatus && self->_recoveryStatus == other->_recoveryStatus) || (!self->_has.recoveryStatus && !other->_has.recoveryStatus))
    &&
    ((self->_has.coolOffEnd && other->_has.coolOffEnd && self->_coolOffEnd == other->_coolOffEnd) || (!self->_has.coolOffEnd && !other->_has.coolOffEnd))
    &&
    ((!self->_serialNumber && !other->_serialNumber) || [self->_serialNumber isEqual:other->_serialNumber])
    &&
    ((self->_has.recordViability && other->_has.recordViability && self->_recordViability == other->_recordViability) || (!self->_has.recordViability && !other->_has.recordViability))
    &&
    ((self->_has.viabilityStatus && other->_has.viabilityStatus && self->_viabilityStatus == other->_viabilityStatus) || (!self->_has.viabilityStatus && !other->_has.viabilityStatus))
    &&
    ((!self->_federationId && !other->_federationId) || [self->_federationId isEqual:other->_federationId])
    &&
    ((!self->_expectedFederationId && !other->_expectedFederationId) || [self->_expectedFederationId isEqual:other->_expectedFederationId])
    ;
}

- (NSUInteger)hash
{
    return 0
    ^
    (self->_has.creationDate ? PBHashInt((NSUInteger)self->_creationDate) : 0)
    ^
    (self->_has.remainingAttempts ? PBHashInt((NSUInteger)self->_remainingAttempts) : 0)
    ^
    [self->_escrowInformationMetadata hash]
    ^
    [self->_label hash]
    ^
    (self->_has.silentAttemptAllowed ? PBHashInt((NSUInteger)self->_silentAttemptAllowed) : 0)
    ^
    (self->_has.recordStatus ? PBHashInt((NSUInteger)self->_recordStatus) : 0)
    ^
    [self->_recordId hash]
    ^
    (self->_has.recoveryStatus ? PBHashInt((NSUInteger)self->_recoveryStatus) : 0)
    ^
    (self->_has.coolOffEnd ? PBHashInt((NSUInteger)self->_coolOffEnd) : 0)
    ^
    [self->_serialNumber hash]
    ^
    (self->_has.recordViability ? PBHashInt((NSUInteger)self->_recordViability) : 0)
    ^
    (self->_has.viabilityStatus ? PBHashInt((NSUInteger)self->_viabilityStatus) : 0)
    ^
    [self->_federationId hash]
    ^
    [self->_expectedFederationId hash]
    ;
}

- (void)mergeFrom:(OTEscrowRecord *)other
{
    if (other->_has.creationDate)
    {
        self->_creationDate = other->_creationDate;
        self->_has.creationDate = YES;
    }
    if (other->_has.remainingAttempts)
    {
        self->_remainingAttempts = other->_remainingAttempts;
        self->_has.remainingAttempts = YES;
    }
    if (self->_escrowInformationMetadata && other->_escrowInformationMetadata)
    {
        [self->_escrowInformationMetadata mergeFrom:other->_escrowInformationMetadata];
    }
    else if (!self->_escrowInformationMetadata && other->_escrowInformationMetadata)
    {
        [self setEscrowInformationMetadata:other->_escrowInformationMetadata];
    }
    if (other->_label)
    {
        [self setLabel:other->_label];
    }
    if (other->_has.silentAttemptAllowed)
    {
        self->_silentAttemptAllowed = other->_silentAttemptAllowed;
        self->_has.silentAttemptAllowed = YES;
    }
    if (other->_has.recordStatus)
    {
        self->_recordStatus = other->_recordStatus;
        self->_has.recordStatus = YES;
    }
    if (other->_recordId)
    {
        [self setRecordId:other->_recordId];
    }
    if (other->_has.recoveryStatus)
    {
        self->_recoveryStatus = other->_recoveryStatus;
        self->_has.recoveryStatus = YES;
    }
    if (other->_has.coolOffEnd)
    {
        self->_coolOffEnd = other->_coolOffEnd;
        self->_has.coolOffEnd = YES;
    }
    if (other->_serialNumber)
    {
        [self setSerialNumber:other->_serialNumber];
    }
    if (other->_has.recordViability)
    {
        self->_recordViability = other->_recordViability;
        self->_has.recordViability = YES;
    }
    if (other->_has.viabilityStatus)
    {
        self->_viabilityStatus = other->_viabilityStatus;
        self->_has.viabilityStatus = YES;
    }
    if (other->_federationId)
    {
        [self setFederationId:other->_federationId];
    }
    if (other->_expectedFederationId)
    {
        [self setExpectedFederationId:other->_expectedFederationId];
    }
}

@end

