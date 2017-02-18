
#include "config.h"
#include "fuses.h"
#include "ledmatrix.h"

#include <xc.h>

uint8_t main( void )
{      
    ledmatrix_init();
    datetime_t time;
    ledmatrix_set_time(time);
    
    while(1)
    {
        ledmatrix_display_next_row();
    }
    
    return 0;
}
