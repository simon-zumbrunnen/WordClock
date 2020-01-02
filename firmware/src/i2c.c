#include "config.h"

#include "i2c.h"

#include <pic.h>

void i2c_init()
{    
	TRISC3 = 1;
    TRISC4 = 1;
	SSPSTAT = 0x80;
	SSPCON = 0x28;
	SSPCON2 = 0x00;
	SSPADD  = (_XTAL_FREQ/(4*100000))-1;
	SSPIF = 0;
}

inline void i2c_wait()
{
    while(SSPIF == 0);
    SSPIF = 0;
}

inline void i2c_start()
{
    SEN = 1;
    i2c_wait();    
}

inline void i2c_rep_start()
{
    RSEN = 1;
    i2c_wait();
}

inline void i2c_stop()
{
    PEN = 1;
    i2c_wait();
}

inline void i2c_write(uint8_t byte)
{
    SSPBUF = byte;
    i2c_wait();
}

inline uint8_t i2c_read(uint8_t ack)
{
	RCEN = 1;
	i2c_wait();
	ACKDT = (ack == 0) ? 1 : 0;
	ACKEN = 1;
	i2c_wait();
    
	return SSPBUF;
}