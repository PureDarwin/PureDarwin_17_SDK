/*
 * Copyright (c) 2015 Apple Inc. All rights reserved.
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
#ifndef _SYS_PERSONA_H_
#define _SYS_PERSONA_H_

#include <sys/param.h>

enum {
	PERSONA_INVALID = 0,
	PERSONA_GUEST   = 1,
	PERSONA_MANAGED = 2,
	PERSONA_PRIV    = 3,
	PERSONA_SYSTEM  = 4,

	PERSONA_TYPE_MAX = PERSONA_SYSTEM,
};

#define PERSONA_ID_NONE ((uid_t)-1)

struct kpersona_info {
	uint32_t persona_info_version;

	uid_t    persona_id; /* overlaps with UID */
	int      persona_type;
	gid_t    persona_gid;
	uint32_t persona_ngroups;
	gid_t    persona_groups[NGROUPS];
	uid_t    persona_gmuid;
	char     persona_name[MAXLOGNAME+1];

	/* TODO: MAC policies?! */
};

#define PERSONA_INFO_V1       1
#define PERSONA_INFO_V1_SIZE  (sizeof(struct kpersona_info))


#define PERSONA_OP_ALLOC    1
#define PERSONA_OP_DEALLOC  2
#define PERSONA_OP_GET      3
#define PERSONA_OP_INFO     4
#define PERSONA_OP_PIDINFO  5
#define PERSONA_OP_FIND     6


/* XNU + kext private interface */
#include <sys/cdefs.h>
#include <sys/kauth.h>
#include <libkern/libkern.h>

#ifdef PERSONA_DEBUG
#define persona_dbg(fmt, ...) \
	printf("[%4d] %s:  " fmt "\n", \
	       current_proc() ? current_proc()->p_pid : -1, \
	       __func__, ## __VA_ARGS__)
#else
#define persona_dbg(fmt, ...) do { } while (0)
#endif

/*
 * Persona
 */
/* kexts should only see an opaque persona structure */
struct persona;

__BEGIN_DECLS

#ifndef _KAUTH_CRED_T
#define	_KAUTH_CRED_T
typedef struct ucred *kauth_cred_t;
#endif	/* !_KAUTH_CRED_T */

/* returns the persona ID for the given pesona structure */
uid_t persona_get_id(struct persona *persona);

/* returns the type of the persona (see enum above: PERSONA_GUEST, etc.) */
int persona_get_type(struct persona *persona);

/* returns ref on kauth_cred_t that must be dropped via kauth_cred_unref() */
kauth_cred_t persona_get_cred(struct persona *persona);

/* returns a reference that must be released with persona_put() */
struct persona *persona_lookup(uid_t id);

/*
 * returns non-zero on error, on success returns 0 and updates 'plen' to
 * total found (could be more than original value of 'plen')
 */
int persona_find(const char *login, uid_t uid,
		 struct persona **persona, size_t *plen);

/* returns a reference to the persona tied to the current thread */
struct persona *current_persona_get(void);

/* get a reference to a persona structure */
struct persona *persona_get(struct persona *persona);

/* release a reference to a persona structure */
void persona_put(struct persona *persona);

__END_DECLS


#endif /* _SYS_PERSONA_H_ */
