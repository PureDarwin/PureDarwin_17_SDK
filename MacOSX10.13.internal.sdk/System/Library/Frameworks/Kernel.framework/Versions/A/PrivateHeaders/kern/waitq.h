#ifndef _WAITQ_H_
#define _WAITQ_H_
/*
 * Copyright (c) 2014-2015 Apple Computer, Inc. All rights reserved.
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

#include <mach/mach_types.h>
#include <mach/sync_policy.h>
#include <mach/kern_return.h>		/* for kern_return_t */

#include <kern/kern_types.h>		/* for wait_queue_t */
#include <kern/queue.h>
#include <kern/assert.h>

#include <sys/cdefs.h>

/*
 * Constants and types used in the waitq APIs
 */
#define WAITQ_ALL_PRIORITIES   (-1)
#define WAITQ_PROMOTE_PRIORITY (-2)
#define WAITQ_SELECT_MAX_PRI   (-3)

typedef enum e_waitq_lock_state {
	WAITQ_KEEP_LOCKED    = 0x01,
	WAITQ_UNLOCK         = 0x02,
	WAITQ_SHOULD_LOCK    = 0x04,
	WAITQ_ALREADY_LOCKED = 0x08,
	WAITQ_DONT_LOCK      = 0x10,
} waitq_lock_state_t;

/*
 * The Jenkins "one at a time" hash.
 * TBD: There may be some value to unrolling here,
 * depending on the architecture.
 */
static __inline__ uint32_t 
jenkins_hash(char *key, size_t length)
{
	uint32_t hash = 0;
	size_t i;

	for (i = 0; i < length; i++) {
		hash += (uint32_t)key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}

/* Opaque sizes and alignment used for struct verification */
#if __arm__ || __arm64__
	#define WQ_OPAQUE_ALIGN   __BIGGEST_ALIGNMENT__
	#define WQS_OPAQUE_ALIGN  __BIGGEST_ALIGNMENT__
	#if __arm__
		#define WQ_OPAQUE_SIZE   32
		#define WQS_OPAQUE_SIZE  48
	#else
		#define WQ_OPAQUE_SIZE   40
		#define WQS_OPAQUE_SIZE  56
	#endif
#elif __x86_64__
	#define WQ_OPAQUE_ALIGN   8
	#define WQS_OPAQUE_ALIGN  8
	#define WQ_OPAQUE_SIZE   48
	#define WQS_OPAQUE_SIZE  64
#else
	#error Unknown size requirement
#endif


/*
 * The opaque waitq structure is here mostly for AIO and selinfo,
 * but could potentially be used by other BSD subsystems.
 */
struct waitq { char opaque[WQ_OPAQUE_SIZE]; } __attribute__((aligned(WQ_OPAQUE_ALIGN)));
struct waitq_set { char opaque[WQS_OPAQUE_SIZE]; } __attribute__((aligned(WQS_OPAQUE_ALIGN)));



__BEGIN_DECLS

/*
 * waitq init
 */
extern kern_return_t waitq_init(struct waitq *waitq, int policy);
extern void waitq_deinit(struct waitq *waitq);

/*
 * global waitqs
 */
extern struct waitq *_global_eventq(char *event, size_t event_length);
#define global_eventq(event) _global_eventq((char *)&(event), sizeof(event))

extern struct waitq *global_waitq(int index);

/*
 * set alloc/init/free
 */
extern struct waitq_set *waitq_set_alloc(int policy, void *prepost_hook);

extern kern_return_t waitq_set_init(struct waitq_set *wqset,
				    int policy, uint64_t *reserved_link,
				    void *prepost_hook);

extern void waitq_set_deinit(struct waitq_set *wqset);

extern kern_return_t waitq_set_free(struct waitq_set *wqset);

#if DEVELOPMENT || DEBUG
#if CONFIG_WAITQ_DEBUG
extern uint64_t wqset_id(struct waitq_set *wqset);

struct waitq *wqset_waitq(struct waitq_set *wqset);
#endif /* CONFIG_WAITQ_DEBUG */
#endif /* DEVELOPMENT || DEBUG */


/*
 * set membership
 */
extern uint64_t waitq_link_reserve(struct waitq *waitq);

extern void waitq_link_release(uint64_t id);

extern boolean_t waitq_member(struct waitq *waitq, struct waitq_set *wqset);

/* returns true if the waitq is in at least 1 set */
extern boolean_t waitq_in_set(struct waitq *waitq);


/* on success, consumes an reserved_link reference */
extern kern_return_t waitq_link(struct waitq *waitq,
				struct waitq_set *wqset,
				waitq_lock_state_t lock_state,
				uint64_t *reserved_link);

extern kern_return_t waitq_unlink(struct waitq *waitq, struct waitq_set *wqset);

extern kern_return_t waitq_unlink_all(struct waitq *waitq);

extern kern_return_t waitq_set_unlink_all(struct waitq_set *wqset);

/*
 * preposts
 */
extern void waitq_clear_prepost(struct waitq *waitq);

extern void waitq_set_clear_preposts(struct waitq_set *wqset);

/*
 * interfaces used primarily by the select/kqueue subsystems
 */
extern uint64_t waitq_get_prepost_id(struct waitq *waitq);
extern void     waitq_unlink_by_prepost_id(uint64_t wqp_id, struct waitq_set *wqset);
extern struct waitq *waitq_lock_by_prepost_id(uint64_t wqp_id);

/*
 * waitq attributes
 */
extern int waitq_is_valid(struct waitq *waitq);

extern int waitq_set_is_valid(struct waitq_set *wqset);

extern int waitq_is_global(struct waitq *waitq);

extern int waitq_irq_safe(struct waitq *waitq);

#if CONFIG_WAITQ_STATS
/*
 * waitq statistics
 */
#define WAITQ_STATS_VERSION 1
struct wq_table_stats {
	uint32_t version;
	uint32_t table_elements;
	uint32_t table_used_elems;
	uint32_t table_elem_sz;
	uint32_t table_slabs;
	uint32_t table_slab_sz;

	uint64_t table_num_allocs;
	uint64_t table_num_preposts;
	uint64_t table_num_reservations;

	uint64_t table_max_used;
	uint64_t table_avg_used;
	uint64_t table_max_reservations;
	uint64_t table_avg_reservations;
};

extern void waitq_link_stats(struct wq_table_stats *stats);
extern void waitq_prepost_stats(struct wq_table_stats *stats);
#endif /* CONFIG_WAITQ_STATS */

/*
 *
 * higher-level waiting APIs
 *
 */

/* assert intent to wait on <waitq,event64> pair */
extern wait_result_t waitq_assert_wait64(struct waitq *waitq,
					 event64_t wait_event,
					 wait_interrupt_t interruptible,
					 uint64_t deadline);

extern wait_result_t waitq_assert_wait64_leeway(struct waitq *waitq,
						event64_t wait_event,
						wait_interrupt_t interruptible,
						wait_timeout_urgency_t urgency,
						uint64_t deadline,
						uint64_t leeway);

/* wakeup the most appropriate thread waiting on <waitq,event64> pair */
extern kern_return_t waitq_wakeup64_one(struct waitq *waitq,
					event64_t wake_event,
					wait_result_t result,
					int priority);

/* wakeup all the threads waiting on <waitq,event64> pair */
extern kern_return_t waitq_wakeup64_all(struct waitq *waitq,
					event64_t wake_event,
					wait_result_t result,
					int priority);


__END_DECLS

#endif	/* _WAITQ_H_ */
