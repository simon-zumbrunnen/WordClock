
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include <stdint.h>
#include <pic.h>

uint8_t main( void )
{  
    /* Configure anode pins as outputs */
    ANSEL = 0x00; // Disable analog inputs on Port A
    TRISA = 0x00;
    TRISD0 = 0;
    TRISD1 = 0;
    
    /* Deactivate all anodes */
    PORTA = 0xFF;
    RD0 = 1;
    RD1 = 1;
    
    /* Activate first anode */
    RA0 = 0;
    RA1 = 0;
    
    /* Configure LED-Driver-Interface pins as outputs */
    TRISD4 = 0;
    TRISD5 = 0;
    TRISD6 = 0;
    TRISD7 = 0;
    
    /* Bypass latches */
    RD6 = 1;
    
    /* Activate outputs */
    RD7 = 0;
    
    /* Turn off all cathodes */
    RD5 = 0; // clk = 0
    RD4 = 0; // data = 0
    
    for (uint8_t i = 0; i < 16; i++)
    {
        RD5 = 0; // clk = 0
        RD5 = 1; // clk = 1 (rising edge)   
    }
    
    /* Turn on first cathode */
    RD5 = 0; // clk = 0
    RD4 = 1; // data = 1
    RD5 = 1; // clk = 1 (rising edge)
    RD5 = 0; // clk = 0
    
    while(1);  
    return 0;
}
