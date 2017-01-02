/* 
 * File:   datetime.h
 * Author: zumbrunn
 *
 * Created on January 2, 2017, 10:23 AM
 */

#ifndef DATETIME_H
#define	DATETIME_H

#include "config.h"
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;

} datetime_t; 

#ifdef	__cplusplus
}
#endif

#endif	/* DATETIME_H */

