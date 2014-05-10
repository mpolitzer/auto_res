/* ========================================================================== */
struct msg_t {
	uint16_t dst;
	uint8_t len; /* up to 32bytes */
	char pl[];
};

#define L2_HELLO
#define L2_ALIVE
#define L2_ACK
#define L2_PL
struct l2msg_t {
	uint16_t src; // 2

	uint8_t type; // 3

	/* seq or CRC, check todo decisions. */
	uint8_t  crc; // 4 /* because we want to crypt the l2 package. AES? */
	uint8_t seq;  // 4 /* to prevent replay attack. */

	char pl[];
};

struct l2msg_alive_t {
	uint16_t dst; // 5
};

#define L3_OGM
#define L3_ROGM
#define L3_KNOWN
#define L3_PL
#define L3_PL_BROADCAST
struct l3msg_t {
	uint16_t src; // 5
	uint16_t dst; // 7
	uint8_t type; // 8
#if 0
	/* Do split later */
	uint8_t df:1;
	uint8_t mf:1;
	uint8_t fragment_offset:6; // 9
#endif
	char pl[];
};

struct l3msg_ctl { /* no payload! */
	uint8_t seq;
};

struct l3msg_pl_broadcast {
	uint8_t seq;
	char pl[];
};

/* msg ====================================================================== */
/* payload = sizeof(l2msg_t) + sizeof(l3msg_t) + ... */
struct msg_t   *msg_alloc(size_t payload);
void            msg_free (struct msg_t *);

struct l2msg_t *msg_get_l2(struct msg_t *);
struct l3msg_t *msg_get_l3(struct msg_t *);
struct l4msg_t *msg_get_l4(struct msg_t *);

/* node ===================================================================== */
void node_init(struct node_t *);
void node_tick(struct node_t *);

/* l2 ======================================================================= */
void l2_tick(struct node_t *); /* alive enviado de tempos em tempos. */
bool l2_send(struct node_t *, struct msg_t *);
void l2_recv(struct node_t *, struct msg_t *);

/* l3 ======================================================================= */
void l3_tick(struct node_t *); /* OGM enviado de tempos em tempos. */
bool l3_send(struct node_t *, struct msg_t *);
void l3_recv(struct node_t *, struct msg_t *);

/* callbacks para l2 */
void l3_found(struct node_t *, node_id id);
void l3_died (struct node_t *, node_id id);

/* l4 ======================================================================= */
/* timeouts? */
bool l4_send(struct node_t *, struct msg_t *);
void l4_recv(struct node_t *, struct msg_t *);

void l4_msg_timed_out(struct node_t *, struct msg_t *);

/* radio ==================================================================== */
struct radio_t {
	uint8_t sending;
	uint8_t address[6][3];
	struct radio_buffer = {
		uint8_t msg[32];
		uint8_t len;
	} tx[3], rx[3];
};

void    radio_init(struct radio_t *, void (*cont)(void *arg), void *arg);
void    radio_send(struct radio_t *, uint16_t to, uint8_t *pl, uint8_t len);
void    radio_read(struct radio_t *, uint8_t *pl);
uint8_t radio_get_payload_lenght(struct radio_t *);

/* -------------------------------------------------------------------------- */
/* received message. */
(recv)
gpio_IRQ -> worker -> radio_read(m) -> l2_recv(n, m) -> l3_recv(n, m) -> l4_recv(n, m)
					|		|		|
					|		|		+-> handle (l4_ack:"TCP" / timeout)
					|		+-> handle(rogm, known)
					+-> handle (hello, alive, l2_ack)

/* -------------------------------------------------------------------------- */
/* send message. */
l4_send(n, m) -> l3_send(n, m) -> l2_send(n, m)
					|
					+-> enqueue(m)
					gpio_IRQ -> dequeue(m) -> radio_send(m)
/* -------------------------------------------------------------------------- */
