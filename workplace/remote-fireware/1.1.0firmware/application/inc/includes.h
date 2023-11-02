#ifndef _includes_h_
#define _includes_h_



#include "main.h"
#include "math.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "spi.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "Task_key.h"

#include "oled_menu.h"
#include "struct_typedef.h"
#include "Task_Date_pack.h"

#include "oled_iic.h"



 #include <stdio.h>
#include <stdlib.h>
typedef struct
{
	
unsigned char flage;
	
}mode;



#define adc_channel_number 5  //adc采集通道数量（用于摇杆的）

















#endif 
