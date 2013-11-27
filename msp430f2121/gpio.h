#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
typedef uint8_t gpio_mask;

#define PALL ((gpio_mask)-1)
#define P0 (1<<0)
#define P1 (1<<1)
#define P2 (1<<2)
#define P3 (1<<3)
#define P4 (1<<4)
#define P5 (1<<5)
#define P6 (1<<6)
#define P7 (1<<7)

#endif /* GPIO_H */

