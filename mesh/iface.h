#ifndef IFACE_H
#define IFACE_H
#include <stdint.h>

void radio_pins_init(void);

// call from IRQ
void radio_pins_irq(void);

void    radio_spi_init(void);
uint8_t radio_spi_rw8(uint8_t w);

#endif /* IFACE_H */
