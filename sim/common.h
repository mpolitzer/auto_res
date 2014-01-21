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
#define TIMEOUT_TO_DEAD (100)
#define ALIVE_INTERVAL (0.70*(TIMEOUT_TO_DEAD)) // 70 %

/* up to 255 */
#define PENDING_MAX (100)

#endif /* COMMON_H */
