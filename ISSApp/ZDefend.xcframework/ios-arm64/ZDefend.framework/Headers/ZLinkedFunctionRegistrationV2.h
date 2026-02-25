//
//  ZLinkedFunctionRegistrationV2.h
//  ZLinkedFunctionRegistrationV2
//
//  Created by User on 04/17/2024
//  Copyright © 2024 Zimperium Inc. All rights reserved.
//

#ifndef ZLinkedFunctionRegistrationV2__h
#define ZLinkedFunctionRegistrationV2__h

#import <Foundation/Foundation.h>
#import <ZDefend/ZLinkedFunctionEvent.h>


/**
 * ZLinkedFunctionV2 is the interface for receiving linked function events.
 *
 * A class implementing this interface is required for receiving linked function events. See ZDefend#registerLinkedFunction for registering linked functions.
 *
 * @param event the linked function event..
 */
typedef void (^ZLinkedFunctionV2)(ZLinkedFunctionEvent * _Nonnull event);

__attribute__ ((visibility ("default")))

/**
 * The linked function registration object returned from ZDefend#registerLinkedFunction(String, ZLinkedFunctionV2, ZLinkedFunctionV2).
 * This object can be used to de-register this function when the linked function is no longer required.
 *
 */
@interface ZLinkedFunctionRegistrationV2 : NSObject

/**
 * @property linkedFunction - the ZLinkedFunctionV2 for this registration, null is returned after calling deregister().
 */
@property (nonatomic, readonly, strong) ZLinkedFunctionV2 _Nullable linkedFunction;

/**
 * @property mitigationFunction - the mitigation ZLinkedFunctionV2 for this registration, null is returned after calling deregister().
 */
@property (nonatomic, readonly, strong) ZLinkedFunctionV2 _Nullable mitigationFunction;

/**
 * @property label - the label this linked function was registered with.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull label;

/**
 * Remove this linked function registration.
 */
- (void)deregister;

@end


#endif /* ZLinkedFunctionRegistrationV2__h */

