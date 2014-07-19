#ifndef RADIO_DRV_H
#define RADIO_DRV_H

#define T struct radio_drv

#define RADIO_TX_BUF 3

T {
	RadioDev dev;
	uint8_t tx_pending;
};

typedef void (*radio_dev_irq) (void *);

void   radio_drv_init(T *self, radio_dev_irq cb, void *arg);

bool radio_drv_send(T *self,
		bool auto_ack, uint16_t addr,
		uint8_t *pl, uint8_t len);
uint8_t radio_drv_recv(T *self, uint8_t *pl);

// IRQs do GPIO.
//void radio_drv_irq(int type, void *arg);

typedef T RadioDrv;
#undef T
#endif /* RADIO_DRV_H */
