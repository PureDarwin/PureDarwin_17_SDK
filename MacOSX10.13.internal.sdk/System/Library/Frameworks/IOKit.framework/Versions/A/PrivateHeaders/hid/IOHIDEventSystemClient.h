/*
 * File:            IOKit.framework/PrivateHeaders/hid/IOHIDEventSystemClient.h
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

#ifndef _IOKIT_IOHIDEVENTSYSTEMCLIENT_H /* guard */
#define _IOKIT_IOHIDEVENTSYSTEMCLIENT_H /* guard */

/* [TODO]: TODOs for this header file are:
 *
 *   - The following TODOs are URGENT and this header should not be released
 *     until they have been completed:
 *
 *       - Finish the definitiion of IOHIDEventSystemClientRef.
 *         (@libsystem_ethan)
 *
 *   - Once the above URGENT TODOs have been completed, remove the "Empty
 *     header file" warning. (@libsystem_ethan)
 */

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/hid/IOHIDServiceClient.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

typedef struct __IOHIDEventSystemClient {
    void    *empty;
} *IOHIDEventSystemClientRef;

enum IOHIDEventSystemClientType {
    kIOHIDEventSystemClientTypePassive,
    kIOHIDEventSystemClientTypeMonitor,
};

CFTypeRef                   IOHIDEventSystemClientCopyProperty(IOHIDEventSystemClientRef client,
                                                               CFStringRef key);
IOHIDServiceClientRef       IOHIDEventSystemClientCopyServiceForRegistryID(IOHIDEventSystemClientRef client,
                                                                           uint64_t entryID);
CFArrayRef                  IOHIDEventSystemClientCopyServices(IOHIDEventSystemClientRef client);
IOHIDEventSystemClientRef   IOHIDEventSystemClientCreateWithType(CFAllocatorRef allocator,
                                                                 enum IOHIDEventSystemClientType type,
                                                                 void *empty);
void                        IOHIDEventSystemClientSetProperty(IOHIDEventSystemClientRef client,
                                                              CFStringRef key,
                                                              CFTypeRef parameter);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* guard: _IOKIT_IOHIDEVENTSYSTEMCLIENT_H */
