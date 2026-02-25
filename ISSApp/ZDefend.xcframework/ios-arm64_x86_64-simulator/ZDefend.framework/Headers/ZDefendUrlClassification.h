//
//  ZDefendUrlClassification.h
//  ZDefendUrlClassification
//
//  Created by User on 06/12/2023
//  Copyright © 2023 Zimperium Inc. All rights reserved.
//


#ifndef ZDefendUrlClassification__h
#define ZDefendUrlClassification__h

#import <ZDefend/ZDefendUrlClassificationResult.h>

 __attribute__ ((visibility ("default")))
/**
 * The ZDefend URL Classification API.
 */
@interface ZDefendUrlClassification : NSObject

/**
 * Request a URL classification for phishing or content-filtering.
 *
 * The URL classification will asynchronously verify the passed URL and provide the scan result to the provided callback.
 *
 * URL classification results determined as phishing or filtered will additionally trigger a web threat.
 *
 * @param url - The url to be classified, e.g. https://zimperium.com
 * @param callback - handler to be called asynchronously to delver the classification result. See ZDefendUrlClassificationResultCallback.
 * @throws NSException - for non web URL strings, e.g. the URL scheme is missing, not http or not https.
 */
+ (void) classifyUrl:(NSString * _Nonnull)url withCallback:(ZDefendUrlClassificationCallback _Nonnull)callback;


/**
 * Mitigate all active web threats.
 *
 * Mitigation is an asynchronous action. Any mitigated web threats will generate a ZDeviceStatusCallback with the updated web threat.
 */
+ (void) mitigateWebThreats;

@end


#endif /* ZDefendUrlClassification__h */

