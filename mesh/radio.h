#ifndef RADIO_H
#define RADIO_H
#include "msg.h"
#define T struct radio

#define RADIO_TX_BUF 3

T {
	uint8_t tx_pending;
};

gpio_IRQ(RX)     -> radio_recv -> enq + set_job
gpio_IRQ(TX_ack) -> radio_send -> l2_get_next_msg
gpio_IRQ(TX_nak) -> l2_failed -> (l3_died ?)

void	radio_set_mode(bool tx);

void    radio_write(T *self, uint8_t *pl, uint8_t len);
uint8_t radio_get_pl_len(T *self);
void    radio_read (T *self, uint8_t *pl);

// IRQs do GPIO.
void radio_sent(void);
void radio_recvd(void);

#endif /* RADIO_H */
