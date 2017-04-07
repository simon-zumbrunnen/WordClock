
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
        ledmatrix_timerepr[i] = 0b000000000000;
    }
    
    LEDMATRIX_SDO_PIN = 0;
    LEDMATRIX_CLK_PIN = 0;
    LEDMATRIX_LE_PIN = 1;
}

void ledmatrix_set_time( time_t time )
{   
     /* Clear all LEDs */
    uint8_t i;
    for (i = 0; i < LEDMATRIX_NUM_ROWS; i++)
    {
        ledmatrix_timerepr[i] = 0b000000000000;
    }
    
    ledmatrix_timerepr[0] = 0b110111100000; // ES ISCH
    
    
    uint8_t hour = time.hour;
    if ( time.minute > 22 )
    {
        hour += 1; // ab der halben Stunde = VOR der n‰chsten Stunde
        
        if ( time.minute < 38 )
        {
            ledmatrix_timerepr[4] = 0b111110000000; // HALBI
        }
        else
        {
            if ( !(time.minute > 57) )
            {    
                ledmatrix_timerepr[3] = 0b000111000000; // VOR
            }
        }     
    }
    else
    {
        if ( !(time.minute < 3) )
            { 
            ledmatrix_timerepr[3] = 0b000000011000; // AB
            }
    }
        
    switch (hour)
    {
        case 0:
        case 12:
        case 24:
            ledmatrix_timerepr[7] = 0b000001111110; // ZW÷LFI         
            break;
        case 1:
        case 13:
            ledmatrix_timerepr[5] = 0b111000000000; // EIS
            break;
        case 2:
        case 14:
            ledmatrix_timerepr[6] = 0b111100000000; // ZWEI
            break;
        case 3:
        case 15:
            ledmatrix_timerepr[5] = 0b000111000000; //  DR‹
            break;
        case 4:
        case 16:
            ledmatrix_timerepr[7] = 0b111110000000; //  VIERI
            break;           
        case 5:
        case 17:
            ledmatrix_timerepr[5] = 0b000000111110; // F÷IFI
            break;
        case 6:
        case 18:
            ledmatrix_timerepr[6] = 0b000011111100; // SƒCHSI
            break;
        case 7:
        case 19:
            ledmatrix_timerepr[8] = 0b000011111100; // SIEBNI
            break; 
        case 8:
        case 20:
            ledmatrix_timerepr[9] = 0b111110000000; // ACHTI
            break;
        case 9:
        case 21:
            ledmatrix_timerepr[4] = 0b000000111100; // N‹NI
            break;
        case 10:
        case 22:
            ledmatrix_timerepr[9] = 0b000000111110; // ZƒHNI
            break;
        case 11:
        case 23:
            ledmatrix_timerepr[8] = 0b111100000000; // ELFI
            break;            
        default:
            
            break;
    }         
    
    //ledmatrix_timerepr[0] = 0b110111100001; // ES ISCH, 12. Col f¸r Minute +1 (oben rechts)
    //ledmatrix_timerepr[1] = 0b000000000001; // VIERTEL / F÷IF, 12. Col f¸r Minute +2 (unten rechts)
    //ledmatrix_timerepr[2] = 0b000000000001; // ZƒH / ZWƒNZG,  12. Col f¸r Minute -1 (oben links)
    //ledmatrix_timerepr[3] = 0b000000000001; // VOR / AB, 12. Col f¸r Minute -2 (unten links)
    //ledmatrix_timerepr[4] = 0b000000000000; // HALBI / N‹NI
    //ledmatrix_timerepr[5] = 0b000000000000; // EIS / DR‹ / F÷IFI
    //ledmatrix_timerepr[6] = 0b000000000000; // ZWEI / SƒCHSI
    //ledmatrix_timerepr[7] = 0b000000111111; // VIERI / ZW÷LFI
    //ledmatrix_timerepr[8] = 0b000000000000; // ELFI / SIEBNI
    //ledmatrix_timerepr[9] = 0b000000000000; // ACHTI / ZƒHNI

}

void ledmatrix_display_row( uint16_t row_value )
{
    LEDMATRIX__OE_PIN = 1;

    int i;
    for (i = 0; i < LED_MATRIX_NUM_COLS; i++)
    {
        volatile uint16_t temp = (row_value>>i) & 0x01;
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
    
    volatile uint16_t temp1 = 0x00;
    volatile uint16_t temp2 = 0x00;
    temp1 |= ~(1L<<current_row & LEDMATRIX_ANODE_MASK_1);
    temp2 |= ~((1L<<current_row)>>2 & LEDMATRIX_ANODE_MASK_2);
    
    /* Select current row */
    LEDMATRIX_ANODE_PORT_1 &= ~LEDMATRIX_ANODE_MASK_1;
    LEDMATRIX_ANODE_PORT_2 &= ~LEDMATRIX_ANODE_MASK_2;
    LEDMATRIX_ANODE_PORT_1 |= ~(1L<<current_row & LEDMATRIX_ANODE_MASK_1);
    LEDMATRIX_ANODE_PORT_2 |= ~((1L<<current_row)>>8 & LEDMATRIX_ANODE_MASK_2);

    ledmatrix_display_row(ledmatrix_timerepr[current_row]);
    
    current_row++;
    current_row %= LEDMATRIX_NUM_ROWS; // current_row can't be larger than LEDMATRIX_NUM_ROWS
}
