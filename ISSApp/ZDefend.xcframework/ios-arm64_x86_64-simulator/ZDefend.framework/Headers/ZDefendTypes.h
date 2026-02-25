//
//  ZDefendTpes.h
//  ZDefendTypes
//
//  Created by User on 01/11/2023
//  Copyright © 2023 Zimperium Inc. All rights reserved.
//

#ifndef ZDefendTypes__h
#define ZDefendTypes__h

#import <Foundation/Foundation.h>

/**
 *  The possible login status returned from ZDeviceStatus#loginStatus.
 */
typedef NS_ENUM(NSInteger, ZLoginStatus) {
    LOGGED_OUT = 0,
    LOGGED_IN = 1,
    LOGIN_IN_PROGRESS = 2
};

/**
 *  The possible last login error values returned from ZDeviceStatus#lastLoginError.
 */
typedef NS_ENUM(NSInteger, ZLoginError) {
    LOGIN_ERROR_NONE = 0,
    LOGIN_ERROR_CLIENT_ERROR = 1,
    LOGIN_ERROR_LICENSE_EXPIRED = 2,
    LOGIN_ERROR_LICENSE_INVALID = 3,
    LOGIN_ERROR_CONNECTION_ERROR = 4,
    LOGIN_ERROR_LICENSE_LIMITED = 5,
    LOGIN_ERROR_SERVER_ERROR = 6
};

/**
 *  The possible content inspection modes returned from ZDefend#getContentInspectionMode).
 */
typedef NS_ENUM(NSInteger, ZContentInspectionMode) {
    MODE_PHISHING = 0,
    MODE_CONTENT_FILTERING = 1
};

/**
 * The possible setRuleLevel values, see ZDefendDeveloper#setRuleLevel.
 */
typedef NS_ENUM(NSInteger, ZDefendRuleLevel) {
    ZRULELEVEL_BETA = 0,
    ZRULELEVEL_PRODUCTION = 1
};


/**
 * Type possilbe ZDeviceStatus compression type values, see ZDeviceStatus#setCompressionType.
 */
typedef NS_ENUM(NSInteger, ZDeviceStatusCompressionType) {
    COMPRESSION_TYPE_NONE = 0,
    COMPRESSION_TYPE_DEFLATE = 1 /* zlib deflate compression */
};


#endif /* ZDefendTypes__h */
