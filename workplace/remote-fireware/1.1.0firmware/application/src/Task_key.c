#include "Task_key.h"
extern SPI_HandleTypeDef hspi1;

key_data key1;

void key_any(key_data *key)
{
	for (int i = 0; i < 8; i++)
	{
		key->key[i] = (key->pData2[0] & (1 << i)) >> i;
	}
	for (int i = 0; i < 8; i++)
	{
		key->key[i + 8] = (key->pData2[1] & (1 << i)) >> i;
	}
}

void Task_key(void const *argument)
{
	for (;;)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET); // ce 失能时钟
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  // pl使能  读值
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET); // ce
		HAL_SPI_Receive(&hspi1, key1.pData2, 2, 20);	       // 输出
		key_any(&key1);

		osDelay(10);
	}
}
