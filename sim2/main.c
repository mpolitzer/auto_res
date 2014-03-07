#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "l1.h"
#include "l2.h"
#include "l3.h"

int main(int argc, char *argv[]) {
	l1_init(10);
	l1_set_weight(0, 1, 255);
	l1_set_weight(1, 0, 255);

	for (int i=0; i<1000; i++) {
		l1_tick();
	}

	l1_fini();
	return 0;
}
