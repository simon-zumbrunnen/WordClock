/* 
 * File:   datetime.h
 * Author: zumbrunn
 *
 * Created on January 2, 2017, 10:23 AM
 */

#ifndef TIME_H
#define	TIME_H

#include "config.h"
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;

} time_t; 

#ifdef	__cplusplus
}
#endif

#endif	/* TIME_H */

