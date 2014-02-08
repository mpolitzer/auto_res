#include "report.h"

	static bool _report[REPORT_MAX];

void report(enum report_types rtype, const char *format, ...)
{
	va_list ap;
	if (_report[rtype] == false) return;

	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
}

void report_enable(enum report_types rtype)
{
	_report[rtype] = true;
}

void report_disable(enum report_types rtype)
{
	_report[rtype] = false;
}

void report_all()
{
	int i;
	for (i=0; i<REPORT_MAX; i++)
		report_enable(i);
}

void report_none()
{
	int i;
	for (i=0; i<REPORT_MAX; i++)
		report_disable(i);
}
