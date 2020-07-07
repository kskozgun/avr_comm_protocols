#include "i2c_lib.h"


void i2c_init()
{
    /* Optional - Pull Up SDA and SCL */
    PORTC |= (1 << PORT4) | (1 << PORT5);
    /* Reset TWCR */
    TWCR &=~ (1<<TWEN); 
    /*TWBR 16*/
    TWBR = (1 << TWBR4);
    /*Pre Scale 16 */
    TWSR |= (1 << TWPS1);
    /* Enable TWI */
    TWCR = (1 << TWEN);
}

void i2c_send_ack()
{
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR & (1<<TWINT)));
}

void i2c_send_nack()
{
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1<<TWINT)));
}

int8_t i2c_start(uint8_t addr)
{
    int8_t ret;
    TWCR = 0;
    /* Send start command */
    TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN);
    /* Wait till start send */
    while (!(TWCR & (1<<TWINT)));
    /* Check status code */
    ret = TWSR & 0xF8;
    if((ret != I2C_START_ST) && (ret!=I2C_RPSTART_ST)) {
        return -1;
    }

    TWDR = addr;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1<<TWINT)));
    ret = TWSR & 0xF8;
    if((ret != I2C_MT_SLAW_ACK) && (ret != I2C_MR_SLAR_ACK)) {
        return -1;
    }
    return 0;
}

int8_t i2c_write(uint8_t data)
{
    int8_t ret;
    /* Data is written data register */
    
    TWDR = data;
    /* Transmit data */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Check status code */
    while (!(TWCR & (1<<TWINT)));
    ret = TWSR & 0xF8;
    if (ret != I2C_MT_DATA_ACK) {
        return -1;
    }
    return 0;
}

int8_t i2c_read_data(uint8_t addr, uint8_t *rx_buf, uint8_t reg, uint8_t len)
{
    int8_t ret;
    int8_t i;
    addr = addr << 1;
    /* Start I2C Communication */
    ret = i2c_start(addr | I2C_WRITE);
    if (ret < 0) {
        return ret;
    }
    
    ret = i2c_write(reg);
    if(ret < 0){
      return ret;
    }

    ret = i2c_start(addr | I2C_READ);
    if(ret < 0) {
        return ret;
    }
    
    for(i = 0; i<len-1; i++){
      i2c_send_ack();
      *rx_buf = TWDR;
      rx_buf++;
    }
    //Serial.println(ret);
    /* Read last byte and sen nack */
    i2c_send_nack();
    *rx_buf = TWDR;

    
    /* Send Stop Bit */
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    return 0;
}

int8_t i2c_write_data(uint8_t addr, uint8_t *tx_buf, uint8_t reg, uint8_t len)
{
    int8_t ret;
    uint8_t i;

    addr = addr << 1;

    ret = i2c_start(addr | I2C_WRITE);
    if(ret < 0) {
        return ret;
    }
    ret = i2c_write(reg);
    if(ret < 0) {
        return ret;
    }

    for(i = 0; i<len; i++) {
        ret = i2c_write(*tx_buf);
        if (ret < 0) {
            return ret;
        }
        tx_buf++;
    }
    /* Send Stop */
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

    return 0;
}