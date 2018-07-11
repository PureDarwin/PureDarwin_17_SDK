#ifndef SYS_MONOTONIC_H
#define SYS_MONOTONIC_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/ioccom.h>

__BEGIN_DECLS

/*
 * XXX These declarations are subject to change at any time.
 */

struct monotonic_config {
	uint64_t event;
	uint64_t allowed_ctr_mask;
};

union monotonic_ctl_add {
	struct {
		struct monotonic_config config;
	} in;

	struct {
		uint32_t ctr;
	} out;
};

union monotonic_ctl_enable {
	struct {
		bool enable;
	} in;
};

union monotonic_ctl_counts {
	struct {
		uint64_t ctr_mask;
	} in;

	struct {
		uint64_t counts[1];
	} out;
};

#define MT_IOC(x) _IO('m', (x))

/*
 * FIXME
 *
 * - Consider a separate IOC for disable -- to avoid the copyin to determine which way to set it.
 *
 * - Maybe IOC_COUNTS should just return all the enable counters' counts.
 */
enum monotonic_ioc {
	MT_IOC_RESET = MT_IOC(0),
	MT_IOC_ADD = MT_IOC(1),
	MT_IOC_ENABLE = MT_IOC(2),
	MT_IOC_COUNTS = MT_IOC(3),
};

#undef MT_IOC


__END_DECLS

#endif /* !defined(SYS_MONOTONIC_H) */
