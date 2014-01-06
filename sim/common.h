#ifndef COMMON_H
#define COMMON_H

#include <assert.h>
#include <stdint.h>

/* zero is reserved for invalid. */
typedef uint16_t nodeid_t;
//#define NODE_MAX    ((nodeid_t)-1)
#define NODE_MAX     10 
#define MSG_BUF_MAX  128

/* up to 127 */
#define ALIVE_MAX (100)

/* up to 255 */
#define PENDING_MAX (100)

#endif /* COMMON_H */
