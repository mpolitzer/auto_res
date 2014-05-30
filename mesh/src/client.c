void myrx(...)
{
	/* ignore rx */
}

int main(int argc, char *argv[])
{
	mesh_init(&myrx);

	for (;;) {
		uint16_t adc = adc_aquire();
		msg_t *m = msg_alloc(sizeof(uint16_t));
		memcpy(msg_getpayload(m), &adc, sizeof(uint16_t));
		mesh_sendto(m, MYSERVER);

		mesh_tick(100);
		delay_ms(100);
	}
	return 0;
}
