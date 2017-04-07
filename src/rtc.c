
#include "rtc.h"
#include "i2c.h"

void rtc_init()
{
    volatile uint8_t seconds = 13;
    seconds = i2c_read_reg(RTC_I2C_ADDR, 0x01) & 0b00001111;
    volatile uint8_t waitHere = 0;
}