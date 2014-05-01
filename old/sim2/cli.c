#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "cli.h"
#include "cliconf.h"

enum sm_state { START, INSTR, INTOK, STSTR, ESCAPE, END };
enum sm_input { OTHER, BLANK, QUOTE };

/* state machine to transform a string into argc+argv.
 * recognizes double-quoted strings, escaped double-quote and tokens. */
static int eval(char ch, int state) {
	enum sm_input input;

	int sm[][5] = {
		/* START, INSTR, INTOK, STSTR */
		{  INTOK, INSTR, INTOK, INSTR }, /* OTHER */
		{  START, INSTR, START, INSTR }, /* BLANK */
		{  STSTR, START, STSTR, START }, /* QUOTE */
	};
	if      (ch == '\0')  return END;
	else if (ch == '\\')  return ESCAPE;
	else if (ch ==  '"')  input = QUOTE;
	else if (isspace(ch)) input = BLANK;
	else                  input = OTHER;
	return sm[input][state];
}
static int tokenize(char *msg, const char **argv, int maxarg) {
	int state=START, argc=0;
	char *tail = msg+strlen(msg);

	while (1) {
		int newstate = eval(*msg, state);
		if (state != newstate) {
			switch (newstate) {
			case ESCAPE:
				memmove(msg, msg+1, tail-msg);
				break;
			case START:
				*msg = '\0';
				break;
			case INSTR: /* fall */
			case INTOK:
				argv[argc++] = msg;
				break;
			default: break;
			}
		}
		if (newstate == END)
			break;
		if (newstate != ESCAPE)
			state = newstate;
		msg++;
	}
	return argc;
}
static int bsearch(const char *s, struct cli_pair *pairs, int low, int high) {
	while (low < high) {
		int cur = (low+high)/2;
		int ret = strcmp(pairs[cur].name, s);
		cur = (low+high)/2;
		if (ret < 0)	low  = cur+1;
		else		high = cur;
	}
	if (low == high && strcmp(pairs[low].name, s) == 0)
		return low;
	return -1;
}
int cli_call(char *msg, struct cli_pair *pairs, uint16_t n, void *arg) {
	const char *argv[CLI_MAX_ARGC];
	int i, argc, pos;
	if ((argc = tokenize(msg, argv, ARRAY_COUNT(argv))) == 0)
		return 0;
	for (i=argc; i<CLI_MAX_ARGC; i++)
		argv[i] = 0;
	if ((pos = bsearch(argv[0], pairs, 0, n-1)) < 0)
		return EOF;
	return pairs[pos].fn(argc, argv, arg);
}

void cli_term(struct cli_pair *pairs, uint16_t n, void *arg) {
	char buf[CLI_TERM_MAX];

	cli_puts(CLI_SPLASH);
	cli_puts(CLI_PROMPT);
	while (cli_gets(buf) != NULL) {
		if (cli_call(buf, pairs, n, arg) < 0) {
			cli_puts("invalid command: ");
			cli_puts(buf);
		}
		cli_puts(CLI_PROMPT);
	}
	cli_puts("\n");
}
