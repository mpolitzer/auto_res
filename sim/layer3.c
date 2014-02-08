/* --------------------------------------- */

#include <stdlib.h>
#include "common.h"
#include "report.h"
#include "layer3.h"
#include "layer2.h"

/* --------------------------------------- */

bool l3_died(Node *self, nodeid_t id)
{
	report(REPORT_L3_DIED,"L3_DIED %d -> %d\n", self->id, id);
	return true;
}

bool l3_found(Node *self, nodeid_t id)
{
	report(REPORT_L3_FOUND,"L3_FOUND %d -> %d\n", self->id, id);
	return true;
}

void l3_handle_rogm(Node *self, MessageL3 *m)
{
	
}

/* --------------------------------------- */
