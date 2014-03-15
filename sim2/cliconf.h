#ifndef CLICONF_H
#define CLICONF_H

#define CLI_SPLASH "Command Line Interface\n"
#define CLI_PROMPT "> "
#define CLI_TERM_MAX 32
#define CLI_MAX_ARGC 20
#define cli_gets(b) fgets(b, CLI_TERM_MAX, stdin)
#define cli_puts(b) fputs(b, stdout)

#endif /* CLICONF_H */
