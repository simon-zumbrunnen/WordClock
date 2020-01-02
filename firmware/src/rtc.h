/* 
 * File:   rtc.h
 * Author: seims
 *
 * Created on 21. Januar 2017, 19:15
 */

#ifndef RTC_H
#define	RTC_H

#include "time.h"

#include <xc.h>

#define RTC_I2C_ADDR 0xD0

#ifdef	__cplusplus
extern "C" {
#endif
    
void rtc_init();

uint8_t rtc_read(uint8_t reg_adr);
void rtc_write(uint8_t reg_adr, uint8_t reg_value);

inline uint8_t int_to_bcd(uint8_t int_val);
inline uint8_t bcd6_to_int(uint8_t bcd_val);
inline uint8_t bcd7_to_int(uint8_t bcd_val);

time_t rtc_read_time();
void rtc_write_time(time_t time);

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

