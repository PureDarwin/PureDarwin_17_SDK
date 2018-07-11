/*
 * File:            IOKit.framework/PrivateHeaders/hid/IOHIDEventQueue.h
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

#ifndef _IOKIT_IOHIDEVENTQUEUE_H /* guard */
#define _IOKIT_IOHIDEVENTQUEUE_H /* guard */

/* [TODO]: TODOs for this header file are:
 *
 *   - The following TODOs are URGENT and this header should not be released
 *     until they have been completed:
 *
 *       - Finish the definition of IOHIDEventQueueRef. (@libsystem_ethan)
 *       - Complete the implementations of the functions defined here in
 *         IOHIDEvent.c (@libsystem_ethan)
 *
 *   - Once the above URGENT TODOs have been completed, remove the "Empty
 *     header file" warning. (@libsystem_ethan)
 */

#include <IOKit/hid/IOHIDEvent.h>
#include <IOKit/hidsystem/IOHIDShared.h>
#include <mach/port.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

typedef struct __IOHIDEventQueue {
    void    *empty;
} *IOHIDEventQueueRef;

IOHIDEventQueueRef  IOHIDEventQueueCreate(CFAllocatorRef allocator, int eventQueueType, int empty1, int empty2);
IOHIDEventRef       IOHIDEventQueueDequeueCopy(IOHIDEventQueueRef queue);
void                IOHIDEventQueueSetNotificationPort(IOHIDEventQueueRef queue, mach_port_t port);
void                IOHIDEventQueueStart(IOHIDEventQueueRef queue);
void                IOHIDEventQueueStop(IOHIDEventQueueRef queue);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* guard: _IOKIT_IOHIDEVENTQUEUE_H */

