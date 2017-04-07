#include <pic.h>
#include "config.h"

#include "i2c.h"

void i2c_init()
{    
    SSPCON = 0b00101000;
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*400000))-1;
    SSPSTAT = 0;
    TRISC3 = 1;
    TRISC4 = 1;
}

uint8_t i2c_read_reg(uint8_t slave_addr, uint8_t reg_addr)
{
    uint8_t temp;
    
    i2c_start();
    i2c_write(slave_addr&0b11111110);
    i2c_write(reg_addr);
    
    i2c_start();
    i2c_write(slave_addr|0b00000001);
    temp = i2c_read(0);
    
    i2c_stop();
    
    return temp;
}

void i2c_wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void i2c_start()
{
  i2c_wait();    
  SEN = 1;
}

void i2c_rep_start()
{
  i2c_wait();
  RSEN = 1;
}

void i2c_stop()
{
    i2c_wait();
    PEN = 1;
}

void i2c_write(uint8_t byte)
{
    i2c_wait();
    SSPBUF = byte;
}

uint8_t i2c_read(uint8_t ack)
{
    uint8_t temp;
    
    i2c_wait();
    RCEN = 1;
    i2c_wait();
    temp = SSPBUF;
    i2c_wait();
    ACKDT = (ack)?0:1;
    ACKEN = 1;
    
    return temp;
}