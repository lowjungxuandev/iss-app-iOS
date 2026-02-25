//
//  ZLinkedFunctionEvent.h
//  ZLinkedFunctionEvent
//
//  Created by User on 04/17/2024
//  Copyright © 2024 Zimperium Inc. All rights reserved.
//

#ifndef ZLinkedFunctionEvent__h
#define ZLinkedFunctionEvent__h

#import <Foundation/Foundation.h>
#import <ZDefend/ZDeviceStatus.h>
#import <ZDefend/ZDefendThreat.h>

/**
 * ZLinkedFunctionEvent is a class representing the a triggered linked function event. These events are passed to registered
 * linked function callbacks when a linked function event is triggered.
 * See ZDefend#registerLinkedFunction(String, ZLinkedFunctionV2, ZLinkedFunctionV2) for registering linked functions.
 */

/**
 * The possible event types for a ZLinkedFunctionEvent.
 */
typedef NS_ENUM(NSInteger, ZLinkedFunctionEventType) {
    /**
     * The event is a new activated linked function.
      */
    ACTIVATED_LINKED_FUNCTION = 0,
    /**
     * The event is the mitigation of a previous active linked function.
      */
    MITIGATED_LINKED_FUNCTION = 1
};

__attribute__ ((visibility ("default")))

/**
 * The linked function registration object returned from ZDefend#registerLinkedFunction.
 *
 * This object can be used to de-register this function when the linked function is no longer required.
 *
 */
@interface ZLinkedFunctionEvent : NSObject

/**
 * @property label - the label for this ZLinkedFunction event.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull label;

/**
 * @property eventType - the ZLinkedFunctionEventType for this ZLinkedFunction event.
 */
@property (nonatomic, readonly) ZLinkedFunctionEventType eventType;

/**
 * @property deviceStatus - the ZDeviceStatus for when this ZLinkedFunction event was generated.
 */
@property (nonatomic, readonly, strong) ZDeviceStatus * _Nonnull deviceStatus;

/**
 * @property relatedThreats - the list of related threats for this ZLinkedFunction event.
 */
@property (nonatomic, readonly, strong) NSArray<ZDefendThreat *> * _Nonnull relatedThreats;

@end


#endif /* ZLinkedFunctionEvent__h */

