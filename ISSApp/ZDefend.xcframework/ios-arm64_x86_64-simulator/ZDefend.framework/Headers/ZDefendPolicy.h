//
//  ZDefendPolicy.h
//  ZDefendPolicy
//
//  Created by User on 01/23/2023
//  Copyright © 2023 Zimperium Inc. All rights reserved.
//

#ifndef ZDefendPolicy__h
#define ZDefendPolicy__h

#import <Foundation/Foundation.h>


/**
 * The possible ZDefend policy types.
 */
typedef NS_ENUM(NSInteger, ZDefendPolicyType) {
    ZDEFENDPOLICY_APP_SETTINGS = 0,
    ZDEFENDPOLICY_PHISHING = 1,
    ZDEFENDPOLICY_PRIVACY = 2,
    ZDEFENDPOLICY_THREAT = 3
};

__attribute__ ((visibility ("default")))

/**
 * A ZDefend policy description.
 */
@interface ZDefendPolicy : NSObject

/**
 * @property policyType - the current policy type.
 */
@property (nonatomic, readonly) ZDefendPolicyType policyType;

/**
 * @property policyDownloadDate - the policy download date and time.
 */
@property (nonatomic, readonly, strong) NSDate * _Nonnull policyDownloadDate;

/**
 * @property policyHash - the policy hash value that uniquely identifies the policy.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull policyHash;

/**
 * @property policyName - the policy type name. See ZDefendPolicyType for possible policy types.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull policyName;


/**
 * @return the policy description string.
 */
- (NSString * _Nonnull)debugDescription;

@end


#endif /* ZDefendPolicy__h */
