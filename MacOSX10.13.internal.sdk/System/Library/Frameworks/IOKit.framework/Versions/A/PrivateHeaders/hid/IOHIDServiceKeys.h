/*
 * File:            IOKit.framework/PrivateHeaders/hid/IOHIDServiceKeys.h
 * Project:         IOKitUser
 *
 * Author:          @libsystem_ethan
 * Organisation:    PureDarwin
 *
 * License:         Simplified BSD License
 * License Text:    Copyright (C) 2018 Ethan Sherriff
 *
 *                  Redistribution and use in source and binary forms, with or
 *                  without modification, are permitted provided that the
 *                  following conditions are met:
 *
 *                      1. Redistributions of source code must retain the above
 *                         copyright notice, this list of conditions and the
 *                         following disclaimer.
 *                      2. Redistributions in binary form must reproduce the
 *                         above copyright notice, this list of conditions and
 *                         the following disclaimer in the documentation and/or
 *                         other materials provided with the distribution.
 *
 *                  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *                  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *                  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *                  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *                  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *                  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *                  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *                  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *                  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *                  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *                  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *                  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 *                  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *                  POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _IOKIT_IOHIDSERVICEKEYS_H /* guard */
#define _IOKIT_IOHIDSERVICEKEYS_H /* guard */

#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/* IOHIDService Keys */
//#define kIOHIDServicePlugInDebugKey             "PlugInDebug"
#define kIOHIDServicePluginDebugKey             "PluginDebug"
#define kIOHIDServiceSlowKeysDelayKey           "SlowKeysDelay"
#define kIOHIDServiceCapsLockDelayKey           "CapsLockDelay"
#define kIOHIDServiceCapsLockStateKey           "CapsLockState"
#define kIOHIDServiceCapsLockLEDKey             "CapsLockLED"
#define kIOHIDServiceCapsLockLEDKey_Off         CFSTR("CapsLockLED_Off")
#define kIOHIDServiceCapsLockLEDKey_Inhibit     CFSTR("CapsLockLED_Inhibit")
#define kIOHIDServiceCapsLockLEDKey_On          CFSTR("CapsLockLED_On")
#define kIOHIDServiceCapsLockLEDInhibitKey      "CapsLockLEDInhibit"
#define kIOHIDServiceCapsLockLEDKey_Auto        kIOHIDServiceCapsLockLEDKey_Off
#define kIOHIDServiceDeviceUsagePairsKey        "DeviceUsagePairs"
#define kIOHIDServiceNumLockStateKey            "NumLockState"
#define kIOHIDServiceModifierMappingDstKey      "ModifierMappingDst"
#define kIOHIDServiceModifierMappingPairsKey    "ModifierMappingPairs"
#define kIOHIDServiceModifierMappingSrcKey      "ModifierMappingSrc"
#define kIOHIDServiceStickyKeysDisabledKey      "StickyKeysDisabled"
#define kIOHIDServiceStickyKeysOnKey            "StickyKeysOn"
#define kIOHIDServiceStickyKeysShiftTogglesKey  "StickyKeysShiftToggles"
#define kIOHIDServicePrimaryUsageKey            "PrimaryUsage"
#define kIOHIDServicePrimaryUsagePageKey        "PrimaryUsagePage"

/* IOHIDServiceFilterKeys */
#define kIOHIDServiceFilterDebugKey             "FilterDebug"

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* guard: _IOKIT_IOHIDSERVICEKEYS_H */
