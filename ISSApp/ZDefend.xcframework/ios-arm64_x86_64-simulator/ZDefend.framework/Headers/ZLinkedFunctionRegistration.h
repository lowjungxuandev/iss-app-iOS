//
//  ZLinkedFunctionRegistration.h
//  ZLinkedFunctionRegistration
//
//  Created by User on 05/17/2023
//  Copyright © 2023 Zimperium Inc. All rights reserved.
//

#ifndef ZLinkedFunctionRegistration__h
#define ZLinkedFunctionRegistration__h

#import <Foundation/Foundation.h>
#import <ZDefend/ZDeviceStatus.h>


/**
 * ZLinkedFunction is the interface for receiving linked function events.
 *
 * A class implementing this interface is required for receiving linked function events. See ZDefend#registerLinkedFunction for registering linked functions.
 *
 * @param label the linked function register label.
 * @param threat the threat that triggered the linked function, or null when not triggered by a threat.
 */
typedef void (^ZLinkedFunction)(NSString * _Nonnull label, ZDefendThreat * _Nullable threat);

__attribute__ ((visibility ("default")))

/**
 * The linked function registration object returned from ZDefend#registerLinkedFunction.
 *
 * This object can be used to de-register this function when the linked function is no longer required.
 *
 */
@interface ZLinkedFunctionRegistration : NSObject

/**
 * @property callback -  the linked function implementation tracked by this registration. null is returned after calling deregister().
 */
@property (nonatomic, readonly, strong) ZLinkedFunction _Nullable linkedFunction;

/**
 * @property label - the label this linked function was registered with.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull label;

/**
 * Remove this linked function registration.
 */
- (void)deregister;

@end


#endif /* ZLinkedFunctionRegistrationn__h */
