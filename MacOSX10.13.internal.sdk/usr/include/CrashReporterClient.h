/*
 * Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/***********************************************************************
 * Not to be installed in /usr/local/include                           *
 ***********************************************************************/

#ifndef _LIBC_CRASHREPORTERCLIENT_H
#define _LIBC_CRASHREPORTERCLIENT_H

#ifndef APPLE_OPEN_SOURCE_ENABLE_LIBCRASHREPORTERCLIENT

#include <stdint.h>

#pragma message("Disabling CrashReporterClient")

/* Fake the CrashReporterClient API */
#define CRGetCrashLogMessage() 0 /* CRGetCrashLogMessage() isn't available because CrashReporterClient is not open source */
#define CRSetCrashLogMessage(x) /* CRSetCrashLogMessage(x) isn't available because CrashReporterClient is not open source */
#define CRSetCrashLogMessage2(x) /* CRSetCrashLogMessage2(x) isn't available because CrashReporterClient is not open source */

/* Taken from cups-450/cups/backend/usb-darwin.c  *
 * Thank you github.com/samdmarshall for your     *
 * OSXPrivateSDK project from which I found this. */

#define _crc_make_setter(attr, arg) (gCRAnnotations.attr = (uint64_t)(unsigned long)(arg))
#define CRASH_REPORTER_CLIENT_HIDDEN __attribute__((visibility("hidden")))
#define CRASHREPORTER_ANNOTATIONS_VERSION 4
#define CRASHREPORTER_ANNOTATIONS_SECTION "__crash_info"

struct crashreporter_annotations_t {
        uint64_t version;               // unsigned long
        uint64_t message;               // char *
        uint64_t signature_string;      // char *
        uint64_t backtrace;             // char *
        uint64_t message2;              // char *
        uint64_t thread;                // uint64_t
        uint64_t dialog_mode;           // unsigned int
};

/* CRASH_REPORTER_CLIENT_HIDDEN
 * struct crashreporter_annotations_t gCRAnnotations
 *         __attribute__((section("__DATA," CRASHREPORTER_ANNOTATIONS_SECTION)))
 *         = { CRASHREPORTER_ANNOTATIONS_VERSION, 0, 0, 0, 0, 0, 0 };
 */

#else /* APPLE_OPEN_SOURCE_ENABLE_LIBCRASHREPORTERCLIENT */

/* Include the real CrashReporterClient.h */
#include_next <CrashReporterClient.h>

#endif /* !APPLE_OPEN_SOURCE_ENABLE_LIBCRASHREPORTERCLIENT */

#endif /* _LIBC_CRASHREPORTERCLIENT_H */
