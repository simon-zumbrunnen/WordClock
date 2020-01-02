
#include "config.h"
#include "fuses.h"

#include "i2c.h"
#include "rtc.h"
#include "ledmatrix.h"
#include "timer.h"

#include <xc.h>

volatile static uint8_t time_changed = 1;
static time_t display_time = {0, 0, 0};

static void interrupt timer_isr(void)
{
    TMR1IF = 0;   // clear timer 1 interrupt flag
    TMR1H = 0x0B; // set high timer1 reg to 0xff
    TMR1L = 0xDC; // set low timer1 reg to 0xff
    
    time_t current_time = rtc_read_time();
        
    current_time.minute++;
    
    if (
               (current_time.hour   != display_time.hour  )
            || (current_time.minute != display_time.minute)
            || (current_time.second != display_time.second)
        )
    {
        display_time = current_time;
        time_changed = 1;
    }
}

uint8_t main( void )
{
    i2c_init();
    rtc_init();
    ledmatrix_init();
    timer_init();
    
    time_t init_time = {16, 47, 0};
    rtc_write_time(init_time);
    
    while(1)
    {
        if (time_changed)
        {
            time_changed = 0;
            ledmatrix_set_time(display_time);
        }
        
        ledmatrix_display_next_row();
    }
    
    return 0;
}
