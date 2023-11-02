/**
	*@author »úµç2201ËÕÀûê»
	*@note   i2c  oled   128*64ÏñËØ
	*@date   23/7/20
	*/
#ifndef _oled_iic_
#define _oled_iic_

#include "i2c.h"
#include "includes.h"
#include "u8g2.h"
					
uint8_t u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr);
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

void u8g2Init(u8g2_t *u8g2);
void draw(void);

#endif
