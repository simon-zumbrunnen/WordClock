
#include "config.h"
#include "rtc.h"
#include "i2c.h"
#include "time.h"

#include <xc.h>

void rtc_init()
{
	i2c_start();
	i2c_write(0b11010000); // Device address (write)
	i2c_write(0b00001000); // Start at reg 08
	i2c_write(0b00000000); // 08 No calibration
	i2c_write(0b10000000); // 09 Osc fail interrupt enabled
	i2c_write(0b00000000); // 0A Alarm interrupt !enabled
	i2c_write(0b11000000); // 0B Alarm every minute
	i2c_write(0b10000000); // 0C
	i2c_write(0b10000000); // 0D
	i2c_write(0b00000000); // 0E
	i2c_stop();
    
	__delay_ms(1);
}

uint8_t rtc_read(uint8_t reg_adr)
{
	uint8_t reg_value;
    
	i2c_start();
	i2c_write(0b11010000); // Device address (write)
	i2c_write(reg_adr);
    
	i2c_rep_start();
	i2c_write(0b11010001); // Device address (read)
	reg_value = i2c_read(I2C_NACK);
	i2c_stop();
    
	return reg_value;
}

void rtc_write(uint8_t reg_adr, uint8_t reg_value)
{
	i2c_start();
	i2c_write(0b11010000); // Device address (write)
	i2c_write(reg_adr);
	i2c_write(reg_value);
	i2c_stop();
}

time_t rtc_read_time()
{
    time_t time;
    time.second = bcd7_to_int(rtc_read(0x01));
    time.minute = bcd7_to_int(rtc_read(0x02));
	time.hour = bcd6_to_int(rtc_read(0x03));
    
    return time;
}

void rtc_write_time(time_t time)
{
	rtc_write(0x00, 0); //0.1 seconds and 0.01 seconds = 0
       
	rtc_write(0x01, int_to_bcd(time.second));
	rtc_write(0x02, int_to_bcd(time.minute));
	rtc_write(0x03, int_to_bcd(time.hour));
}
	
inline uint8_t bcd7_to_int(uint8_t bcd_val)
{
	uint8_t int_val;
    
	int_val = bcd_val & 0b00001111;
	int_val += (bcd_val>>4 & 0b00000111)*10;
    
	return int_val;
}

inline uint8_t bcd6_to_int(uint8_t bcd_val)
{
	uint8_t int_val;
    
	int_val = bcd_val & 0b00001111;
	int_val += (bcd_val>>4 & 0b00000011)*10;
    
	return int_val;
}

inline uint8_t int_to_bcd(uint8_t int_val)
{
	uint8_t bcd_val;
    
	bcd_val = (int_val/10)<<4;
	bcd_val += int_val%10;
	
	return bcd_val;
}