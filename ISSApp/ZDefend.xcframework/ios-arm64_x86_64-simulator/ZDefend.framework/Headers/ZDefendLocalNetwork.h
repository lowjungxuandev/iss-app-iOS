//
//  ZDefendLocalNetwork.h
//  ZDefendLocalNetwork
//
//  Created by User on 2020/09/20.
//  Copyright © 2023 Zimperium Inc. All rights reserved.
//


#import <Foundation/Foundation.h>

/**
 * The possible local network permission results.
 * See ZDefend#hasLocalNetworkAuthorization.
 */
typedef NS_ENUM(NSInteger, ZLocalNetworkAuthorizationType) {
    ZLOCALNETWORK_AUTHORIZATION_NOT_ASKED = 0,
    ZLOCALNETWORK_AUTHORIZATION_DENIED = 1,
    ZLOCALNETWORK_AUTHORIZATION_ALLOWED = 2,
};


NS_ASSUME_NONNULL_BEGIN

__attribute__ ((visibility ("default")))

@interface ZDefendLocalNetwork : NSObject

/**
 * Query if the user has granted local network permission for this application.
 * @param callback to deliver authorization result, see ZLocalNetworkAuthorizationType.
 * throws NSException if  NSLocalNetworkUsageDescription key is missing from app Info plist.
 */
+ (void) hasLocalNetworkAuthorization:(void (^_Nonnull)(ZLocalNetworkAuthorizationType authorization))callback;

/**
 * Request the local network permission popup from iOS which may prompt the user for this application permission.
 * @param callback The callback to return the request result, see ZLocalNetworkAuthorizationType.
 * throws NSException if  NSLocalNetworkUsageDescription key is missing from app Info plist.
 */
+ (void) requestLocalNetworkAuthorizationFromUser:(void (^_Nonnull)(ZLocalNetworkAuthorizationType authorization))callback;




@end

NS_ASSUME_NONNULL_END

