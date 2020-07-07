#ifndef _I2C_LIB_H_
#define _I2C_LIB_H_

#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <stdint.h>

#define I2C_READ  0x01
#define I2C_WRITE 0x00

#define I2C_SPEED_100K
#define I2C_SPEED_400K

/* Status Type */
#define I2C_START_ST   0x08
#define I2C_RPSTART_ST 0x10
#define I2C_LOST_ARB   0x38
/* Master Transmitter Mode ST */
#define I2C_MT_SLAW_ACK   0x18
#define I2C_MT_SLAW_NACK  0x20
#define I2C_MT_DATA_ACK   0x28
#define I2C_MT_DATA_NACK  0x30
/* Master Receiver MODE ST */
#define I2C_MR_SLAR_ACK   0x40
#define I2C_MR_SLAR_NACK  0x48
#define I2C_MR_DATA_ACK   0x50
#define I2C_MR_DATA_NACK  0x58

void i2c_init();

int8_t i2c_start(uint8_t addr);

void i2c_stop();

void i2c_send_ack();

void i2c_send_nack();

int8_t i2c_write(uint8_t data);

int8_t i2c_read_data(uint8_t addr, uint8_t *rx_buf, uint8_t reg, uint8_t len);

int8_t i2c_write_data(uint8_t addr, uint8_t *tx_buf, uint8_t reg, uint8_t len);


#endif //_I2C_LIB_H