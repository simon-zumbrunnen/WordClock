
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
    ledmatrix_timerepr[0] = 0b0000000000;
    ledmatrix_timerepr[1] = 0b0000000000;
    ledmatrix_timerepr[2] = 0b0100000000;
    ledmatrix_timerepr[3] = 0b0100001000;
    ledmatrix_timerepr[4] = 0b0100001000;
    ledmatrix_timerepr[5] = 0b0100000011;
    ledmatrix_timerepr[6] = 0b0100000011;
    ledmatrix_timerepr[7] = 0b0100000011;
    ledmatrix_timerepr[8] = 0b0000000011;
    ledmatrix_timerepr[9] = 0b0000000010;
    ledmatrix_timerepr[10]= 0b0000000011;
    ledmatrix_timerepr[11]= 0b0000000011;
    
}

void ledmatrix_display_row( uint8_t row_num )
{
    LEDMATRIX__OE_PIN = 1;

    int i;
    for (i = 0; i < LEDMATRIX_NUM_ROWS; i++)
    {
        if (i == row_num)
        {
            LEDMATRIX_SDO_PIN = 1;
        }
        else
        {
            LEDMATRIX_SDO_PIN = 0;
        }
        LEDMATRIX_CLK_PIN = 0;
        LEDMATRIX_CLK_PIN = 1;
        LEDMATRIX_CLK_PIN = 0;
    }
    
    LEDMATRIX__OE_PIN = 0;
}

void ledmatrix_display_next_row()
{
    static uint8_t current_row = 0;
    LEDMATRIX_ANODE_PORT_1 &= ~LEDMATRIX_ANODE_MASK_1;
    LEDMATRIX_ANODE_PORT_2 &= ~LEDMATRIX_ANODE_MASK_2;
    LEDMATRIX_ANODE_PORT_1 |= ~(ledmatrix_timerepr[current_row] & LEDMATRIX_ANODE_MASK_1);
    LEDMATRIX_ANODE_PORT_2 |= ~((ledmatrix_timerepr[current_row]>>8) & LEDMATRIX_ANODE_MASK_2);

    ledmatrix_display_row(current_row);
    
    current_row++;
    current_row %= LEDMATRIX_NUM_ROWS; // current_row can't be larger than LEDMATRIX_NUM_COLUMNS
}
