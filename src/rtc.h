/* 
 * File:   rtc.h
 * Author: seims
 *
 * Created on 21. Januar 2017, 19:15
 */

#ifndef RTC_H
#define	RTC_H

#define RTC_I2C_ADDR 0xD0

#ifdef	__cplusplus
extern "C" {
#endif

void rtc_init();

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

