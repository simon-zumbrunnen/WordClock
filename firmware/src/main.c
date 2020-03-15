
#include "config.h"
#include "fuses.h"
#include "config.h"
#include "uart.h"
#include "ledmatrix.h"

#include <xc.h>

static uint16_t timerepr[LEDMATRIX_NUM_ROWS];
volatile static int word_count = 0;
volatile static int byte_count = 0;

int main( void )
{
    // Set clock to 8 MHz
    IRCF0 = 1;
    IRCF1 = 1;
    IRCF2 = 1;
    
    ledmatrix_init();
    uart_init(9600);
        
    while(1)
    {   
        ledmatrix_display_next_row();
    }
    
    return 0;
}

void __interrupt () interrupt_service_routine (void)
{
    if (RCIF == 1)
        { 
        static char low_data;
        static char high_data;
        uint16_t whole_data;
        char data = uart_read();
        
        if (byte_count % 2 == 0) {
            high_data = data;
        } else {
            uart_write(word_count);
            
            low_data = data;
            whole_data = (high_data<<8) + low_data;
            
            switch(whole_data) {
                case 0x1fff:
                    word_count = 0;
                    break;
                case 0xffff:
                    ledmatrix_set_timerepr(timerepr);
                    break;
                default:
                    timerepr[word_count] = whole_data;
                    word_count++;
            }
        }
        
        byte_count++;
        RCIF = 0;
    }
}
