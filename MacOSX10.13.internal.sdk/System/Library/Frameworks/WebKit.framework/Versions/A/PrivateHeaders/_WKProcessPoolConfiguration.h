/*
 * Copyright (C) 2014 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Foundation/Foundation.h>
#import <WebKit/WKFoundation.h>

#if WK_API_ENABLED

NS_ASSUME_NONNULL_BEGIN

WK_EXTERN API_AVAILABLE(macosx(10.10), ios(8.0))
@interface _WKProcessPoolConfiguration : NSObject <NSCopying>

@property (nonatomic, copy) NSURL *injectedBundleURL;
@property (nonatomic) NSUInteger maximumProcessCount;

@property (nonatomic) BOOL ignoreSynchronousMessagingTimeoutsForTesting API_AVAILABLE(macosx(10.12), ios(10.0));

@property (nonatomic, copy) NSArray<NSURL *> *additionalReadAccessAllowedURLs API_AVAILABLE(macosx(10.13), ios(NA));

// Network Process properties
// FIXME: These should be be per-session/data store when we support multiple non-persistent sessions/data stores.

@property (nonatomic) NSInteger diskCacheSizeOverride API_AVAILABLE(macosx(10.11), ios(9.0));
@property (nonatomic, copy) NSArray *cachePartitionedURLSchemes;
@property (nonatomic, copy) NSArray<NSString *> *alwaysRevalidatedURLSchemes API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic) BOOL diskCacheSpeculativeValidationEnabled API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, nullable, copy) NSString *sourceApplicationBundleIdentifier API_AVAILABLE(macosx(10.12.3), ios(10.3));
@property (nonatomic, nullable, copy) NSString *sourceApplicationSecondaryIdentifier API_AVAILABLE(macosx(10.12.3), ios(10.3));
@property (nonatomic) BOOL allowsCellularAccess API_AVAILABLE(macosx(10.13), ios(NA));
@property (nonatomic) BOOL shouldCaptureAudioInUIProcess API_AVAILABLE(macosx(10.13), ios(NA));
#if TARGET_OS_IPHONE
@property (nonatomic, nullable, copy) NSString *CTDataConnectionServiceType API_AVAILABLE(ios(10.3));
@property (nonatomic) BOOL alwaysRunsAtBackgroundPriority API_AVAILABLE(ios(10.3));
@property (nonatomic) BOOL shouldTakeUIBackgroundAssertion API_AVAILABLE(ios(NA));
#endif
@property (nonatomic) pid_t presentingApplicationPID API_AVAILABLE(macosx(10.13), ios(NA));

@end

NS_ASSUME_NONNULL_END

#endif
