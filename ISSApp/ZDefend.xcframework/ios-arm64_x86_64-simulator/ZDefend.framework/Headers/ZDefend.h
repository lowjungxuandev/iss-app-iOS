//
//  ZDefend.h
//  ZDefend
//
//  Created by User on 01/11/2023
//  Copyright © 2023 Zimperium Inc. All rights reserved.
//

#ifndef ZDefend__h
#define ZDefend__h

#import <ZDefend/ZDefendTypes.h>
#import <ZDefend/ZDeviceStatus.h>
#import <ZDefend/ZDeviceStatusRegistration.h>
#import <ZDefend/ZDeviceStatusJsonRegistration.h>
#import <ZDefend/ZLinkedFunctionRegistration.h>
#import <ZDefend/ZLinkedFunctionRegistrationV2.h>


 __attribute__ ((visibility ("default")))
/**
 * ZDefend is the main interface point for information and control.
 *
 * All requests and commands occur asynchronous and passing handlers is required to obtain status and details.
 */
@interface ZDefend : NSObject

/**
 * Register a handler that will be called for updates to the ZDefend device status.
 *
 * ZDeviceStatusRegistration#deregister must be called before the deviceStatusCallback goes out of scope.
 *
 * You will get the current ZDeviceStatusCallback immediately returned when adding the callback.
 *
 * Device status callbacks are asynchronous for the following events: login status change, new threats, mitigated threats, policy updates.
 *
 * @param callback - handler to be called for ZDefend device status updates. See ZDeviceStatusCallback.
 * @return the registration object that can be used for de-registering the handeler. See ZDeviceStatusRegistration.
 */
+ (ZDeviceStatusRegistration * _Nonnull)addDeviceStatusCallback:(ZDeviceStatusCallback _Nonnull)callback;

/**
 * Register a handler that will be called for updates to the ZDefend device status.
 * <p/>
 * Care must be taken not to leak activity contexts through this method. ZDeviceStatusRegistration#deregister() must be called before the deviceStatusCallback goes out of scope.
 * <p/>
 * You will get the current ZDeviceStatusJsonCallback immediately returned when adding the callback.
 * <p/>
 * Device status callbacks are asynchronous for the following events: login status change, new threats, mitigated threats, policy updates.
 * @param deviceStatusJsonCallback - handler to be called for ZDefend device status json updates. See ZDeviceStatusJsonCallback.
 * @return the registration object that can be used for de-registering the handler. See ZDeviceStatusJsonRegistration.
 */
+ (ZDeviceStatusJsonRegistration * _Nonnull)addDeviceStatusJsonCallback:(ZDeviceStatusJsonCallback _Nonnull)callback;


/**
 * Deprecated. Instead use registerLinkedFunction(NSString *, ZLinkedFunction, ZLinkedFunction).
 * Register a sdk linked function that will run when a linked function with the label string is triggered.
 * <p/>
 * Linked functions are triggered from ZDefend events, e.g. a new Threat. Registering a linked function allows
 * custom actions to execute for triggered events.
 * <p/>
 * @param label The linked function trigger label.
 * @param linkedFunction The custom action function to run for the triggered event.
 * @return the registration object that can be used for de-registering the linked function, see {@link ZLinkedFunctionRegistration}.
 */
+ (ZLinkedFunctionRegistration * _Nonnull)registerLinkedFunction:(NSString * _Nonnull)label function:(ZLinkedFunction _Nonnull)linkedFunction;

/**
 * Register a sdk linked function that will run when a linked function with the label string is triggered.
 * <p/>
 * Linked functions are triggered from ZDefend events, e.g. a new Threat. Registering a linked function allows
 * custom actions to execute for triggered events.
 * Each registered linked function is triggered only when a trigger event label matches the registered linked function label.
 * <p/>
 * The registered actionFunction will be called one-time only when the first trigger event with a matching label becomes active.
 * Later trigger events after the first will not invoke the actionFunction unless all trigger events with the matching label have
 * been mitigated. If there is an active trigger event with matching label at the time the liked function is registered, the
 * actionFunction will be immediately called.
 * <p/>
 * The registered mitigateFunction will be called one-time only after the mitigation of every trigger event with a matching label.
 * <p/>
 * @param label The linked function trigger label.
 * @param function The custom action function to run when a triggered event first becomes active.
 * @param mitigateFunction The custom action function to run for the triggered event.
 * @return the registration object that can be used for de-registering the linked function, see ZLinkedFunctionRegistrationV2.
 */
+ (ZLinkedFunctionRegistrationV2 * _Nonnull)registerLinkedFunction:(NSString * _Nonnull)label function:(ZLinkedFunctionV2 _Nonnull)function mitigateFunction:(ZLinkedFunctionV2 _Nonnull)mitigateFunction;

/**
 * Set tracking id tags for threats and device events.
 * Once id tags are set, they will be associated with device events and threats.
 * Setting an id to nil or empty string will remove the tracking ID.
 * <p/>
 * @param tag1 string
 * @param tag2 string
 * @throws NSException is thrown if any tracking ID length is greater than 128 characters.
 */
+ (void) setTrackingIds:(NSString* _Nullable)tag1 tag2:(NSString* _Nullable)tag2;

/**
 * Request the device check for ZDefend updates.
 *
 * The update check occurs asynchronous where any ZDefend updates will generate a ZDeviceStatusCallback. See ZDefend#addDeviceStatusCallback(ZDeviceStatusCallback}.
 */
+ (void)checkForUpdates;

/**
 * Set the SDK nonce string.
 * If the nonce string is set, the value will be included in the json details for all ZDeviceStatus events
 * with the json key "nonce". The nonce string can be cleared by setting an empty string.
 * After the nonce string is set with a non-empty value, a new ZDeviceStatus event will automatically be generated,
 * see ZDefend#addDeviceStatusCallback.
 * <p/>
 * @param nonceString the nonce string value or an empty string.
 */
+ (void)setNonce:(NSString *_Nonnull) nonceString;

/**
 * Set the SDK nonce string and register a device status json callback for this nonce.
 * The set nonce string will be included in the json details for all future ZDeviceStatus events
 * with the json key "nonce".
 * After the nonce string is set, a new ZDeviceStatus event will be generated and delivered via the callback.
 * <p/>
 * The provided callback will only be called for device status events that contain the set nonceString. If the nonceString is
 * later changed, then the future device status events will not be delivered to the callback.
 * @param nonceString the nonce string value.
 * @param cllback the device status json callback to deliver any device status with nonceString.
 * @return the registration object that can be used for de-registering the handler. See {@link ZDeviceStatusJsonRegistration}.
 * @throws NSException is nonString is empty.
 */
+ (ZDeviceStatusJsonRegistration * _Nonnull)setNonceWithCallback:(NSString *_Nonnull) nonceString callback:(ZDeviceStatusJsonCallback _Nonnull)callback;

@end


#endif /* ZDefend__h */
