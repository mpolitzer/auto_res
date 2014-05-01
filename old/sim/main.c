
/* --------------------------------------- */

#include <stdio.h>
#include "report.h"
#include "layer1.h"
#include "layer2.h"

/* --------------------------------------- */

int main(int argc, char *argv[]) {
	int ticks = 1000;

	if (argc != 1) { /* iterate tick times. */
		sscanf(argv[1], " %d\n", &ticks);
	}

	report_all();
	l1_init(2);
	l1_set_weight(1,2,255);
	l1_set_weight(2,1,255);

//	l2_send_l3_message(l1_get_node(1), NULL, 0);

	while(ticks--) {
		l1_tick();
	}
	l1_fini();

	return 0;
}

/* --------------------------------------- */

