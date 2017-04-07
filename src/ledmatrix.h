/* 
 * File:   ledmatrix.h
 * Author: zumbrunn
 *
 * Created on January 2, 2017, 10:15 AM
 */

#ifndef LEDMATRIX_H
#define	LEDMATRIX_H

#include "config.h"
#include "time.h"

#include <pic.h>

#define LEDMATRIX_NUM_ROWS 10
#define LED_MATRIX_NUM_COLS 11

#define DEBUG_LED_1_PIN RC0
#define DEBUG_LED_2_PIN RC1
#define DEBUG_LED_1_TRIS TRISC0
#define DEBUG_LED_2_TRIS TRISC1
    
#define LEDMATRIX_ANODE_PORT_1 PORTA
#define LEDMATRIX_ANODE_PORT_2 PORTD
#define LEDMATRIX_ANODE_TRIS_1 TRISA
#define LEDMATRIX_ANODE_TRIS_2 TRISD
#define LEDMATRIX_ANODE_MASK_1 0b11111111
#define LEDMATRIX_ANODE_MASK_2 0b00000011
#define LEDMATRIX_SDO_PIN RD4
#define LEDMATRIX_CLK_PIN RD5
#define LEDMATRIX_LE_PIN RD6
#define LEDMATRIX__OE_PIN RD7
#define LEDMATRIX_SDO_TRIS TRISD4
#define LEDMATRIX_CLK_TRIS TRISD5
#define LEDMATRIX_LE_TRIS TRISD6
#define LEDMATRIX__OE_TRIS TRISD7

#ifdef	__cplusplus
extern "C" {
#endif
    
void ledmatrix_init();
void ledmatrix_set_time( time_t time );
void ledmatrix_display_next_row();

#ifdef	__cplusplus
}
#endif

#endif	/* LEDMATRIX_H */

