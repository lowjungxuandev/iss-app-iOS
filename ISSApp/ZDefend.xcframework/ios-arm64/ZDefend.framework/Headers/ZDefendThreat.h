//
//  ZDefendThreat.h
//  ZDefendThreat
//
//  Created by User on 01/11/2023
//  Copyright © 2023 Zimperium Inc. All rights reserved.
//

#ifndef ZDefendThreat__h
#define ZDefendThreat__h

#import <Foundation/Foundation.h>

/**
 * The possible threat severity values.
 */
typedef enum {
    THREATSEVERITY_HIDDEN,
    THREATSEVERITY_LOW,
    THREATSEVERITY_IMPORTANT,
    THREATSEVERITY_CRITICAL
} ZThreatSeverity;

__attribute__ ((visibility ("default")))

/**
 * ZDefendThreat contains all of the information needed to determine what threat was encountered.
 * There are also methods for retrieving the localized threat names and descriptions in human readable format.
 * See ZDeviceStatus.
 */
@interface ZDefendThreat : NSObject

/**
 * @property appName - the App name of an App threat. An empty string if the Label is not available.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull appName;

/**
 * @property attackTime - the date and time of the threat detection.
 */
@property (nonatomic, readonly, strong) NSDate *  _Nonnull attackTime;

/**
 * @property internalName - the internal threat name.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull internalName;

/**
 * @property internalThreatID - the internal threat ID.
 */
@property (nonatomic, readonly) int internalThreatID;

/**
 * @property isDeviceMitigated - true if the threat has been mitigated on the device.
 */
@property (nonatomic, readonly) bool isDeviceMitigated;

/**
 * @property isMitigated - true if the threat has been mitigated via the device or server.
 */
@property (nonatomic, readonly) bool isMitigated;

/**
 * @property isServerMitigated - true if a threat has been acknowledged via the console/server. This property allows determining if this threat
 * has been acknowledged on the console/server.
 */
@property (nonatomic, readonly) bool isServerMitigated;

/**
 * @property isSimulated - true if this threat is a simulated test threat.
 */
@property (nonatomic, readonly) bool isSimulated;

/**
 * @property json - the threat key/value pair set describing this threat.
 */
@property (nonatomic, readonly, strong) NSDictionary * _Nonnull json;

/**
 * @property localizedAlertButtonLink- the user configured alert button link. The alert button link can be configured in zConsole.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull localizedAlertButtonLink;

/**
 * @property localizedAlertButtonText - the user configured alert button string. The alert button string can be configured in zConsole.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull localizedAlertButtonText;

/**
 * @property localizedAlertText - the user configured alert string with HTML elements removed. The alert string can be configured in zConsole.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull localizedAlertText;

/**
 * @property localizedAlertTextHtml - the user configured alert string including HTML elements. The alert string can be configured in zConsole.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull localizedAlertTextHtml;

/**
 * @property localizedDetails - the localized (configurable) description of the attack with HTML elements removed.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull localizedDetails;

/**
 * @property localizedDetailsHtml - the localized (configurable) description of the attack including HTML elements.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull localizedDetailsHtml;

/**
 * @property localizedName - the localized name of the threat reported (example, "ARP MITM", "SSL STRIP", "TCP SCAN", etc).
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull localizedName;

/**
 * @property localizedResolution - the threat resolution message string with HTML elements removed.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull localizedResolution;

/**
 * @property localizedResolutionHtml - the threat resolution message string including HTML elements.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull localizedResolutionHtml;

/**
 * @property malwareFamily - the family name of the malware threat. An empty string if the Label is not available.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull malwareFamily;

/**
 *  @property malwareName - the name of the malware threat. An empty string if the Label is not available.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull malwareName;

/**
 * @property packageName - the App name of an App threat. An empty string if the Label is not available.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull packageName;

/**
 * @property profileName - the name of the suspicious profile threat. An empty string if the Label is not available.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull profileName;

/**
 * @property severity - the severity of the threat reported ("THREATSEVERITY_CRITICAL", "ITHREATSEVERITY_MPORTANT", "THREATSEVERITY_LOW").
 */
@property (nonatomic, readonly) ZThreatSeverity severity;

/**
 * @property nameForSeverity - convenience name of the threatSeverity value.
 */
@property (nonatomic, readonly) NSString * _Nonnull nameForSeverity;

/**
 * @property sideloadedAppDeveloper - the app developer for a sideloaded app threat. An empty string if the Label is not available.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull sideloadedAppDeveloper;

/**
 * @property SSID - the SSID of the access point when the attack was detected. Only present when the device was connected to a wifi network.
 * An empty string if the Label is not available.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull SSID;

/**
 * @property url - the URL of a web threat or an empty string for other threats.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull url;

/**
 * @property UUID - the unique threat UUID value. Each generated threat will have a unique UUID that can be used to identify the specific threat.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull UUID;

/**
 * @property vector - the threat vector description.
 *
 * @return the threat vector description string of the following possible values (new entries may be added dynamically):
 *   "DEVICE" - for device related threats
 *   "NETWORK" - for network related threats
 *   "APP" - for application related threats
 *   "WEB" - for URL scan and content inspection related threats
 *   "TRACKER" - for tracker related threats (e.g. AirTag)
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull vector;


/**
 * Get the threat debug description.
 *
 * @return the threat description string.
 */
- (NSString * _Nonnull)debugDescription;




/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see localizedAlertText
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull alertText DEPRECATED_ATTRIBUTE;

/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see localizedAlertTextHtml
*/
@property (nonatomic, readonly, strong) NSString * _Nonnull alertTextHtml DEPRECATED_ATTRIBUTE;

/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see localizedName
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull humanThreatName DEPRECATED_ATTRIBUTE;

/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see localizedDetails
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull humanThreatSummary DEPRECATED_ATTRIBUTE;

/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see localizedDetailsHtml
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull humanThreatSummaryHtml DEPRECATED_ATTRIBUTE;

/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see localizedName
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull humanThreatType DEPRECATED_ATTRIBUTE;

/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see isMitigated
 */
@property (nonatomic, readonly) bool mitigated DEPRECATED_ATTRIBUTE;

/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see json
 */
@property (nonatomic, readonly, strong) NSDictionary * _Nonnull threatJson DEPRECATED_ATTRIBUTE;

/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see localizedResolution
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull threatResolution DEPRECATED_ATTRIBUTE;

/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see severity
 */
@property (nonatomic, readonly) ZThreatSeverity threatSeverity DEPRECATED_ATTRIBUTE;

/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see nameForSeverity
 */
@property (nonatomic, readonly) NSString * _Nonnull nameForThreatSeverity DEPRECATED_ATTRIBUTE;

/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see UUID
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull threatUUID DEPRECATED_ATTRIBUTE;

/**
 * Deprecated - do not use. To be removed in future SDK.
 *
 * see vector
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull threatVector DEPRECATED_ATTRIBUTE;



@end


#endif /* ZDefendThreat__h */
