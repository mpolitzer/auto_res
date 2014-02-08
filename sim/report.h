#ifndef REPORT_H
#define REPORT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

enum report_types {
	REPORT_L1_FAILED,
	REPORT_L2_ACK,
	REPORT_L2_ALIVE,
	REPORT_L2_HELLO,
	REPORT_L2_L3,
	REPORT_L3_OGM,
	REPORT_L3_ROGM,
	REPORT_L3_KNOWN,
	REPORT_L3_BROADCAST,
	REPORT_L3_UNICAST,
	REPORT_L3_FOUND,
	REPORT_L3_DIED,
	REPORT_MAX,
};

void report(enum report_types rtype, const char *format, ...);

void report_enable(enum report_types rtype);
void report_disable(enum report_types rtype);
void report_all();
void report_none();

#endif /* REPORT_H */
