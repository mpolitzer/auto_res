#include <assert.h>
#include "radio_dev.h"
#define T struct radio_dev

static void radio_dev_shift_buf(struct buf *m, uint8_t n);

void radio_dev_init(T *m,
		radio_dev_irq irq,
		void *arg)
{
	assert(m);
	assert(irq);

	memset(m, 0, sizeof(*m));

	m->gpio_irq = irq;
	m->arg = arg;
}

void radio_dev_listen(T *m, uint8_t i, uint16_t addr)
{
	assert(m);
	assert(i < RADIO_NUM_LISTENERS);

	m->listeners[i] = addr;
}

void radio_dev_set_to_rx(T *m, bool prim_rx)
{
	assert(m);

	m->prim_rx = prim_rx;
}

void radio_dev_write(T *m, uint16_t addr, uint8_t w[RADIO_MAX_PL], uint8_t len)
{
	assert(m);
	assert(m->prim_rx == false);
	assert(w);
	assert(len && len <= RADIO_MAX_PL);
	assert(m->txbuf_qtd < RADIO_NUM_TX_BUFFERS);

	memcpy(m->tx[m->txbuf_qtd].data, w, len);
	m->tx[m->txbuf_qtd].len = len;
	m->tx[m->txbuf_qtd].addr = addr;
	m->txbuf_qtd++;
}

uint8_t radio_dev_get_pl_len(T *m)
{
	assert(m);
	assert(m->prim_rx == true);
	assert(m->rxbuf_qtd > 0 && m->rxbuf_qtd <= RADIO_NUM_RX_BUFFERS);

	return m->rx[0].len;
}

uint8_t radio_dev_read(T *m, uint8_t r[RADIO_MAX_PL])
{
	uint8_t len;
	assert(m);
	assert(m->prim_rx == true);
	assert(m->rxbuf_qtd > 0 && m->rxbuf_qtd <= RADIO_NUM_RX_BUFFERS);

	len = radio_dev_get_pl_len(m);
	memcpy(r, m->rx[0].data, len);
	radio_dev_shift_buf(m->rx, m->rxbuf_qtd);
	return len;
}

static void radio_dev_recv_cpy(T *self, struct buf *from_buf, struct buf *to_buf)
{
	int i;
	for(i = 0; i < RADIO_NUM_LISTENERS; i++)
	{
		if(from_buf->addr == self->listeners[i])
		{
			*to_buf = *from_buf;
			self->gpio_irq(RADIO_IRQ_RECEIVED,
					self->arg);
			break;
		}
	}
}

void radio_dev_transfer(T *from, T *to)
{
	struct buf *from_buf = &from->tx[0],
		   *to_buf   = &to->rx[to->rxbuf_qtd++];
	
	radio_dev_recv_cpy(to, from_buf, to_buf);
}

void radio_dev_end_transfer(T *from)
{
	radio_dev_shift_buf(from->tx, from->txbuf_qtd);
	from->txbuf_qtd--;
	from->gpio_irq(RADIO_IRQ_SENT, from->arg);
}

static void radio_dev_shift_buf(struct buf *m, uint8_t n)
{
	for (int i=0; i < n-1; i++) {
		struct buf *from_buf = &m[i+1],
			   *to_buf =   &m[i];
		*to_buf = *from_buf;
	}
}

void radio_dev_auto_ack(T *m, bool _)
{
	// noop :)
}
