//
//  ZDeviceStatusJsonRegistration.h
//  ZDeviceStatusJsonRegistration
//
//  Created by User on 04/01/2025
//  Copyright © 2025 Zimperium Inc. All rights reserved.
//

#ifndef ZDeviceStatusJsonRegistration__h
#define ZDeviceStatusJsonRegistration__h

#import <Foundation/Foundation.h>
#import <ZDefend/ZDeviceStatus.h>

__attribute__ ((visibility ("default")))

/**
 * The device status handler registration object returned from ZDefend#addDeviceStatusJsonCallback:ZDeviceStatusJsonCallback.
 *
 * This object can be used to de-register the handler when device status json updates are no longer required.
 *
 */
@interface ZDeviceStatusJsonRegistration : NSObject

/**
 *
 * @property callback -  the callback implementation block tracked by this registration. nil is returned after calling ZDeviceStatusJsonRegistration#deregister.
 */
@property (nonatomic, readonly, strong) ZDeviceStatusJsonCallback _Nullable callback;


/**
 * Remove the device status handler from receiving device status change events.
 */
- (void)deregister;


@end


#endif /* ZDeviceStatusJsonRegistration__h */
