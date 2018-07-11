/*
 * Copyright (c) 2000-2009 Apple Inc. All rights reserved.
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
/*
 * @OSF_COPYRIGHT@
 */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 */
/*
 *	File:	vm/vm_pageout.h
 *	Author:	Avadis Tevanian, Jr.
 *	Date:	1986
 *
 *	Declarations for the pageout daemon interface.
 */

#ifndef	_VM_VM_PAGEOUT_H_
#define _VM_VM_PAGEOUT_H_


#include <mach/mach_types.h>
#include <mach/boolean.h>
#include <mach/machine/vm_types.h>
#include <mach/memory_object_types.h>

#include <kern/kern_types.h>
#include <kern/locks.h>

#include <libkern/OSAtomic.h>


#include <vm/vm_options.h>


#include <sys/kdebug.h>

#define VM_PAGE_AVAILABLE_COUNT()		((unsigned int)(vm_page_cleaned_count))

/* externally manipulated counters */
extern unsigned int vm_pageout_cleaned_reactivated, vm_pageout_cleaned_fault_reactivated, vm_pageout_cleaned_commit_reactivated;

#if CONFIG_FREEZE
extern boolean_t memorystatus_freeze_enabled;
#endif

#define VM_DYNAMIC_PAGING_ENABLED() (VM_CONFIG_COMPRESSOR_IS_ACTIVE)

#if VM_PRESSURE_EVENTS
extern boolean_t vm_pressure_events_enabled;
#endif /* VM_PRESSURE_EVENTS */


/*
 * the following codes are used in the DBG_MACH_WORKINGSET subclass
 * of the DBG_MACH class
 */
#define	VM_DISCONNECT_ALL_PAGE_MAPPINGS		0x00
#define VM_DISCONNECT_TASK_PAGE_MAPPINGS	0x01
#define VM_REAL_FAULT_ADDR_INTERNAL		0x02
#define VM_REAL_FAULT_ADDR_PURGABLE		0x03
#define VM_REAL_FAULT_ADDR_EXTERNAL		0x04
#define VM_REAL_FAULT_ADDR_SHAREDCACHE		0x05



extern int	vm_debug_events;

#define VMF_CHECK_ZFDELAY		0x100
#define VMF_COWDELAY			0x101
#define VMF_ZFDELAY			0x102
#define VMF_COMPRESSORDELAY		0x103

#define VM_PAGEOUT_SCAN			0x104
#define VM_PAGEOUT_BALANCE		0x105
#define VM_PAGEOUT_FREELIST		0x106
#define VM_PAGEOUT_PURGEONE		0x107
#define VM_PAGEOUT_CACHE_EVICT		0x108
#define VM_PAGEOUT_THREAD_BLOCK		0x109
#define VM_PAGEOUT_JETSAM		0x10A
#define VM_INFO1                        0x10B
#define VM_INFO2                        0x10C
#define VM_INFO3                        0x10D
#define VM_INFO4                        0x10E
#define VM_INFO5                        0x10F
#define VM_INFO6                        0x110
#define VM_INFO7                        0x111

#define VM_UPL_PAGE_WAIT		0x120
#define VM_IOPL_PAGE_WAIT		0x121
#define VM_PAGE_WAIT_BLOCK		0x122

#if CONFIG_IOSCHED
#define VM_PAGE_SLEEP			0x123
#define VM_PAGE_EXPEDITE		0x124
#define VM_PAGE_EXPEDITE_NO_MEMORY      0x125
#endif

#define VM_PRESSURE_EVENT		0x130
#define VM_EXECVE			0x131
#define VM_WAKEUP_COMPACTOR_SWAPPER	0x132

#define VM_DATA_WRITE 			0x140

#define VM_DEBUG_EVENT(name, event, control, arg1, arg2, arg3, arg4)	\
	MACRO_BEGIN						\
	if (vm_debug_events) {					\
		KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, event)) | control, arg1, arg2, arg3, arg4, 0); \
	}							\
	MACRO_END

#define VM_DEBUG_CONSTANT_EVENT(name, event, control, arg1, arg2, arg3, arg4)	\
	MACRO_BEGIN						\
		KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, event)) | control, arg1, arg2, arg3, arg4, 0); \
	MACRO_END

extern void memoryshot(unsigned int event, unsigned int control);

extern void update_vm_info(void);

#if CONFIG_IOSCHED
extern int upl_get_cached_tier(
       upl_t                   upl);
#endif

extern ppnum_t upl_get_highest_page(
	upl_t			upl);

extern upl_size_t upl_get_size(
	upl_t			upl);

extern upl_t upl_associated_upl(upl_t upl);
extern void upl_set_associated_upl(upl_t upl, upl_t associated_upl);


extern struct vnode * upl_lookup_vnode(upl_t upl);

typedef struct vm_page	*vm_page_t;

extern void                vm_page_free_list(
                            vm_page_t	mem,
                            boolean_t	prepare_object);

extern kern_return_t      vm_page_alloc_list(
                            int         page_count,
                            int			flags,
                            vm_page_t * list);

extern void               vm_page_set_offset(vm_page_t page, vm_object_offset_t offset);
extern vm_object_offset_t vm_page_get_offset(vm_page_t page);
extern ppnum_t            vm_page_get_phys_page(vm_page_t page);
extern vm_page_t          vm_page_get_next(vm_page_t page);

extern kern_return_t	mach_vm_pressure_level_monitor(boolean_t wait_for_pressure, unsigned int *pressure_level);

#if !CONFIG_EMBEDDED
extern kern_return_t 	vm_pageout_wait(uint64_t deadline);
#endif


#if UPL_DEBUG
extern kern_return_t  upl_ubc_alias_set(
	upl_t upl,
	uintptr_t alias1,
	uintptr_t alias2);
extern int  upl_ubc_alias_get(
	upl_t upl,
	uintptr_t * al,
	uintptr_t * al2);
#endif /* UPL_DEBUG */

extern void vm_countdirtypages(void);

extern void vm_backing_store_disable(
			boolean_t	suspend);

extern kern_return_t upl_transpose(
	upl_t	upl1,
	upl_t	upl2);

extern kern_return_t mach_vm_pressure_monitor(
	boolean_t	wait_for_pressure,
	unsigned int	nsecs_monitored,
	unsigned int	*pages_reclaimed_p,
	unsigned int	*pages_wanted_p);

extern kern_return_t
vm_set_buffer_cleanup_callout(
	boolean_t	(*func)(int));

struct vm_page_stats_reusable {
	SInt32		reusable_count;
	uint64_t	reusable;
	uint64_t	reused;
	uint64_t	reused_wire;
	uint64_t	reused_remove;
	uint64_t	all_reusable_calls;
	uint64_t	partial_reusable_calls;
	uint64_t	all_reuse_calls;
	uint64_t	partial_reuse_calls;
	uint64_t	reusable_pages_success;
	uint64_t	reusable_pages_failure;
	uint64_t	reusable_pages_shared;
	uint64_t	reuse_pages_success;
	uint64_t	reuse_pages_failure;
	uint64_t	can_reuse_success;
	uint64_t	can_reuse_failure;
	uint64_t	reusable_reclaimed;
	uint64_t	reusable_nonwritable;
	uint64_t	reusable_shared;
	uint64_t	free_shared;
};
extern struct vm_page_stats_reusable vm_page_stats_reusable;
	
extern int hibernate_flush_memory(void);
extern void hibernate_reset_stats(void);
extern void hibernate_create_paddr_map(void);

extern void vm_set_restrictions(void);

extern int vm_compressor_mode;
extern int vm_compressor_thread_count;
extern boolean_t vm_restricted_to_single_processor;
extern kern_return_t vm_pageout_compress_page(void **, char *, vm_page_t, boolean_t);
extern void vm_pageout_anonymous_pages(void);
extern void vm_pageout_disconnect_all_pages(void);


struct	vm_config {
	boolean_t	compressor_is_present;		/* compressor is initialized and can be used by the freezer, the sweep or the pager */
	boolean_t	compressor_is_active;		/* pager can actively compress pages...  'compressor_is_present' must be set */
	boolean_t	swap_is_present;		/* swap is initialized and can be used by the freezer, the sweep or the pager */
	boolean_t	swap_is_active;			/* pager can actively swap out compressed segments... 'swap_is_present' must be set */
	boolean_t	freezer_swap_is_active;		/* freezer can swap out frozen tasks... "compressor_is_present + swap_is_present" must be set */
};

extern	struct vm_config	vm_config;


#define	VM_PAGER_NOT_CONFIGURED				0x0	/* no compresser or swap configured */
#define VM_PAGER_DEFAULT				0x1	/* Use default pager... DEPRECATED */
#define VM_PAGER_COMPRESSOR_NO_SWAP			0x2	/* Active in-core compressor only. */
#define VM_PAGER_COMPRESSOR_WITH_SWAP			0x4	/* Active in-core compressor + swap backend. */
#define VM_PAGER_FREEZER_DEFAULT			0x8	/* Freezer backed by default pager... DEPRECATED */
#define VM_PAGER_FREEZER_COMPRESSOR_NO_SWAP		0x10	/* Freezer backed by in-core compressor only i.e. frozen data remain in-core compressed.*/
#define VM_PAGER_COMPRESSOR_NO_SWAP_PLUS_FREEZER_COMPRESSOR_WITH_SWAP	0x20	/* Active in-core compressor + Freezer backed by in-core compressor with swap support too.*/

#define VM_PAGER_MAX_MODES				6	/* Total number of vm compressor modes supported */


#define	VM_CONFIG_COMPRESSOR_IS_PRESENT		(vm_config.compressor_is_present == TRUE)
#define	VM_CONFIG_COMPRESSOR_IS_ACTIVE		(vm_config.compressor_is_active == TRUE)
#define	VM_CONFIG_SWAP_IS_PRESENT		(vm_config.swap_is_present == TRUE)
#define	VM_CONFIG_SWAP_IS_ACTIVE		(vm_config.swap_is_active == TRUE)
#define	VM_CONFIG_FREEZER_SWAP_IS_ACTIVE	(vm_config.freezer_swap_is_active == TRUE)


#endif	/* _VM_VM_PAGEOUT_H_ */
