/* 
 * File:   i2c.h
 * Author: seims
 *
 * Created on 21. Januar 2017, 18:36
 */

#ifndef I2C_H
#define	I2C_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
void i2c_init();

uint8_t i2c_read_reg(uint8_t slave_addr, uint8_t reg_addr);

void i2c_wait();
void i2c_start();
void i2c_rep_start();
void i2c_stop();

void i2c_write(uint8_t byte);
uint8_t i2c_read(uint8_t ack);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

