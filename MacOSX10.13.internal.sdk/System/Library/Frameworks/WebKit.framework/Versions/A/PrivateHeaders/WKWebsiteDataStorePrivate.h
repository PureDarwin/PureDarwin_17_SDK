/*
 * Copyright (C) 2016-2017 Apple Inc. All rights reserved.
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

#import <WebKit/WKWebsiteDataStore.h>

#if WK_API_ENABLED

NS_ASSUME_NONNULL_BEGIN

@class _WKWebsiteDataStoreConfiguration;

typedef NS_OPTIONS(NSUInteger, _WKWebsiteDataStoreFetchOptions) {
    _WKWebsiteDataStoreFetchOptionComputeSizes = 1 << 0,
} API_AVAILABLE(macosx(10.12), ios(10.0));

@interface WKWebsiteDataStore (WKPrivate)

+ (NSSet<NSString *> *)_allWebsiteDataTypesIncludingPrivate;

- (instancetype)_initWithConfiguration:(_WKWebsiteDataStoreConfiguration *)configuration API_AVAILABLE(macosx(10.13), ios(NA));

- (void)_fetchDataRecordsOfTypes:(NSSet<NSString *> *)dataTypes withOptions:(_WKWebsiteDataStoreFetchOptions)options completionHandler:(void (^)(NSArray<WKWebsiteDataRecord *> *))completionHandler;

@property (nonatomic, setter=_setResourceLoadStatisticsEnabled:) BOOL _resourceLoadStatisticsEnabled API_AVAILABLE(macosx(10.12), ios(10.0));

// ResourceLoadStatistics SPI for testing.
- (void)_resourceLoadStatisticsSetLastSeen:(double)seconds forHost:(NSString *)host API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetIsPrevalentResource:(BOOL)value forHost:(NSString *)host API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsIsPrevalentResource:(NSString *)host completionHandler:(void (^)(BOOL))completionHandler API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsIsRegisteredAsSubFrameUnder:(NSString *)subFrameHost topFrameHost:(NSString *)topFrameHost completionHandler:(void (^)(BOOL))completionHandler API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsIsRegisteredAsRedirectingTo:(NSString *)hostRedirectedFrom hostRedirectedTo:(NSString *)hostRedirectedTo completionHandler:(void (^)(BOOL))completionHandler API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetHadUserInteraction:(BOOL)value forHost:(NSString *)host API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsHadUserInteraction:(NSString *)host completionHandler:(void (^)(BOOL))completionHandler API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetIsGrandfathered:(BOOL)value forHost:(NSString *)host API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsIsGrandfathered:(NSString *)host completionHandler:(void (^)(BOOL))completionHandler API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetSubframeUnderTopFrameOrigin:(NSString *)topFrameHostName forHost:(NSString *)host API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetSubresourceUnderTopFrameOrigin:(NSString *)topFrameHostName forHost:(NSString *)host API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetSubresourceUniqueRedirectTo:(NSString *)hostNameRedirectedTo forHost:(NSString *)host API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetTimeToLiveUserInteraction:(double)seconds API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetTimeToLiveCookiePartitionFree:(double)seconds API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetMinimumTimeBetweenDataRecordsRemoval:(double)seconds API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetGrandfatheringTime:(double)seconds API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetMaxStatisticsEntries:(size_t)entries API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetPruneEntriesDownTo:(size_t)entries API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsProcessStatisticsAndDataRecords API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsUpdateCookiePartitioning API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetShouldPartitionCookies:(BOOL)value forHost:(NSString *)host API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSubmitTelemetry API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetNotifyPagesWhenDataRecordsWereScanned:(BOOL)value API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetShouldClassifyResourcesBeforeDataRecordsRemoval:(BOOL)value API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetNotifyPagesWhenTelemetryWasCaptured:(BOOL)value API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsSetShouldSubmitTelemetry:(BOOL)value API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsClearInMemoryAndPersistentStore API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsClearInMemoryAndPersistentStoreModifiedSinceHours:(unsigned)hours API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_resourceLoadStatisticsResetToConsistentState API_AVAILABLE(macosx(10.13), ios(NA));
- (void)_setResourceLoadStatisticsTestingCallback:(nullable void (^)(WKWebsiteDataStore *, NSString *))callback;

@end

NS_ASSUME_NONNULL_END

#endif
