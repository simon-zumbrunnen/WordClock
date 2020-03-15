/* 
 * File:   uart.h
 * Author: simonzumbrunnen
 *
 * Created on January 2, 2020, 12:01 AM
 */

#ifndef UART_H
#define	UART_H

#include "config.h"

#include <pic.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
void uart_init( const unsigned long baudrate );
inline void uart_write( char data );
inline char uart_read( void );

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */
