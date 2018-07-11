/*
 * Copyright (C) 2014, 2015 Apple Inc. All rights reserved.
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

#import <WebKit/WKWebViewConfiguration.h>

#if WK_API_ENABLED

#if TARGET_OS_IPHONE
typedef NS_ENUM(NSUInteger, _WKDragLiftDelay) {
    _WKDragLiftDelayShort = 0,
    _WKDragLiftDelayMedium,
    _WKDragLiftDelayLong
} API_AVAILABLE(ios(NA));
#endif

@class WKWebView;
@class _WKVisitedLinkStore;
@class _WKWebsiteDataStore;

@interface WKWebViewConfiguration (WKPrivate)

@property (nonatomic, weak, setter=_setRelatedWebView:) WKWebView *_relatedWebView;
@property (nonatomic, copy, setter=_setGroupIdentifier:) NSString *_groupIdentifier;

@property (nonatomic, strong, setter=_setVisitedLinkStore:) _WKVisitedLinkStore *_visitedLinkStore;

@property (nonatomic, weak, setter=_setAlternateWebViewForNavigationGestures:) WKWebView *_alternateWebViewForNavigationGestures;

@property (nonatomic, setter=_setTreatsSHA1SignedCertificatesAsInsecure:) BOOL _treatsSHA1SignedCertificatesAsInsecure API_AVAILABLE(ios(9_0));

@property (nonatomic, setter=_setRespectsImageOrientation:) BOOL _respectsImageOrientation API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setPrintsBackgrounds:) BOOL _printsBackgrounds API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setIncrementalRenderingSuppressionTimeout:) NSTimeInterval _incrementalRenderingSuppressionTimeout API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setAllowsJavaScriptMarkup:) BOOL _allowsJavaScriptMarkup API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setConvertsPositionStyleOnCopy:) BOOL _convertsPositionStyleOnCopy API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setAllowsMetaRefresh:) BOOL _allowsMetaRefresh API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setAllowUniversalAccessFromFileURLs:) BOOL _allowUniversalAccessFromFileURLs API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setNeedsStorageAccessFromFileURLsQuirk:) BOOL _needsStorageAccessFromFileURLsQuirk API_AVAILABLE(macosx(10.12.3), ios(10.3));
@property (nonatomic, setter=_setMainContentUserGestureOverrideEnabled:) BOOL _mainContentUserGestureOverrideEnabled API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setInvisibleAutoplayNotPermitted:) BOOL _invisibleAutoplayNotPermitted API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setMediaDataLoadsAutomatically:) BOOL _mediaDataLoadsAutomatically API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setAttachmentElementEnabled:) BOOL _attachmentElementEnabled API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setInitialCapitalizationEnabled:) BOOL _initialCapitalizationEnabled API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setApplePayEnabled:) BOOL _applePayEnabled API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setWaitsForPaintAfterViewDidMoveToWindow:) BOOL _waitsForPaintAfterViewDidMoveToWindow API_AVAILABLE(macosx(10.12.3), ios(10.3));
@property (nonatomic, setter=_setControlledByAutomation:, getter=_isControlledByAutomation) BOOL _controlledByAutomation API_AVAILABLE(macosx(10.12.3), ios(10.3));

#if TARGET_OS_IPHONE
@property (nonatomic, setter=_setAlwaysRunsAtForegroundPriority:) BOOL _alwaysRunsAtForegroundPriority API_AVAILABLE(ios(9_0));
@property (nonatomic, setter=_setInlineMediaPlaybackRequiresPlaysInlineAttribute:) BOOL _inlineMediaPlaybackRequiresPlaysInlineAttribute API_AVAILABLE(ios(10.0));
@property (nonatomic, setter=_setAllowsInlineMediaPlaybackAfterFullscreen:) BOOL _allowsInlineMediaPlaybackAfterFullscreen  API_AVAILABLE(ios(10.0));
@property (nonatomic, setter=_setAllowsBlockSelection:) BOOL _allowsBlockSelection API_AVAILABLE(ios(NA));
@property (nonatomic, setter=_setDragLiftDelay:) _WKDragLiftDelay _dragLiftDelay API_AVAILABLE(ios(NA));
#else
@property (nonatomic, setter=_setShowsURLsInToolTips:) BOOL _showsURLsInToolTips API_AVAILABLE(macosx(10.12));
@property (nonatomic, setter=_setServiceControlsEnabled:) BOOL _serviceControlsEnabled API_AVAILABLE(macosx(10.12));
@property (nonatomic, setter=_setImageControlsEnabled:) BOOL _imageControlsEnabled API_AVAILABLE(macosx(10.12));
@property (nonatomic, readwrite, setter=_setRequiresUserActionForEditingControlsManager:) BOOL _requiresUserActionForEditingControlsManager API_AVAILABLE(macosx(10.12));
#endif

@property (nonatomic, strong, setter=_setWebsiteDataStore:) _WKWebsiteDataStore *_websiteDataStore API_DEPRECATED_WITH_REPLACEMENT("websiteDataStore", macosx(10.10, 10.11), ios(8.0, 9.0));
@property (nonatomic, setter=_setRequiresUserActionForAudioPlayback:) BOOL _requiresUserActionForAudioPlayback API_DEPRECATED_WITH_REPLACEMENT("mediaTypesRequiringUserActionForPlayback", macosx(10.12, 10.12), ios(10.0, 10.0));
@property (nonatomic, setter=_setRequiresUserActionForVideoPlayback:) BOOL _requiresUserActionForVideoPlayback API_DEPRECATED_WITH_REPLACEMENT("mediaTypesRequiringUserActionForPlayback", macosx(10.12, 10.12), ios(10.0, 10.0));

@property (nonatomic, setter=_setOverrideContentSecurityPolicy:) NSString *_overrideContentSecurityPolicy API_AVAILABLE(macosx(10.12.3), ios(10.3));
@property (nonatomic, setter=_setMediaContentTypesRequiringHardwareSupport:) NSString *_mediaContentTypesRequiringHardwareSupport API_AVAILABLE(macosx(10.13), ios(NA));
@property (nonatomic, setter=_setLegacyEncryptedMediaAPIEnabled:) BOOL _legacyEncryptedMediaAPIEnabled API_AVAILABLE(macosx(10.13), ios(NA));
@property (nonatomic, setter=_setAllowMediaContentTypesRequiringHardwareSupportAsFallback:) BOOL _allowMediaContentTypesRequiringHardwareSupportAsFallback API_AVAILABLE(macosx(10.13), ios(NA));

@end

#endif
