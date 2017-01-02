
#include "config.h"
#include "ledmatrix.h"
#include <stdint.h>
#include <xc.h>

static uint16_t ledmatrix_timerepr[LEDMATRIX_NUM_ROWS];

void ledmatrix_init()
{
    /* Configure anode pins as outputs */
    ANSEL = 0x00; // Disable analog inputs on Port A
    LEDMATRIX_ANODE_TRIS_1 &= ~LEDMATRIX_ANODE_MASK_1;
    LEDMATRIX_ANODE_TRIS_2 &= ~LEDMATRIX_ANODE_MASK_2;
    LEDMATRIX_ANODE_TRIS_1 |= 0x00 & LEDMATRIX_ANODE_MASK_1;
    LEDMATRIX_ANODE_TRIS_2 |= 0x00 & LEDMATRIX_ANODE_MASK_2;
    
    /* Configure LED driver interface pins as outputs */
    LEDMATRIX__OE_TRIS = 0;
    LEDMATRIX__OE_PIN = 0;
    
    
    LEDMATRIX_SDO_TRIS = 0;
    LEDMATRIX_CLK_TRIS = 0;
    LEDMATRIX_LE_TRIS = 0;

    /* Deactivate anode pins */
    LEDMATRIX_ANODE_PORT_1 &= ~LEDMATRIX_ANODE_MASK_1;
    LEDMATRIX_ANODE_PORT_2 &= ~LEDMATRIX_ANODE_MASK_2;
    LEDMATRIX_ANODE_PORT_1 |= 0xff & LEDMATRIX_ANODE_MASK_1;
    LEDMATRIX_ANODE_PORT_2 |= 0xff & LEDMATRIX_ANODE_MASK_2;

    /* Fill timerepr-array with init sequence */
    uint8_t i;
    for (i = 0; i < LEDMATRIX_NUM_ROWS; i++)
    {
        ledmatrix_timerepr[i] = 0b1111111111;
    }
    
    LEDMATRIX_SDO_PIN = 0;
    LEDMATRIX_CLK_PIN = 0;
    LEDMATRIX_LE_PIN = 1;
}

void ledmatrix_set_time( datetime_t time )
{
    
}

void ledmatrix_display_next_row()
{
    static uint8_t current_row = 0;
    LEDMATRIX_ANODE_PORT_1 &= ~LEDMATRIX_ANODE_MASK_1;
    LEDMATRIX_ANODE_PORT_2 &= ~LEDMATRIX_ANODE_MASK_2;
    LEDMATRIX_ANODE_PORT_1 |= ~(ledmatrix_timerepr[current_row] & LEDMATRIX_ANODE_MASK_1);
    LEDMATRIX_ANODE_PORT_2 |= ~((ledmatrix_timerepr[current_row]>>8) & LEDMATRIX_ANODE_MASK_2);
    
    if( current_row == 0 )
    {
        LEDMATRIX_SDO_PIN = 1;
    }
    else
    {
        LEDMATRIX_SDO_PIN = 0;  
    }
    
    LEDMATRIX__OE_PIN = 1;
    LEDMATRIX_CLK_PIN = 0;
    __delay_ms(100);
    LEDMATRIX_CLK_PIN = 1;
    __delay_ms(100);
    LEDMATRIX_CLK_PIN = 0;
    __delay_ms(100);
    LEDMATRIX__OE_PIN = 0;
    
    current_row++;
    current_row %= LEDMATRIX_NUM_ROWS; // current_row can't be larger than LEDMATRIX_NUM_COLUMNS
}
