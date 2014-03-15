#include "layer1.h"
#include "report.h"

static bool _report[REPORT_MAX];

void report(Node *n, enum report_types rtype, const char *format, ...)
{
	static int last_tick;
	va_list ap;
	if (_report[rtype] == false) return;
	if (last_tick != l1_get_tick()) {
		printf("tick: % 4d node: % 3d: ", l1_get_tick(), n->id);
	} else
		printf("           node: % 3d: ", n->id);

	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);

	last_tick = l1_get_tick();
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
