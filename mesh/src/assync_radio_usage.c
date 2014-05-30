static struct node_t N;

typedef void (*worker_t)(void *arg, uint16_t dt);

/* radio API */
void    radio_init(struct radio_t *, void (*cont)(uint8_t pl_len, void *arg), void *arg);
void    radio_send(struct radio_t *, uint16_t to, uint8_t *pl, uint8_t len);
void    radio_read(struct radio_t *, uint8_t pl[PL_LEN_MAX]);

/* l2 */
void l2_cont(uint8_t pl_len, void *_arg)
{
	struct node_t *n = arg;
	msg_t *m = malloc(pl_len);
	radio_read(&n->radio, m);
	...
}

void node_init(struct node_t *n)
{
	radio_init(&n->radio, l2_cont, n);
}

void gpio_irq(struct radio_t *r)
{
	schedule_worker(r);
}

void mesh_tick(uint16_t dt)
{
	run_workers();
	l2_tick(dt); /* and 3, and 4. */
}

int main(int argc, char *argv[])
{
	mesh_init(&M, rx_cb, NULL);

	while (1) {
		mesh_tick(dt);
		...
	}

	return 0;
}

/* MESH INTERFACE */
void mesh_init(void (*recv)(msg_t *, void *arg), void *arg);

/*
	msg_t *m  = msg_alloc(bytes);
	char  *pl = msg_payload(m);
	pl[0] = 1;

	mesh_sendto(m, 192.168.1.8);
	mesh_send(m);
*/
void mesh_send(msg_t *m);

void mesh_setaddr(address_t *);
void mesh_getaddr(address_t *);
