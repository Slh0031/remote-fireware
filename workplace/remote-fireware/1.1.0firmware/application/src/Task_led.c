#include "Task_led.h"
mode led_mode;

void Task_led(void const *argument)
{

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);
	while (1)
	{
		if (led_mode.flage == 0) //
		{

			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
			osDelay(500);
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
			osDelay(500);
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
			osDelay(500);
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
		}

		osDelay(500);
	}
}
