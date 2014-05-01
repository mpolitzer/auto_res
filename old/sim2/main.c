#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cliconf.h"
#include "cli.h"

#include "l1.h"
#include "l2.h"
#include "l3.h"

static int read_int(const char *s) {
	int i;
	sscanf(s, " %d", &i);
	return i;
}

uint16_t cmd_step(int argc, const char *argv[], void *envp) {
	int n = 1;
	if (argc == 2) {
		sscanf(argv[1], " %d", &n);
		if (n < 0) n = 1;
	}
	while (n--) l1_tick();
	return 0;
}

uint16_t cmd_exit(int argc, const char *argv[], void *envp) {
	return 1;
}

uint16_t cmd_addlink(int argc, const char *argv[], void *envp) {
	if (argc != 4) {
		uint32_t max = l1_get_n()-1;
		printf("%s src(0..%d), dst(0..%d), weight(1..255)\n",
				argv[0], max, max);
		return -1;
	}
	int i = read_int(argv[1]),
	    j = read_int(argv[2]),
	    w  = read_int(argv[3]);
	l1_set_weight(i, j, w);
	return 0;
}

uint16_t cmd_dellink(int argc, const char *argv[], void *envp) {
	if (argc != 3) {
		uint32_t max = l1_get_n()-1;
		printf("%s src(0..%d), dst(0..%d)\n",
				argv[0], max, max);
		return -1;
	}
	int i = read_int(argv[1]),
	    j = read_int(argv[2]);
	l1_set_weight(i, j, 0);
	return 0;
}

uint16_t cmd_dotit(int argc, const char *argv[], void *envp) {
	int i, j, w, n = l1_get_n()-1;
	FILE *fil = stdout;

	if (argc > 1)
		fil = fopen(argv[1], "w");

	fprintf(fil, "digraph {\n");
	for (i = 0; i<n; i++) {
		for (j = 0; j<n; j++) {
			if ((w = l1_get_weight(i, j))) {
				fprintf(fil, "\t%d -> %d;\n", i, j);
			}
		}
	}
	fprintf(fil, "}\n");
	if (fil != stdout)
		fclose(fil);
	return 0;
}

/* keep me sorted by string. */
static struct cli_pair cmds[] = {
	{ "addlink", cmd_addlink },
	{ "dellink", cmd_dellink },
	{ "dotit",   cmd_dotit },
	{ "exit",    cmd_exit },
	{ "step",    cmd_step },
};

int main(int argc, char *argv[]) {
	char buf[CLI_TERM_MAX];

	l1_init(10);
	l1_set_weight(0, 1, 255);
	l1_set_weight(1, 0, 255);

	while (cli_gets(buf) != NULL) {
		int err = cli_call(buf, cmds, ARRAY_COUNT(cmds), NULL);
		switch (err) {
			case-1: cli_puts("invalid command: ");
				cli_puts(buf);
				break;
		case 1: goto fini;
		default: break;
		}
	}
fini:
	l1_fini();
	return 0;
}
