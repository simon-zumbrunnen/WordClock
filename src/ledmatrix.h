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

#define VOR       0b000111000000
#define AB        0b000000011000

#define FUENFAB   0b000000011110
#define ZEHNAB    0b011100000000
#define VIERTEL   0b111111100000
#define ZWANZIG   0b000001111110
#define HALB      0b111110000000

#define EINS      0b111000000000
#define ZWEI      0b111100000000
#define DREI      0b000111000000
#define VIER      0b111110000000
#define FUENF     0b000000111110
#define SECHS     0b000011111110
#define SIEBEN    0b000011111110
#define ACHT      0b111110000000
#define NEUN      0b000000111100
#define ZEHN      0b000000111110
#define ELF       0b111100000000
#define ZWOELF    0b000001111110


#define LEDMATRIX_NUM_ROWS 10
#define LED_MATRIX_NUM_COLS 11+1

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

