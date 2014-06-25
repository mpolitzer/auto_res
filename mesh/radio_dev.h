#ifndef RADIO_DEV_H
#define RADIO_DEV_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#define T struct radio_dev

#define RADIO_NUM_TX_BUFFERS 3
#define RADIO_NUM_RX_BUFFERS 3
#define RADIO_NUM_LISTENERS 6
#define RADIO_MAX_PL 32

#define RADIO_IRQ_RECEIVED 0
#define RADIO_IRQ_SENT     1

typedef void (*radio_dev_irq)(int type, void *arg);


T {
	bool prim_rx;

	radio_dev_irq gpio_irq;
	void *arg;

	uint16_t listeners[RADIO_NUM_LISTENERS];

	struct buf {
		uint16_t addr;
		uint8_t len;
		uint8_t data[RADIO_MAX_PL];
	} tx[RADIO_NUM_TX_BUFFERS], rx[RADIO_NUM_RX_BUFFERS];

	uint8_t txbuf_qtd;
	uint8_t rxbuf_qtd;
};

void    radio_dev_init(T *m,
		radio_dev_irq irq,
		void *arg);

void    radio_dev_listen(T *m,
		uint8_t i,
		uint16_t addr);
void    radio_dev_set_to_rx(T *m,
		bool rx);

void    radio_dev_write(T *m,
		uint16_t addr,
		uint8_t w[RADIO_MAX_PL],
		uint8_t len);
uint8_t radio_dev_read (T *m,
		uint8_t r[RADIO_MAX_PL]);
uint8_t radio_dev_get_pl_len(T *m);
void    radio_dev_auto_ack(T *m, bool _);

void    radio_dev_transfer(T *from, T *to);
void    radio_dev_end_transfer(T *from);

typedef T RadioDev;
#undef T
#endif /* RADIO_DEV_H */
