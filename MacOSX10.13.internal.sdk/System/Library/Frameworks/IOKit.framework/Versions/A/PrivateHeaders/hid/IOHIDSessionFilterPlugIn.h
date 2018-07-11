/*
 * File:            IOKit.framework/PrivateHeaders/hid/IOHIDSessionFilterPlugIn.h
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

#ifndef _IOKIT_IOHIDSESSIONFILTERPLUGIN_H /* guard */
#define _IOKIT_IOHIDSESSIONFILTERPLUGIN_H /* guard */

#include <dispatch/dispatch.h>
#include <CoreFoundation/CFPlugInCOM.h>
#include <IOKit/hid/IOHIDEvent.h>
#include <IOKit/hid/IOHIDService.h>
#include <IOKit/hid/IOHIDSession.h>
#include <IOKit/hidsystem/IOHIDShared.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/* 00000000-0000-0000-0000-000000000000 */
#define kIOHIDSessionFilterPlugInTypeID CFUUIDGetConstantUUIDWithBytes(NULL, \
    0x00, 0x00, 0x00, 0x00,                     \
    /* - */ 0x00, 0x00,                         \
    /* - */ 0x00, 0x00,                         \
    /* - */ 0x00, 0x00,                         \
    /* - */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

/* 00000000-0000-0000-0000-000000000000 */
#define kIOHIDSessionFilterPlugInInterfaceID CFUUIDGetConstantUUIDWithBytes(NULL, \
    0x00, 0x00, 0x00, 0x00,                     \
    /* - */ 0x00, 0x00,                         \
    /* - */ 0x00, 0x00,                         \
    /* - */ 0x00, 0x00,                         \
    /* - */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

/* 00000000-0000-0000-0000-000000000000 */
#define kIOHIDSimpleSessionFilterPlugInInterfaceID CFUUIDGetConstantUUIDWithBytes(NULL, \
    0x00, 0x00, 0x00, 0x00,                     \
    /* - */ 0x00, 0x00,                         \
    /* - */ 0x00, 0x00,                         \
    /* - */ 0x00, 0x00,                         \
    /* - */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

#define kIOHIDDFRKeyboardEventFilterEnabledKey          "DFRKeyboardEventFilterEnabled"
#define kIOHIDDFRTouchIDEventFilterEnabledKey           "DFRTouchIDEventFilterEnabled"
#define kIOHIDDFREventFilterKeyboardCancelThreshold     "DFREventFilterKeyboardCancelThreshold"
#define kIOHIDDFREventFilterDFRTouchCancelThreshold     "DFREventFilterDFRTouchCancelThreshold"
#define kIOHIDDFREventFilterBiometricCancelThreshold    "DFREventFilterBiometricCancelThreshold"
#define kIOHIDSessionFilterDebugKey                     "SessionFilterDebug"

typedef struct {
    void            (*COMPadding)(void);
    HRESULT         (*QueryInterface)(void *self, REFIID iid, LPVOID *ppv);
    ULONG           (*AddRef)(void *self);
    ULONG           (*Release)(void *self);
    IOHIDEventRef   (*filter)(void *self, IOHIDServiceRef sender, IOHIDEventRef event);
    void            (*empty1)(void);
    void            (*empty2)(void);
    boolean_t       (*open)(void *self, IOHIDSessionRef session, IOOptionBits options);
    void            (*close)(void *self, IOHIDSessionRef session, IOOptionBits options);
    void            (*empty3)(void);
    void            (*empty4)(void);
    void            (*registerService)(void *self, IOHIDServiceRef service);
    void            (*unregisterService)(void *self, IOHIDServiceRef service);
    void            (*scheduleWithDispatchQueue)(void *self, dispatch_queue_t queue);
    void            (*unscheduleFromDispatchQueue)(void *self, dispatch_queue_t queue);
    CFTypeRef       (*getPropertyForClient)(void *self, CFStringRef key, CFTypeRef client);
    void            (*setPropertyForClient)(void *self, CFStringRef key, CFTypeRef property, CFTypeRef client);
} IOHIDSessionFilterPlugInInterface;

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* guard: _IOKIT_IOHIDSESSIONFILTERPLUGIN_H */
