//
//  ZDeviceStatusRegistration.h
//  ZDeviceStatusRegistration
//
//  Created by User on 01/25/2023
//  Copyright © 2023 Zimperium Inc. All rights reserved.
//

#ifndef ZDeviceStatusRegistration__h
#define ZDeviceStatusRegistration__h

#import <Foundation/Foundation.h>
#import <ZDefend/ZDeviceStatus.h>

__attribute__ ((visibility ("default")))

/**
 * The device status handler registration object returned from ZDefend#addDeviceStatusCallback:ZDeviceStatusCallback.
 *
 * This object can be used to de-register the handler when device status updates are no longer required.
 *
 */
@interface ZDeviceStatusRegistration : NSObject

/**
 *
 * @property callback -  the callback implementation block tracked by this registration. nil is returned after calling ZDeviceStatusRegistration#deregister.
 */
@property (nonatomic, readonly, strong) ZDeviceStatusCallback _Nullable callback;


/**
 * Remove the device status handler from receiving device status change events.
 */
- (void)deregister;


@end


#endif /* ZDeviceStatusRegistration__h */
