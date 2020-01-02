/* 
 * File:   i2c.h
 * Author: seims
 *
 * Created on 21. Januar 2017, 18:36
 */

#ifndef I2C_H
#define	I2C_H

#define I2C_NACK 0
#define I2C_ACK  1

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
void i2c_init();

inline void i2c_wait();
inline void i2c_start();
inline void i2c_rep_start();
inline void i2c_stop();

inline void i2c_write(uint8_t byte);
inline uint8_t i2c_read(uint8_t ack);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

