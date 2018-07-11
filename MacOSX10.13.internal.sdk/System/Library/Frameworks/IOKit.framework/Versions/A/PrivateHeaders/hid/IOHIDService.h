/*
 * File:            IOKit.framework/PrivateHeaders/hid/IOHIDService.h
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

#ifndef _IOKIT_IOHIDSERVICE_H /* guard */
#define _IOKIT_IOHIDSERVICE_H /* guard */

#include <CoreFoundation/CFPlugInCOM.h>
#include <IOKIt/IOTypes.h>
#include <IOKit/hid/IOHIDDevice.h>
#include <IOKit/hid/IOHIDEvent.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

/* 00000000-0000-0000-0000-000000000000 */
#define kIOHIDServicePlugInTypeID           CFUUIDGetConstantUUIDWithBytes(NULL, \
        0x00, 0x00, 0x00, 0x00,                                                  \
        /* - */ 0x00, 0x00,                                                      \
        /* - */ 0x00, 0x00,                                                      \
        /* - */ 0x00, 0x00,                                                      \
        /* - */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

/* 00000000-0000-0000-0000-000000000000 */
#define kIOHIDServiceFastPathPlugInTypeID   CFUUIDGetConstantUUIDWithBytes(NULL, \
        0x00, 0x00, 0x00, 0x00,                                                  \
        /* - */ 0x00, 0x00,                                                      \
        /* - */ 0x00, 0x00,                                                      \
        /* - */ 0x00, 0x00,                                                      \
        /* - */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

/* 00000000-0000-0000-0000-000000000000 */
#define kIOHIDServiceFastPathInterfaceID    CFUUIDGetConstantUUIDWithBytes(NULL, \
        0x00, 0x00, 0x00, 0x00,                                                  \
        /* - */ 0x00, 0x00,                                                      \
        /* - */ 0x00, 0x00,                                                      \
        /* - */ 0x00, 0x00,                                                      \
        /* - */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

/* 00000000-0000-0000-0000-000000000000 */
#define kIOHIDServiceInterface2ID           CFUUIDGetConstantUUIDWithBytes(NULL, \
        0x00, 0x00, 0x00, 0x00,                                                  \
        /* - */ 0x00, 0x00,                                                      \
        /* - */ 0x00, 0x00,                                                      \
        /* - */ 0x00, 0x00,                                                      \
        /* - */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)

typedef struct __IOHIDService {
    void*   empty;
} *IOHIDServiceRef;

Boolean     IOHIDServiceConformsTo(IOHIDServiceRef service, uint32_t usagePage, uint32_t usage);
CFTypeRef   IOHIDServiceGetProperty(IOHIDServiceRef service, CFStringRef property);
CFTypeRef   IOHIDServiceCopyProperty(IOHIDServiceRef service, CFStringRef property);
CFTypeRef   IOHIDServiceGetRegistryID(IOHIDServiceRef service);
void        IOHIDServiceSetElementValue(IOHIDServiceRef service, int page, int pageUsage, boolean_t value);
void        IOHIDServiceSetProperty(IOHIDServiceRef service, CFStringRef property, CFTypeRef value);

typedef void (*IOHIDServiceEventCallback)(void *target,
                                          void *refcon,
                                          void *sender,
                                          IOHIDEventRef event,
                                          IOOptionBits options);

typedef struct {
    void            *empty;
    HRESULT         (*genericQueryInterface)(void *self, REFIID iid, void **ppv);
    UInt32          (*genericAddRef)(void *self);
    UInt32          (*genericRelease)(void *self);
    boolean_t       (*_open)(void *self, IOOptionBits options);
    void            (*_close)(void *self, IOOptionBits options);
    CFTypeRef       (*_copyProperty)(void *self, CFStringRef key);
    boolean_t       (*_setProperty)(void *self, CFStringRef key, CFTypeRef property);
    void            (*_setEventCallback)(void *self, IOHIDServiceEventCallback callback, void * target, void * refcon);
    void            (*_scheduleWithDispatchQueue)(void *self, dispatch_queue_t queue);
    void            (*_unscheduleFromDispatchQueue)(void *self, dispatch_queue_t queue);
    IOHIDEventRef   (*_copyEvent)(void *self, IOHIDEventType type, IOHIDEventRef matching, IOOptionBits options);
    IOReturn        (*_setOutputEvent)(void *self, IOHIDEventRef event);
} IOHIDServiceInterface2;

typedef struct {
    void            *empty;
    HRESULT         (*genericQueryInterface)(void *self, REFIID iid, void **ppv);
    UInt32          (*genericAddRef)(void *self);
    UInt32          (*genericRelease)(void *self);
    boolean_t       (*_open)(void *self, IOOptionBits options, CFDictionaryRef property);
    void            (*_close)(void *self, IOOptionBits options);
    CFTypeRef       (*_copyProperty)(void *self, CFStringRef key);
    boolean_t       (*_setProperty)(void *self, CFStringRef key, CFTypeRef property);
    IOHIDEventRef   (*_copyEvent)(void *self, CFTypeRef copySpec, IOOptionBits options);
} IOHIDServiceFastPathInterface;

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* guard: _IOKIT_IOHIDSERVICE_H */

