#include "radio_mock.h"
#include <assert.h>
#define T struct radio

void radio_init(T *m, void (*irq)(uint8_t type, void *arg), void *arg)
{
	assert(m);
	assert(irq);

	memset(m, 0, sizeof(*m));

	m->gpio_irq = irq;
	m->arg = arg;
}

void radio_listen(T *m, uint8_t i, uint16_t addr)
{
	assert(m);
	assert(i < RADIO_NUM_LISTENERS);

	m->listeners[i] = addr;
}

void radio_set_to_rx(T *m, bool prim_rx)
{
	assert(m);

	m->prim_rx = prim_rx;
}

void radio_write(T *m, uint16_t addr, uint8_t w[RADIO_MAX_PL], uint8_t len)
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

uint8_t radio_get_pl_len(T *m)
{
	assert(m);
	assert(m->prim_rx == true);
	assert(m->rxbuf_qtd > 0 && m->rxbuf_qtd <= RADIO_NUM_RX_BUFFERS);

	return m->rx[0].len;
}

uint8_t radio_read(T *m, uint8_t r[RADIO_MAX_PL])
{
	uint8_t len;
	assert(m);
	assert(m->prim_rx == true);
	assert(m->rxbuf_qtd > 0 && m->rxbuf_qtd <= RADIO_NUM_RX_BUFFERS);

	len = radio_get_pl_len(m);
	memcpy(r, m->rx[0].data, len);
	radio_shift_buf(m->rx, m->rxbuf_qtd);
	return len;
}

void radio_recv_cpy(T *self, struct buf *from_buf, struct buf *to_buf)
{
	int i;
	for(i = 0; i < RADIO_NUM_LISTENERS; i++)
	{
		if(from_buf->addr == self->listeners[i])
		{
			*to_buf = *from_buf;
			self->gpio_irq(RADIO_MOCK_IRQ_RECEIVED, self->arg);
			break;
		}
	}
}

void radio_transfer(T *from, T *to)
{
	struct buf *from_buf = &from->tx[0],
		   *to_buf   = &to->rx[to->rxbuf_qtd++];
	
	radio_recv_cpy(to, from_buf, to_buf);
}

void radio_end_transfer(T *from)
{
	radio_shift_buf(from->tx, from->txbuf_qtd);
	from->txbuf_qtd--;
	from->gpio_irq(RADIO_MOCK_IRQ_SENT, from->arg);
}

void radio_shift_buf(struct buf *m, uint8_t n)
{
	for (int i=0; i < n-1; i++) {
		struct buf *from_buf = &m[i+1],
			   *to_buf =   &m[i];
		*to_buf = *from_buf;
	}
}
