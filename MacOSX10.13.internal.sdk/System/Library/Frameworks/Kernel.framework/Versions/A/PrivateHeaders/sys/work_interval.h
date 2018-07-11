/*
 * Copyright (c) 2015-2017 Apple Inc. All rights reserved.
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

#ifndef _SYS_WORK_INTERVAL_H
#define _SYS_WORK_INTERVAL_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/_types/_size_t.h>

#include <mach/port.h>

__BEGIN_DECLS

/*
 * A work interval is a repeatable unit of work characterized by a
 * start, finish, and deadline.
 *
 * Trusted clients with deadline-sensitive work may report information
 * about the execution of their work using the work interval facility.
 * This is intended to be a higher-level semantic than realtime scheduling,
 * which operates at the level of thread block/unblock. A high level
 * operation may have many blocking points, including IPC to other tasks,
 * and this this metric will capture the overall time to complete a unit of
 * work.
 *
 * A work interval is defined by several timestamps, namely (S)tart,
 * (F)inish, (D)eadline, and (N)ext start.
 *
 *   ... ----+==================+--------+--+==== ...
 *           |                  |        |  |
 *           S                  F        D  N
 *
 *           \__________________/
 *                  Active
 *           \___________________________/
 *                   Work Interval
 *
 *                               \_________/
 *                                    |
 *   report information here ---------+
 *
 * Definitions:
 *
 *   Start: Absolute time when the current deadline-oriented work began. Due
 *          to scheduling latency, preemption, and blocking points, the
 *          thread controlling the work interval may actually begin
 *          executing after this ideal time (which may be the previous work
 *          interval's "next start")
 *   Finish: Absolute time when the current deadline-oriented work finished.
 *          This will typically be a timestamp taken before reporting using
 *          the work interval interface.
 *   Deadline: Absolute time by which the current work was expected to finish.
 *          In cases where the amount of computation (or preemption, or time
 *          spent blocked) causes the active period to take longer than
 *          expected, F may be greater than D.
 *   Next start: Absolute time when the next deadline-oriented work is
 *          expected to begin. This is typically the same as Deadline.
 *   Active: The fraction of the work interval spent completing the work. In
 *          cases where the Finish time exceeded the Deadline, this fraction
 *          will be >1.0.
 *
 * Basic Use:
 *
 *   Clients should report information for a work interval after finishing
 *   work for the current interval but before the next work interval begins.
 *
 *   If Finish far exceeds the previously expected Deadline, the
 *   caller may adjust Next Start to align to a multiple of the period
 *   (and skip over several work intervals that could not be
 *   executed).
 *
 * Caution (!):
 *
 *   Because the information supplied via this facility directly influences power
 *   management decisions, clients should strive to be as accurate as possible.
 *   Failure to do so will adversely impact system power and performance.
 *
 */

/* Flags to be passed with work_interval_create() */

/* If interval is joinable, create no longer implicitly joins, you must use work_interval_join */
#define WORK_INTERVAL_FLAG_JOINABLE             (0x1)
/* Only threads that join the group are measured together, otherwise the group is the creator's home group */
#define WORK_INTERVAL_FLAG_GROUP                (0x2)

/* Flags to describe the interval flavor to the performance controller */
#define WORK_INTERVAL_TYPE_MASK                 (0xF0000000)
#define WORK_INTERVAL_TYPE_DEFAULT              (0x0 << 28)
#define WORK_INTERVAL_TYPE_COREAUDIO            (0x1 << 28)
#define WORK_INTERVAL_TYPE_COREANIMATION        (0x2 << 28)
#define WORK_INTERVAL_TYPE_LAST                 (0xF << 28)



/* Private interface between Libsyscall and xnu */
#define WORK_INTERVAL_OPERATION_CREATE  0x00000001      /* deprecated */
#define WORK_INTERVAL_OPERATION_DESTROY 0x00000002      /* arg is NULL */
#define WORK_INTERVAL_OPERATION_NOTIFY  0x00000003      /* arg is a work_interval_notification_t */
#define WORK_INTERVAL_OPERATION_CREATE2 0x00000004      /* arg is a work_interval_create_params */
#define WORK_INTERVAL_OPERATION_JOIN    0x00000005      /* arg is a port_name */

struct work_interval_notification {
	uint64_t	start;
	uint64_t	finish;
	uint64_t	deadline;
	uint64_t	next_start;
	uint32_t	notify_flags;
	uint32_t	create_flags;
};
typedef struct work_interval_notification *work_interval_notification_t;

struct work_interval_create_params {
	uint64_t        wicp_id;          /* out param */
	uint32_t        wicp_port;        /* out param */
	uint32_t        wicp_create_flags;
};

int     __work_interval_ctl(uint32_t operation, uint64_t work_interval_id, void *arg, size_t len);


__END_DECLS

#endif /* _SYS_WORK_INTERVAL_H */

