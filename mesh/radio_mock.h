#ifndef RADIO_MOCK_H
#define RADIO_MOCK_H
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define T struct radio

#define RADIO_NUM_TX_BUFFERS 3
#define RADIO_NUM_RX_BUFFERS 3
#define RADIO_NUM_LISTENERS 6
#define RADIO_MAX_PL 32

#define RADIO_MOCK_IRQ_RECEIVED 0
#define RADIO_MOCK_IRQ_SENT     1
T {
	bool prim_rx;

	void (*gpio_irq)(uint8_t type, void *arg);
	void *arg;

	uint16_t listeners[RADIO_NUM_LISTENERS];

	struct buf {
		uint8_t data[RADIO_MAX_PL];
		uint8_t len;
		uint16_t addr;
	} tx[RADIO_NUM_TX_BUFFERS], rx[RADIO_NUM_RX_BUFFERS];

	uint8_t txbuf_qtd;
	uint8_t rxbuf_qtd;
};

void radio_init(T *m, void (*irq)(uint8_t type, void *arg), void *arg);

void radio_listen(T *m, uint8_t i, uint16_t addr);
void radio_set_to_rx(T *m, bool rx);

void radio_write(T *m, uint16_t addr, uint8_t w[RADIO_MAX_PL], uint8_t len);
uint8_t radio_read (T *m, uint8_t r[RADIO_MAX_PL]);
uint8_t radio_get_pl_len(T *m);


void radio_transfer(T *from, T *to);
void radio_end_transfer(T *from);

void radio_shift_buf(struct buf *m, uint8_t n);

typedef T radio_t;
#undef T
#endif /* RADIO_MOCK_H */
