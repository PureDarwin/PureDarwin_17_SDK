/*
 * Copyright (c) 2017 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
#ifndef   __COPYOUT_SHIM_X86_64_H__
#define   __COPYOUT_SHIM_X86_64_H__

// Osfmk includes libsa/types.h which causes massive conflicts
// with sys/types.h
#if defined (__i386__) || defined(__x86_64__)
#include "i386/types.h"
#elif defined (__arm__) || defined (__arm64__)
//XXX when ready to turn on for arm: #include "arm/types.h"
#error ARM/ARM64 not supported
#else
#error architecture not supported
#endif

#include <mach/mach_types.h>

#define CO_SRC_NORMAL 1       //copyout() called
#define CO_SRC_MSG    (1<<1)    //copyoutmsg() called
#define CO_SRC_PHYS   (1<<2)    //copyio(COPYOUTPHYS,...) called

typedef void (*copyout_shim_fn_t)(const void *,user_addr_t,vm_size_t,unsigned co_src);



kern_return_t
register_copyout_shim(copyout_shim_fn_t copyout_shim_fn,unsigned co_src_flags);


#define unregister_copyout_shim() register_copyout_shim(NULL,0)

void *
cos_kernel_unslide(const void *);

void *
cos_kernel_reslide(const void *);

#endif /* __COPYOUT_SHIM_X86_64_H__ */
