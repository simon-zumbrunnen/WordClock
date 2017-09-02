
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
    /* Clear all leds */
    uint8_t i;
    for (i = 0; i < LEDMATRIX_NUM_ROWS; i++)
    {
        ledmatrix_timerepr[i] = 0b000000000000;
    }

    /* ES ISCH */
    {
        ledmatrix_timerepr[0] |= ESIST;
    }
    
    uint8_t min = time.minute;
    uint8_t h = time.hour;

    /* VOR next hour */
    if ( min > 22 )
    {
        h++;
    }      
  
    
    /* Decide between VOR and AB */
    if (( min > 2 && min < 23 ) || ( min > 32 && min < 38 ))
    {
        ledmatrix_timerepr[3] |= AB;
    }
    else if (( min > 22 && min < 29 ) || ( min > 37 && min < 58 ))
    {
        ledmatrix_timerepr[3] |= VOR;
    }
    
        
    if (    ( min >  2 && min <  8 ) 
         || ( min > 22 && min < 28 )
         || ( min > 32 && min < 38 )
         || ( min > 52 && min < 58 )
       )
    {
        ledmatrix_timerepr[1] |= FUENFAB;
    }
    else if (   ( min >  7 && min < 13 ) 
             || ( min > 47 && min < 53 )
            )
    {
        ledmatrix_timerepr[2] |= ZEHNAB;
    }
    else if (   ( min > 12 && min < 18 ) 
             || ( min > 42 && min < 48 )
            )
    {
        ledmatrix_timerepr[1] |= VIERTEL;
    }
    else if (   ( min > 17 && min < 23 ) 
             || ( min > 37 && min < 43 )
            )
    {
        ledmatrix_timerepr[2] |= ZWANZIG;
    }
    
    if (   ( min > 22 && min < 38 ) 
             )
    {
        ledmatrix_timerepr[4] |= HALB;
    }
        
    switch (h)
    {
        case 0:
        case 12:
        case 24:
            ledmatrix_timerepr[7] |= ZWOELF; // ZW�LFI         
            break;
        case 1:
        case 13:
            ledmatrix_timerepr[5] |= EINS; // EIS
            break;
        case 2:
        case 14:
            ledmatrix_timerepr[6] |= ZWEI; // ZWEI
            break;
        case 3:
        case 15:
            ledmatrix_timerepr[5] |= DREI; //  DR�
            break;
        case 4:
        case 16:
            ledmatrix_timerepr[7] |= VIER; //  VIERI
            break;           
        case 5:
        case 17:
            ledmatrix_timerepr[5] |= FUENF; // F�IFI
            break;
        case 6:
        case 18:
            ledmatrix_timerepr[6] |= SECHS; // S�CHSI
            break;
        case 7:
        case 19:
            ledmatrix_timerepr[8] |= SIEBEN; // SIEBNI
            break; 
        case 8:
        case 20:
            ledmatrix_timerepr[9] |= ACHT; // ACHTI
            break;
        case 9:
        case 21:
            ledmatrix_timerepr[4] |= NEUN; // N�NI
            break;
        case 10:
        case 22:
            ledmatrix_timerepr[9] |= ZEHN; // Z�HNI
            break;
        case 11:
        case 23:
            ledmatrix_timerepr[8] |= ELF; // ELFI
            break;            
        default:
            break;
    }     
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
