/** @file
 * @defgroup cli cli
 * @{
 *
 * @code
 * uint16_t cmd_debug(int argc, const char *argv[], void *envp) {
 * 	int i;
 * 	printf("cmd:<%s>\n", argv[0]);
 * 	for (i=1; i<argc; i++) {
 * 		printf("arg:<%s>\n", argv[i]);
 * 	}
 * }
 *
 * struct cli_pair cmds[] = {
 * 	{"ls",    cmd_debug},
 * 	{"mkdir", cmd_debug},
 * };
 *
 * int main(int argc, char *argv[])
 * {
 * 	if (argc == 1) return -1;
 * 	return cli_call(argv[1], cmds, ARRAY_COUNT(cmds), NULL);
 * }
 * @endcode
 ******************************************************************************/
#ifndef CLI_H
#define CLI_H

/** get the number of elements in a array. */
#define ARRAY_COUNT(x) (sizeof(x) / sizeof(*x))

#include <stdint.h>

/** prototype for commands. */
typedef uint16_t (*cli_fn)(int argc, const char *argv[], void *envp);

/**@brief link a name to a function. */
struct cli_pair {
	const char *name;	/**< command to match */
	cli_fn fn;		/**< execute on match */
};

/** Break @b s into argc+argv and pass it to the @b pair with matching name.
 * @param [in] s     - command line.
 * @param [in] pairs - sorted array of @ref cli_pair.
 * @param [in] n     - number of entries in @b pairs, pass ARRAY_COUNT(pairs).
 * @param [in] arg   - userdata to pass.
 * @retval EOF command missmatch.
 * @retval >=0 depending on the executed command. */
int cli_call(char *s, struct cli_pair *pairs, uint16_t n, void *arg);

/** Create a command terminal with @ref cli_call as core.
 * IO functions and limits are defined in cliconf.h */
void cli_term(struct cli_pair *pairs, uint16_t n, void *arg);

#endif /* CLI_H */
/* @} */
