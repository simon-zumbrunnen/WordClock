
#include "config.h"
#include "timer.h"

#include <xc.h>

#define SBIT_PS1  5
#define SBIT_PS0  4

void timer_init()
{
    T1CON = (1<<SBIT_PS1) | (1<<SBIT_PS0); // enable timer, prescaler = 1:8
    
    TMR1IF = 0;   // clear timer1 interrupt flag
    GIE = 1;      // enable interrupts
    PEIE = 1;     // enable peripheral interrupts
    TMR1IE = 1;   // enable timer1 interrupt
    TMR1H = 0x0B; // set high timer1 reg to 0xff
    TMR1L = 0xDC; // set low timer1 reg to 0xff
    TMR1ON = 1;   // start timer1
}
