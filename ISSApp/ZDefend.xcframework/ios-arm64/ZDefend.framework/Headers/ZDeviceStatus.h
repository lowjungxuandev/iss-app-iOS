//
//  ZDefendStatus.h
//  ZDefendStatus
//
//  Created by User on 01/11/2023
//  Copyright © 2023 Zimperium Inc. All rights reserved.
//

#ifndef ZDefendStatus__h
#define ZDefendStatus__h

#import <ZDefend/ZDefendTypes.h>
#import <ZDefend/ZDefendPolicy.h>
#import <ZDefend/ZDefendThreat.h>

__attribute__ ((visibility ("default")))
/**
 * The device status describing the ZDefend state when the status event occurred. See ZDeviceStatusCallback.
 *
 * The device status is updated when new policies are processed, device threats are generated and mitigated, and the device login status changes.
 *
 * The device status provides the base64 encoded status and the digital signature that can be used to verify the event authenticity.
 */
@interface ZDeviceStatus : NSObject

/**
 * @property deviceId - The unique identifier of the device.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull deviceId;

/**
 * @property sdkVersion -The build version of the SDK.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull sdkVersion;

/**
 * @property statusDate -  the device status generation time/date.
 */
@property (nonatomic, readonly, strong) NSDate * _Nonnull statusDate;

/**
 * @property deviceStatusBase64 - the base64 encoded device status. This is the base64 encoding of the json key/value pairs
 * describing this device status. The base64 string can be authenticated using the digital signature, see ZDeviceStatus#getBase64Signature.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull deviceStatusBase64;

/**
 * @property deviceStatusBase64Signature - the base64 device status digital signature. See ZDeviceStatus#getBase64.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull deviceStatusBase64Signature;

/**
 * @property compressedDeviceStatusBase64 - the compressed base64 encoded device status. This is the base64 encoding of the json key/value pairs
 * describing this device status. The base64 string can be authenticated using the digital signature, see ZDeviceStatus#getBase64Signature.
 * See #getCompressionType() for how this data is compressed.
 * This property is nil if compression is set to COMPRESSION_TYPE_NONE. See #setCompressionType(CompressionType).
 * Value is nil if
 */
@property (nonatomic, readonly, strong) NSString * _Nullable compressedDeviceStatusBase64;

/**
 * @property compressedDeviceStatusBase64Signature - the compressed base64 device status digital signature. See ZDeviceStatus#compressedDeviceStatusBase64.
 * This property is nil if compression is set to COMPRESSION_TYPE_NONE. See #setCompressionType(CompressionType).
 */
@property (nonatomic, readonly, strong) NSString * _Nullable compressedDeviceStatusBase64Signature;

/**
 * @property loginStatus - the login status.
 */
@property (nonatomic, readonly) ZLoginStatus loginStatus;

/**
 * @property nameForLoginStatus - convenience property for the loginStatus description.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull nameForLoginStatus;

/**
 * @property loginLastError - the last login error. See ZLoginError.
 *          LOGIN_ERROR_NONE is returned when loginStatus is LOGGED_IN or LOGIN_IN_PROGRESS.
 */
@property (nonatomic, readonly) ZLoginError loginLastError;

/**
 * @property nameForLoginLastError - convenience property for the loginLastError description
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull nameForLoginLastError;

/**
 * @property devicePolicies - a list of ZDefendPolicy objects.
 */
@property (nonatomic, readonly, strong) NSArray<ZDefendPolicy *> * _Nonnull devicePolicies;

/**
 * @property allThreats - the threats in the device device status. The threat list will include all new, active and previous threats including mitigated threats.
 */
@property (nonatomic, readonly, strong) NSArray<ZDefendThreat *> * _Nonnull allThreats;

/**
 * @property activeThreats - the  non-mitigated only threat list of the ZDeviceStatus event.
 */
@property (nonatomic, readonly, strong) NSArray<ZDefendThreat *> * _Nonnull activeThreats;

/**
 * @property mitigatedThreats - the mitigated only threat list of the ZDeviceStatus event.
 */
@property (nonatomic, readonly, strong) NSArray<ZDefendThreat *> * _Nonnull mitigatedThreats;

/**
 * @property activeNewThreats - the new non-mitigated threat list since the prior ZDeviceStatus event.
 */
@property (nonatomic, readonly, strong) NSArray<ZDefendThreat *> * _Nonnull activeNewThreats;

/**
 * @property mitigatedNewThreats - the new mitigated threat list since the prior ZDeviceStatus event.
 */
@property (nonatomic, readonly, strong) NSArray<ZDefendThreat *> * _Nonnull mitigatedNewThreats;

/**
 * @property initialScanProgressPercentage - Get the initial scan progress percentage. 0 as the scan is starting,
 * 1 to 99 of the current scan progress percentage, 100 when the scan is complete. The initial scan starts immediately after ZDefend login.
 * .
 */
@property (nonatomic, readonly) int initialScanProgressPercentage;

/**
 * @property threatTextExcluded - Get the text excluded configuration state for this device status event. See ZDeviceStatus#excludeThreatText(boolean).
 * Property is  true if the localized text has been excluded for this event.
 */
@property (nonatomic, readonly) bool threatTextExcluded;

/**
 * @property policyStatusExcluded - Get the policy status excluded configuration state for this device status event. See ZDeviceStatus#excludePolicyStatus(boolean).
 * Property is true if the policy status has been excluded for this event.
 */
@property (nonatomic, readonly) bool policyStatusExcluded;

/**
 * Get the compression type used for this device status event. See ZDeviceStatus#setCompressionType(ZDeviceStatusCompressionType).
 * @return the data compression type used for #getCompressedBase64()}. COMPRESSION_TYPE_NONE is returned if compressed is not enabled.
 */
@property (nonatomic, readonly) ZDeviceStatusCompressionType compressionType;


/**
 * Configure the device status to exclude localized text from device status updates. Setting true will reduce the device status event size.
 * This configuration is persistent for the current login.
 * @param excludeText true to exclude localized text from status updates. The default configuration is false.
 */
+ (void)excludeThreatText:(bool)excludeText;

/**
 * Configure the device status to exclude policy status from device status updates. Setting true will reduce the device status event size.
 * This configuration is persistent for the current login.
 * @param excludePolicyStatus true to exclude policy status from status updates. The default configuration is false.
 */
+ (void)excludePolicyStatus:(bool)excludePolicyStatus;

/**
 * Configure the device status to produce compressed base64 device status. ZDeviceStatus#getCompressedBase64().
 * By default compression is disabled and the type is set to COMPRESSION_TYPE_NONE.
 * @param type the compression type use.
 */
+ (void)setCompressionType:(ZDeviceStatusCompressionType) type;

/**
 * Get a specific device status policy.
 *
 * @param policyType the device policy requested. See ZDefendTypes.h ZDefendPolicyType.
 * @return the requested ZDefendPolicy. nil is returned if the requsted policy type is not recognized.
 */
- (ZDefendPolicy * _Nullable) getPolicy:(ZDefendPolicyType)policyType;


@end

/**
 * ZDeviceStatusCallback is the handler for receiving device status updates.
 *
 * A block implementing this interface is required for receiving device status updates. See ZDefend#addDeviceStatusCallback:ZDeviceStatusCallback for registering the custom handler implementation.
 *
 * @param deviceStatus the current device status. See interface ZDeviceStatus.
 */
typedef void (^ZDeviceStatusCallback)(ZDeviceStatus * _Nonnull deviceStatus);

/**
 * ZDeviceStatusJsonCallback is the handler for receiving device status json updates.
 *
 * A block implementing this interface is required for receiving device status json updates. See ZDefend#addDeviceStatusJsonCallback:ZDeviceStatusJsonCallback for registering the custom handler implementation.
 *
 * @param deviceStatusJsonBase64 the base64 encoded device status json string.
 * @param base64Signature the base64 device status digital signature.
 */
typedef void (^ZDeviceStatusJsonCallback)(NSString * _Nonnull deviceStatusJsonBase64, NSString * _Nonnull base64Signature);

#endif /* ZDefendStatus__h */

