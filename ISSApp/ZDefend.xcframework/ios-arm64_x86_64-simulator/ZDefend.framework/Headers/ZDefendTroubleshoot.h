//
//  ZDefendTroubleshoot.h
//  ZDefendTroubleshoot
//
//  Created by User on 06/12/2023
//  Copyright © 2023 Zimperium Inc. All rights reserved.
//

#ifndef ZDefendTroubleshoot__h
#define ZDefendTroubleshoot__h

#import <Foundation/Foundation.h>



/**
 * The possible request types for ZDefend#getZLog.
 * Use ZLOG_ALL to request all log messages.
 */
typedef NS_ENUM(NSInteger, ZLogType) {
    ZLOG_ALL = -1,
    ZLOG_NORMAL = 0,
    ZLOG_PHISHING = 1,
    ZLOG_VPN = 2,
    ZLOG_RULE_STATE = 3,
    ZLOG_RULE_DOWNLOAD = 4,
    ZLOG_RULE_RUN = 5
};


/**
 * ZDefendTroubleshootDetailsCallback is the handler for receiving the troubleshoot details get request.
 *
 * A block implementing this interface is required for receiving device status updates. See ZDefendTroubleshoot#getTroubleshootDetails.
 *
 * @param troubleshootDetails - the key/value pair set of details.
 */
typedef void (^ZDefendTroubleshootDetailsCallback)(NSDictionary<NSString*,NSObject*> * _Nonnull troubleshootDetails);

/**
 * ZLogCallback is the handler for receiving the results from ZDefend#getLogs.
 *
 * A class implementing this interface is required for receiving the get logs events.
 *
 * @param messages the log messages for the requested type.
 */
typedef void (^ZLogCallback)(NSString * _Nonnull messages);

/**
 * ZLogCallback is the handler for receiving the results from ZDefend#getLogs.
 *
 * A class implementing this interface is required for receiving the get logs events.
 *
 * @param messages the log messages for the requested type.
 * @param requestType the type of logs requested, use ZLOG_ALL to request all logs, see ZLogType.
 */
typedef void (^ZLogTypeCallback)(NSString * _Nonnull messages, ZLogType requestType);


__attribute__ ((visibility ("default")))
/**
 * ZDefendTroubleshoot is the troubleshooting api to aid in development and debugging.
 */
@interface ZDefendTroubleshoot : NSObject

/**
 * Request the device details to assist in troubleshooting.
 *
 * The device troubleshoot details request will asynchronously provide the details to the provided callback.
 *
 * @param callback - handler to be called asynchronously to deliver the troubleshoot details. See ZDefendTroubleshootDetailsCallback.
 */
+ (void)getTroubleshootDetails:(ZDefendTroubleshootDetailsCallback _Nonnull)callback;

/**
 * Request the current NORMAL device ZLog contents.
 *
 * The device logs request will asynchronously provide the logs to the provided callback.
 *
 * @param callback - handler to be called asynchronously to deliver device logs. See ZLogCallback.
 */
+ (void)getZLog:(ZLogCallback _Nonnull)callback;


/**
 * Request the current device ZLog contents for a specific ZLog type.
 *
 * The device logs request will asynchronously provide the logs to the provided callback.
 *
 * @param callback - handler to be called asynchronously to deliver device logs. See ZLogCallback.
 * @param requestType the type of logs requested, use ZLOG_ALL to request all logs, see ZLogType.
 */
+ (void)getZLog:(ZLogTypeCallback _Nonnull)callback type:(ZLogType) requestType;

@end




#endif /* ZDefendTroubleshoot__h */
