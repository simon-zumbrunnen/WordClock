
#include "config.h"
#include "ledmatrix.h"
#include <stdint.h>
#include <xc.h>

static uint16_t ledmatrix_timerepr[LEDMATRIX_NUM_ROWS];

void ledmatrix_init( void )
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
        ledmatrix_timerepr[i] = 0b000000000000;
    }
    
    LEDMATRIX_SDO_PIN = 0;
    LEDMATRIX_CLK_PIN = 0;
    LEDMATRIX_LE_PIN = 1;
}

void ledmatrix_set_timerepr( uint16_t* new_timerepr ) {
    int i;
    for (i = 0; i < LEDMATRIX_NUM_ROWS; i++) {
        ledmatrix_timerepr[i] = new_timerepr[i];
    }
}

void ledmatrix_display_row( uint16_t row_value )
{
    LEDMATRIX__OE_PIN = 1;

    int i;
    for (i = 0; i < LEDMATRIX_NUM_COLS; i++)
    {
        LEDMATRIX_SDO_PIN = (row_value>>i) & 0x01;
            
        LEDMATRIX_CLK_PIN = 0;
        LEDMATRIX_CLK_PIN = 1;
        LEDMATRIX_CLK_PIN = 0;
    }
    
    LEDMATRIX__OE_PIN = 0;
}

void ledmatrix_display_next_row()
{
    static uint16_t current_row = 0;
    
    /* Select current row */
    LEDMATRIX_ANODE_PORT_1 &= ~LEDMATRIX_ANODE_MASK_1;
    LEDMATRIX_ANODE_PORT_2 &= ~LEDMATRIX_ANODE_MASK_2;
    LEDMATRIX_ANODE_PORT_1 |= ~(1L<<current_row & LEDMATRIX_ANODE_MASK_1);
    LEDMATRIX_ANODE_PORT_2 |= ~((1L<<current_row)>>8 & LEDMATRIX_ANODE_MASK_2);

    ledmatrix_display_row(ledmatrix_timerepr[current_row]);
    
    current_row++;
    current_row %= LEDMATRIX_NUM_ROWS; // current_row can't be larger than LEDMATRIX_NUM_ROWS
}
