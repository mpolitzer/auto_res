#ifndef NRF24L01P_REG_H
#define NRF24L01P_REG_H

/* Register Map */
#define RF24_CONFIG      0x00
#define RF24_EN_AA       0x01
#define RF24_EN_RXADDR   0x02
#define RF24_SETUP_AW    0x03
#define RF24_SETUP_RETR  0x04
#define RF24_RF_CH       0x05
#define RF24_RF_SETUP    0x06
#define RF24_STATUS      0x07
#define RF24_OBSERVE_TX  0x08
#define RF24_CD          0x09
#define RF24_RPD         0x09
#define RF24_RX_ADDR_P0  0x0A
#define RF24_RX_ADDR_P1  0x0B
#define RF24_RX_ADDR_P2  0x0C
#define RF24_RX_ADDR_P3  0x0D
#define RF24_RX_ADDR_P4  0x0E
#define RF24_RX_ADDR_P5  0x0F
#define RF24_TX_ADDR     0x10
#define RF24_RX_PW_P0    0x11
#define RF24_RX_PW_P1    0x12
#define RF24_RX_PW_P2    0x13
#define RF24_RX_PW_P3    0x14
#define RF24_RX_PW_P4    0x15
#define RF24_RX_PW_P5    0x16
#define RF24_FIFO_STATUS 0x17
#define RF24_DYNPD       0x1C
#define RF24_FEATURE     0x1D

/* Register Bits */
#define RF24_MASK_RX_DR  (1<<6)
#define RF24_MASK_TX_DS  (1<<5)
#define RF24_MASK_MAX_RT (1<<4)
#define RF24_EN_CRC      (1<<3)
#define RF24_CRCO        (1<<2)
#define RF24_PWR_UP      (1<<1)
#define RF24_PRIM_RX     (1<<0)
#define RF24_ENAA_P5     (1<<5)
#define RF24_ENAA_P4     (1<<4)
#define RF24_ENAA_P3     (1<<3)
#define RF24_ENAA_P2     (1<<2)
#define RF24_ENAA_P1     (1<<1)
#define RF24_ENAA_P0     (1<<0)
#define RF24_ERX_P5      (1<<5)
#define RF24_ERX_P4      (1<<4)
#define RF24_ERX_P3      (1<<3)
#define RF24_ERX_P2      (1<<2)
#define RF24_ERX_P1      (1<<1)
#define RF24_ERX_P0      (1<<0)
#define RF24_AW          (1<<0)
#define RF24_ARD         (1<<4)
#define RF24_ARC         (1<<0)
#define RF24_PLL_LOCK    (1<<4)
#define RF24_CONT_WAVE   (1<<7)
#define RF24_RF_DR       (1<<3)
#define RF24_RF_DR_LOW   (1<<5)
#define RF24_RF_DR_HIGH  (1<<3)
#define RF24_RF_PWR      (1<<1)
#define RF24_LNA_HCURR   (1<<0)
#define RF24_RX_DR       (1<<6)
#define RF24_TX_DS       (1<<5)
#define RF24_MAX_RT      (1<<4)
#define RF24_RX_P_NO     (1<<1)
#define RF24_TX_FULL     (1<<0)
#define RF24_PLOS_CNT    (1<<4)
#define RF24_ARC_CNT     (1<<0)
#define RF24_TX_REUSE    (1<<6)
#define RF24_FIFO_FULL   (1<<5)
#define RF24_TX_EMPTY    (1<<4)
#define RF24_RX_FULL     (1<<1)
#define RF24_RX_EMPTY    (1<<0)
#define RF24_EN_DPL      (1<<2)
#define RF24_EN_ACK_PAY  (1<<1)
#define RF24_EN_DYN_ACK  (1<<0)

/* Instructions */
#define RF24_R_REGISTER    0x00
#define RF24_W_REGISTER    0x20
#define RF24_REGISTER_MASK 0x1F
#define RF24_R_RX_PAYLOAD  0x61
#define RF24_W_TX_PAYLOAD  0xA0
#define RF24_FLUSH_TX      0xE1
#define RF24_FLUSH_RX      0xE2
#define RF24_REUSE_TX_PL   0xE3
#define RF24_R_RX_PL_WID   0x60
#define RF24_W_ACK_PAYLOAD 0xA8
#define RF24_W_TX_PAYLOAD_NOACK 0xB0
#define RF24_NOP           0xFF

#endif /* NRF24L01P_REG_H */
