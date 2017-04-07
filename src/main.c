
#include "config.h"
#include "fuses.h"
#include "time.h"
#include "i2c.h"
#include "rtc.h"
#include "ledmatrix.h"

#include <xc.h>

uint8_t main( void )
{
    i2c_init();
    rtc_init();
    ledmatrix_init();
    
    time_t time = {14, 50, 12};
    rtc_write_time(time);
    time = rtc_read_time();
    
    ledmatrix_set_time(time);
    
    while(1)
    {
        ledmatrix_display_next_row();
    }
    
    return 0;
}
