#include "ic_rgb.h"

extern key_data key1;

void delay_my(int t)
{

	for (int i = 0; i < t; i++)
	{
	}
}
// char count = 0;  /* 计数变量，用于旋转跑马灯计数用 */
char color_rgb[16][3] = {
    {255, 182, 193},
    {255, 20, 147},
    {255, 0, 255},
    {0, 0, 255},
    {30, 144, 255},
    {0, 255, 255},
    {0, 250, 154},
    {50, 205, 50},
    {255, 255, 0},
    {255, 165, 0},
    {255, 140, 0},
    {255, 69, 0},
    {250, 128, 114},
    {255, 0, 0},
    {128, 0, 0},
    {255, 255, 255},
};

void RGB_WriteByte(char dat)
{
	char i;
	for (i = 0; i < 8; i++)
	{
		dat <<= i;
		if (dat & 0x80) // 判断最高位
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		}
	}
}
/* 输出LED数据 */
void RGB_ColorSet(char red, char green, char blue)
{
	RGB_WriteByte(green);
	RGB_WriteByte(red);
	RGB_WriteByte(blue);
}

void RGB_LEDReset()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	delay_my(800);
}

void Task_ic_rgb(void const *argument)
{

	for (;;)
	{
		// RGB_RandomColor(10);

		for (int i = 0; i < 16; i++)
		{
			key1.key[i] ? RGB_ColorSet(0, 0, 0) : RGB_ColorSet(50, 0, 0);
		}

		osDelay(80);
	}
}

/* 关闭 i 个 LED */
void RGB_RandomColor_off(void)
{
	char red, green, blue;

	red = 0;
	green = 0;
	blue = 0;

	RGB_ColorSet(red, green, blue);
}
