
#include "config.h"
#include "fuses.h"
#include "ledmatrix.h"

#include <xc.h>

uint8_t main( void )
{  
    ledmatrix_init();
    
    while(1)
    {
        ledmatrix_display_next_row();
        __delay_ms(1000);
    }
    
    return 0;
}
