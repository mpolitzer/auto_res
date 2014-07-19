#include "radio_drv.h"
#define T struct radio_drv

void radio_drv_init(T *self, radio_dev_irq cb, void *arg)
{
	radio_dev_init(&self->dev, cb, arg);
	radio_dev_set_to_rx(&self->dev, true);
	self->tx_pending = 0;
}

bool radio_drv_send(T *self, bool auto_ack, uint16_t addr,
		uint8_t *pl, uint8_t len)
{
	if (self->tx_pending < RADIO_TX_BUF) {
		radio_dev_set_to_rx(&self->dev, false);
		radio_dev_auto_ack(&self->dev, auto_ack);
		radio_dev_write(&self->dev, addr, pl, len);
		self->tx_pending++;
		return true;
	}
	return false;
}

uint8_t radio_drv_recv(T *self, uint8_t *pl)
{
	return radio_dev_read(&self->dev, pl);
}
