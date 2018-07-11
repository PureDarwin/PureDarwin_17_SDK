/*
 * Copyright (C) 2014-2016 Apple Inc. All rights reserved.
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

#include <WebKit/WKPreferencesRefPrivate.h>

#ifdef __OBJC__

#import <WebKit/WKPreferences.h>

#if WK_API_ENABLED

typedef NS_ENUM(NSInteger, _WKStorageBlockingPolicy) {
    _WKStorageBlockingPolicyAllowAll,
    _WKStorageBlockingPolicyBlockThirdParty,
    _WKStorageBlockingPolicyBlockAll,
} API_AVAILABLE(macosx(10.10), ios(8.0));

typedef NS_OPTIONS(NSUInteger, _WKDebugOverlayRegions) {
    _WKNonFastScrollableRegion = 1 << 0,
    _WKWheelEventHandlerRegion = 1 << 1
} API_AVAILABLE(macosx(10.11), ios(9.0));

typedef NS_OPTIONS(NSUInteger, _WKJavaScriptRuntimeFlags) {
    _WKJavaScriptRuntimeFlagsAllEnabled = 0
} API_AVAILABLE(macosx(10.11), ios(9.0));

@class _WKExperimentalFeature;

@interface WKPreferences (WKPrivate)

// FIXME: This property should not have the verb "is" in it.
@property (nonatomic, setter=_setTelephoneNumberDetectionIsEnabled:) BOOL _telephoneNumberDetectionIsEnabled;
@property (nonatomic, setter=_setStorageBlockingPolicy:) _WKStorageBlockingPolicy _storageBlockingPolicy;

@property (nonatomic, setter=_setCompositingBordersVisible:) BOOL _compositingBordersVisible;
@property (nonatomic, setter=_setCompositingRepaintCountersVisible:) BOOL _compositingRepaintCountersVisible;
@property (nonatomic, setter=_setTiledScrollingIndicatorVisible:) BOOL _tiledScrollingIndicatorVisible;
@property (nonatomic, setter=_setResourceUsageOverlayVisible:) BOOL _resourceUsageOverlayVisible API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setVisibleDebugOverlayRegions:) _WKDebugOverlayRegions _visibleDebugOverlayRegions API_AVAILABLE(macosx(10.11), ios(9.0));
@property (nonatomic, setter=_setSimpleLineLayoutEnabled:) BOOL _simpleLineLayoutEnabled API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setSimpleLineLayoutDebugBordersEnabled:) BOOL _simpleLineLayoutDebugBordersEnabled API_AVAILABLE(macosx(10.11), ios(9.0));
@property (nonatomic, setter=_setAcceleratedDrawingEnabled:) BOOL _acceleratedDrawingEnabled API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setDisplayListDrawingEnabled:) BOOL _displayListDrawingEnabled API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setVisualViewportEnabled:) BOOL _visualViewportEnabled API_AVAILABLE(macosx(10.12.3), ios(10.3));
@property (nonatomic, setter=_setLargeImageAsyncDecodingEnabled:) BOOL _largeImageAsyncDecodingEnabled API_AVAILABLE(macosx(10.12.3), ios(10.3));
@property (nonatomic, setter=_setAnimatedImageAsyncDecodingEnabled:) BOOL _animatedImageAsyncDecodingEnabled API_AVAILABLE(macosx(10.12.3), ios(10.3));
@property (nonatomic, setter=_setTextAutosizingEnabled:) BOOL _textAutosizingEnabled API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setSubpixelAntialiasedLayerTextEnabled:) BOOL _subpixelAntialiasedLayerTextEnabled API_AVAILABLE(macosx(10.12), ios(10.0));

@property (nonatomic, setter=_setDeveloperExtrasEnabled:) BOOL _developerExtrasEnabled API_AVAILABLE(macosx(10.11), ios(9.0));

@property (nonatomic, setter=_setLogsPageMessagesToSystemConsoleEnabled:) BOOL _logsPageMessagesToSystemConsoleEnabled API_AVAILABLE(macosx(10.11), ios(9.0));

@property (nonatomic, setter=_setHiddenPageDOMTimerThrottlingEnabled:) BOOL _hiddenPageDOMTimerThrottlingEnabled API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setHiddenPageDOMTimerThrottlingAutoIncreases:) BOOL _hiddenPageDOMTimerThrottlingAutoIncreases API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setPageVisibilityBasedProcessSuppressionEnabled:) BOOL _pageVisibilityBasedProcessSuppressionEnabled API_AVAILABLE(macosx(10.12), ios(10.0));

@property (nonatomic, setter=_setAllowFileAccessFromFileURLs:) BOOL _allowFileAccessFromFileURLs API_AVAILABLE(macosx(10.11), ios(9.0));
@property (nonatomic, setter=_setJavaScriptRuntimeFlags:) _WKJavaScriptRuntimeFlags _javaScriptRuntimeFlags API_AVAILABLE(macosx(10.11), ios(9.0));

@property (nonatomic, setter=_setStandalone:, getter=_isStandalone) BOOL _standalone API_AVAILABLE(macosx(10.11), ios(9.0));

@property (nonatomic, setter=_setDiagnosticLoggingEnabled:) BOOL _diagnosticLoggingEnabled API_AVAILABLE(macosx(10.11), ios(9.0));

@property (nonatomic, setter=_setDefaultFontSize:) NSUInteger _defaultFontSize API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, setter=_setDefaultFixedPitchFontSize:) NSUInteger _defaultFixedPitchFontSize API_AVAILABLE(macosx(10.12), ios(10.0));
@property (nonatomic, copy, setter=_setFixedPitchFontFamily:) NSString *_fixedPitchFontFamily API_AVAILABLE(macosx(10.12), ios(10.0));

// FIXME: This should be configured on the WKWebsiteDataStore.
// FIXME: This property should not have the verb "is" in it.
@property (nonatomic, setter=_setOfflineApplicationCacheIsEnabled:) BOOL _offlineApplicationCacheIsEnabled;
@property (nonatomic, setter=_setFullScreenEnabled:) BOOL _fullScreenEnabled API_AVAILABLE(macosx(10.11), ios(9.0));
@property (nonatomic, setter=_setShouldSuppressKeyboardInputDuringProvisionalNavigation:) BOOL _shouldSuppressKeyboardInputDuringProvisionalNavigation API_AVAILABLE(macosx(10.12.3), ios(10.3));
@property (nonatomic, setter=_setAllowsPictureInPictureMediaPlayback:) BOOL _allowsPictureInPictureMediaPlayback API_AVAILABLE(macosx(10.13), ios(NA));

@property (nonatomic, setter=_setApplePayCapabilityDisclosureAllowed:) BOOL _applePayCapabilityDisclosureAllowed API_AVAILABLE(macosx(10.12), ios(10.0));

@property (nonatomic, setter=_setLoadsImagesAutomatically:) BOOL _loadsImagesAutomatically API_AVAILABLE(macosx(10.13), ios(NA));

@property (nonatomic, setter=_setMediaDevicesEnabled:) BOOL _mediaDevicesEnabled API_AVAILABLE(macosx(10.13), ios(NA));
@property (nonatomic, setter=_setMockCaptureDevicesEnabled:) BOOL _mockCaptureDevicesEnabled API_AVAILABLE(macosx(10.13), ios(NA));
@property (nonatomic, setter=_setMediaCaptureRequiresSecureConnection:) BOOL _mediaCaptureRequiresSecureConnection API_AVAILABLE(macosx(10.13), ios(NA));
@property (nonatomic, setter=_setEnumeratingAllNetworkInterfacesEnabled:) BOOL _enumeratingAllNetworkInterfacesEnabled API_AVAILABLE(macosx(10.13), ios(NA));
@property (nonatomic, setter=_setICECandidateFilteringEnabled:) BOOL _iceCandidateFiltertingEnabled API_AVAILABLE(macosx(10.13), ios(NA));
@property (nonatomic, setter=_setWebRTCLegacyAPIEnabled:) BOOL _webRTCLegacyAPIEnabled API_AVAILABLE(macosx(10.13), ios(NA));

@property (nonatomic, setter=_setJavaScriptCanAccessClipboard:) BOOL _javaScriptCanAccessClipboard API_AVAILABLE(macosx(10.13), ios(NA));
@property (nonatomic, setter=_setDOMPasteAllowed:) BOOL _domPasteAllowed API_AVAILABLE(macosx(10.13), ios(NA));

@property (nonatomic, setter=_setMediaDocumentEntersFullscreenAutomatically:) BOOL _mediaDocumentEntersFullscreenAutomatically API_AVAILABLE(macosx(10.13), ios(NA));

+ (NSArray<_WKExperimentalFeature *> *)_experimentalFeatures API_AVAILABLE(macosx(10.12), ios(10.0));
- (BOOL)_isEnabledForFeature:(_WKExperimentalFeature *)feature API_AVAILABLE(macosx(10.12), ios(10.0));
- (void)_setEnabled:(BOOL)value forFeature:(_WKExperimentalFeature *)feature API_AVAILABLE(macosx(10.12), ios(10.0));

@end

#endif

#endif
