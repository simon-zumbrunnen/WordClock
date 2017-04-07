
#include "config.h"
#include "fuses.h"
#include "ledmatrix.h"

#include <xc.h>

uint8_t main( void )
{      
    ledmatrix_init();
    time_t time;
    
    uint8_t i, j, k;
    for (i = 0; i < 24; i++)
    {
        time.hour = i;
        
            for (j = 0; j < 60; j++)
            {
                time.minute = j;
                ledmatrix_set_time(time);
                
                for (k = 0; k < 50; k++)
                {
                    ledmatrix_display_next_row();
                }
            }  
    }
    
    while(1)
    {
        ledmatrix_display_next_row();
    }
    
    return 0;
}
