//
//  ZDefendDeveloper.h
//  ZDefendDeveloper
//
//  Created by User on 02/01/2023
//  Copyright © 2023 Zimperium Inc. All rights reserved.
//


#ifndef ZDefendDeveloper__h
#define ZDefendDeveloper__h

#import <ZDefend/ZDefendTypes.h>
#import <ZDefend/ZLinkedFunctionRegistrationV2.h>

 __attribute__ ((visibility ("default")))
/**
 * ZDefendDeveloper is the developer assist api to aid in development and debugging.
 *
 */
@interface ZDefendDeveloper : NSObject

/**
 * Simulate a threat for testing. Refer to ZDefend documentation for details.
 * 
 * @param threatId the threat identifier to simulate.
 * @param forensics the threat forensic details.
 */
+ (void)simulateTestThreat:(int) threatId forensics:(NSDictionary * _Nullable) forensics;

/**
 * Remove all active simulated test threats.
 */
+ (void)mitigateSimulatedThreats;

/**
 * Set the rule run level to production or beta rules. This developer API allows testing using beta
 * run rules. Setting the rule level is persistent across application restarts.
 *
 * @param level the rule level to in effect.
 */
+ (void)setRuleLevel:(ZDefendRuleLevel) level;

/**
 * Get the currently registered linked functions.
 *
 * @param callback to receive the list of currently registered linked functions.
 */
+ (void)getRegisteredLinkedFunctions:(void (^_Nonnull)(NSArray<ZLinkedFunctionRegistrationV2 *> * _Nonnull))callback;



@end


#endif /* ZDefendDeveloper__h */
