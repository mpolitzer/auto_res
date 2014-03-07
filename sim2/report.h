#ifndef REPORT_H
#define REPORT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include "l1.h"
#include "node.h"

void report(struct node_t *n, const char *format, ...);

#endif /* REPORT_H */
