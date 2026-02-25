//
//  ZDefendUrlClassificationResult.h
//  ZDefendUrlClassificationResult
//
//  Created by User on 06/12/2023
//  Copyright © 2023 Zimperium Inc. All rights reserved.
//

#ifndef ZDefendUrlClassificationResult__h
#define ZDefendUrlClassificationResult__h

#import <Foundation/Foundation.h>
#import <ZDefend/ZDefendThreat.h>
#import <ZDefend/ZDefendTypes.h>

__attribute__ ((visibility ("default")))

/**
 * The result from the ZDefend URL classificationrequest. See ZDefendUrlClassificationResultCallback.
 */
@interface ZDefendUrlClassificationResult : NSObject

/**
 * @property url - the url requsted for this result.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull url;

/**
 * @property threat - the result threat details. All unsafe results will include classification threat details. See ZDefendThreat.
 *
 * nil when the ZDefendUrlClassificationResult#isSafe is false, the threat details object when ZDefendUrlClassificationResult#isSafe is true.
 */
@property (nonatomic, readonly, strong) ZDefendThreat * _Nullable threat;

/**
 * @property contentInspectionMode - the content inspection mode for this status.
 */
@property (nonatomic, readonly) ZContentInspectionMode contentInspectionMode;

/**
 * @property nameForContentInspectionMode - convenience property for contentInspectionMode description.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull nameForContentInspectionMode;

/**
 * @property isPhishing - if this ZDefend URL Classification result is classified as phishing.
 *
 * true only if the classification result is a phishing classification,
 *  or false when the result is safe or {@link #getContentInspectionMode()} is not PHISHING.
 */
@property (nonatomic, readonly) bool isPhishing;

/**
 * The content filtering category of the ZDefend URL classification result or empty string if the result is safe or {@link #getContentInspectionMode()} is not CONTENT_FILTERING.
 */
@property (nonatomic, readonly, strong) NSString * _Nonnull contentCategory;


/**
 * @property isSafe - the result safety. Any unsafe result will have threat details available, see ZDefendUrlClassificationResult#getThreat.
 *      true for result that is determined safe
 *      false for a result that was identified as phishing or content filtered.
 */
@property (nonatomic, readonly) bool isSafe;


- (id _Nonnull)initWithUrl:(NSString * _Nonnull)url Threat:(ZDefendThreat * _Nullable)threat;

/**
 * Get the result debug description.
 *
 * @return the result debug description string.
 */
- (NSString * _Nonnull)debugDescription;


@end

/**
 * ZDefendUrlClassificationResultCallback is the handler block for receiving the results from a URL classification request, see ZDefendUrlClassification#classifyUrl.
 *
 * A class implementing this interface is required for receiving the URL classification results.
 *
 * @param classifyUrlResult The URL classification results.
 * @param error Any error exceptions that occurred processing the URL classification. nil is returned for no errors.
 */
typedef void (^ZDefendUrlClassificationCallback)(ZDefendUrlClassificationResult * _Nonnull classifyUrlResult, NSError * _Nullable error);


#endif /* ZDefendUrlClassificationResult__h */

