/*
 * File:   uart.c
 * Author: simonzumbrunnen
 *
 * Created on January 2, 2020, 12:13 PM
 */

#include "config.h"
#include "uart.h"

#include <pic.h>

void uart_init( const unsigned long baudrate )
{
    unsigned long x;
    
    x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);
    
    if (x > 255)
    {
        x = (_XTAL_FREQ - baudrate*16)/(baudrate*16);
        BRGH = 1;
    }
    
    SPBRG = x;
    SYNC = 0;
    SPEN = 1;
    TXEN = 1;
    CREN = 1;
    RCIE = 1;
    PEIE = 1;
    GIE = 1;
}

inline void uart_write( char data )
{
    while(!TRMT);
    TXREG = data;
}

inline char uart_read()
{
    char data;
    
    data = RCREG;
    
    if (OERR) {
        CREN = 0;
        CREN = 1;
    }
    
    return data;
}
