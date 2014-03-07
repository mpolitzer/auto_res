#include "report.h"

void report(struct node_t *n, const char *format, ...)
{
	va_list ap;

	static uint32_t last_tick = -1;

	if (last_tick != l1_get_tick()) {
		printf("tick: % 4d node: % 3d: ", l1_get_tick(), n->id);
	} else
		printf("           node: % 3d: ", n->id);
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);

	last_tick = l1_get_tick();
}
