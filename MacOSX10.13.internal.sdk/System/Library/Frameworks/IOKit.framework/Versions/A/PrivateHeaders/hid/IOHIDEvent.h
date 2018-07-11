/*
 * File:            IOKit.framework/PrivateHeaders/hid/IOHIDEvent.h
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

#ifndef _IOKIT_IOHIDEVENT_H /* guard */
#define _IOKIT_IOHIDEVENT_H /* guard */

/* [TODO]: TODOs for this header file are:
 *
 *   - The following TODOs are URGENT and this header should not be released
 *     until they have been completed:
 *
 *       - Finish the definition of IOHIDEventRef. (@libsystem_ethan)
 *       - Complete the implementations of the functions defined here in
 *         IOHIDEvent.c (@libsystem_ethan)
 *
 *   - Once the above URGENT TODOs have been completed, remove the "Empty
 *     header file" warning. (@libsystem_ethan)
 */

#include <IOKit/hid/IOHIDEventSystem.h>
#include <IOKit/hid/IOHIDEventTypes.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

typedef UInt32 IOHIDEventFlags;

typedef struct __IOHIDEvent {
    void    *empty;
} *IOHIDEventRef;

void                    IOHIDEventAppendEvent(IOHIDEventRef event, IOHIDEventRef tmpEvent, int unknown);
int                     IOHIDEventConformsTo(IOHIDEventRef event, IOHIDEventType type);
IOHIDEventRef           IOHIDEventCreate(CFAllocatorRef allocator, IOHIDEventType eventType, int empty1, int empty2);
IOHIDEventRef           IOHIDEventCreateBiometricEvent(CFAllocatorRef allocator, uint64_t mach_time, IOHIDBiometricEventType biometricEventType, float isDown, int empty1);
IOHIDEventRef           IOHIDEventCreateCopy(CFAllocatorRef allocator, IOHIDEventRef event);
CFDataRef               IOHIDEventCreateData(CFAllocatorRef allocator, IOHIDEventRef matching);
IOHIDEventRef           IOHIDEventCreateKeyboardEvent(CFAllocatorRef allocator, uint64_t mach_time, uint32_t usagePage, uint32_t usage, int empty1, int empty2);
IOHIDEventRef           IOHIDEventCreateVendorDefinedEvent(CFAllocatorRef allocator, uint64_t mach_time, uint32_t usagePage, uint32_t usage, int empty1, uint8_t *data, size_t data_size, int empty2);
IOHIDEventRef           IOHIDEventCreateWithBytes(CFAllocatorRef allocator, const UInt8 *data, UInt32 size);
IOHIDEventRef           IOHIDEventCreateWithData(CFAllocatorRef allocator, CFMutableDataRef data);
CFArrayRef              IOHIDEventGetChildren(IOHIDEventRef event);
IOHIDEventRef           IOHIDEventGetEvent(IOHIDEventRef event, IOHIDEventType eventType);
IOHIDEventFlags         IOHIDEventGetEventFlags(IOHIDEventRef event);
float                   IOHIDEventGetFloatValue(IOHIDEventRef event, IOHIDEventField field);
CFIndex                 IOHIDEventGetIntegerValue(IOHIDEventRef event, IOHIDEventField field);
IOHIDEventPhaseBits     IOHIDEventGetPhase(IOHIDEventRef event);
IOHIDEventPolicyValue   IOHIDEventGetPolicy(IOHIDEventRef event, IOHIDEventPolicyValue policyValue);
uint64_t                IOHIDEventGetTimeStamp(IOHIDEventRef event);
int                     IOHIDEventGetType(IOHIDEventRef event);
IOHIDEventSenderID      IOHIDEventGetSenderID(IOHIDEventRef event);
void                    IOHIDEventGetVendorDefinedData(IOHIDEventRef event, uint8_t **param1, CFIndex *eventLength);
CFBooleanRef            IOHIDEventIsAbsolute(IOHIDEventRef event);
void                    IOHIDEventSetEventFlags(IOHIDEventRef event, IOHIDEventFlags flags);
void                    IOHIDEventSetIntegerValue(IOHIDEventRef event, IOHIDEventField field, uint32_t value);
void                    IOHIDEventSetPhase(IOHIDEventRef event, IOHIDEventPhaseBits phase);
void                    IOHIDEventSetTimeStamp(IOHIDEventRef event, uint64_t mach_time);
CFBooleanRef            _IOHIDEventCopyAttachment(IOHIDEventRef event, CFStringRef attachment, int empty1);
void                    _IOHIDEventSetAttachment(IOHIDEventRef event, CFStringRef attachment, CFBooleanRef value, int empty1);
void                    _IOHIDEventRemoveAttachment(IOHIDEventRef event, CFStringRef attachment, int empty1);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */
    
#endif /* guard: _IOKIT_IOHIDEVENT_H */
