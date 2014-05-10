static struct node_t N;

void gpio_irq(struct radio_t *r)
{
	schedule_worker(r);
}

void myworker(struct node_t *n)
{
	uint8_t len;

	len = radio_get_payload_lenght(&n->radio);
	assert(len && "wut, radio failed...");
	mem = malloc(len);
	radio_read(&n->radio, mem);

	enqueue_package(mem);
}

void node_init(struct node_t *n)
{
	radio_init(&n->radio, myworker, n);
}

int main(int argc, char *argv[])
{
	node_init(&N);

	while (run_workers()) {
	}

	return 0;
}
