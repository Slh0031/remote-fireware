#include "Task_adc.h"

extern ADC_HandleTypeDef hadc1;
// float get_adc_value(void)
//{
//	HAL_ADC_Start (&hadc1);//第一步，开启ADC
//	HAL_ADC_PollForConversion (&hadc1,50);// 查询函数，等着ADC 转换，查询转换的标志位.
//	if (HAL_IS_BIT_SET (HAL_ADC_GetState(&hadc1),HAL_ADC_STATE_REG_EOC)) //判断ADC是否转换完成,判断EOC标志位
//	{
//		return HAL_ADC_GetValue(&hadc1) * 3.3 /4096; //  获取ADC的值，并转换为对应的电压
//	}
//	else return 0;
// }
 
#define adc_conversion_times 5
uint16_t adc_buffer[adc_channel_number * adc_conversion_times];
int ch_buffer[adc_channel_number];

float ad2, ad1;
// uint32_t get_adc_value()
//{
//	for (i = 0, ad1 = 0, ad2 = 0; i < 100; i++)
//	{
//		ad1 += adc_value[i++];
//		ad2 += adc_value[i++];
//	}
//	ad1 = adc_value[0];
//	ad2 = adc_value[1];

//	ad1 /= 50;
//	ad2 /= 50;
//}

// unsigned long kalman_filter1(unsigned long ADC_Value)
//{
//	float x_k1_k1, x_k_k1;
//	static float ADC_OLD_Value;
//	float Z_k;
//	static float P_k1_k1;

//	static float Q = 0.0001;
//	static float R = 0.005;
//	static float Kg = 0;
//	static float P_k_k1 = 1;

//	float kalman_adc;
//	static float kalman_adc_old = 0;
//	Z_k = ADC_Value;
//	x_k1_k1 = kalman_adc_old;

//	x_k_k1 = x_k1_k1;
//	P_k_k1 = P_k1_k1 + Q;

//	Kg = P_k_k1 / (P_k_k1 + R);

//	kalman_adc = x_k_k1 + Kg * (Z_k - kalman_adc_old);
//	P_k1_k1 = (1 - Kg) * P_k_k1;
//	P_k_k1 = P_k1_k1;

//	ADC_OLD_Value = ADC_Value;
//	kalman_adc_old = kalman_adc;

//	return kalman_adc;
//}
#define N 12 // 滤波参数:最大抖动次数
#define M 4  // 滤波参数：除数
uint16_t adc_value[adc_channel_number], new_adc_value[adc_channel_number];
uint8_t count[adc_channel_number]; // 每个通道的滤波计数器
uint8_t dma_flag = 0;		   // dma标志位
uint16_t zero_set[adc_channel_number] =
    {
	0,
	521,
	523,
	454,
	521

};
    #define static_error 15  //0点静态误差
extern remote_data Remote_Data;
#include "math.h"
void Task_adc(void const *argument)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_buffer, adc_channel_number * adc_conversion_times);
	for (;;)
	{

		if (dma_flag)
		{
			uint16_t adc_min = 0, adc_max = 0, adc_add = 0;
			for (int i = 0; i < adc_channel_number; i++)
			{
				adc_add = 0;
				adc_min = adc_buffer[i];
				adc_max = adc_buffer[i];
				for (int e = 0; e < adc_conversion_times; e++)
				{
					adc_add += adc_buffer[i + e * adc_channel_number];
					adc_min = (adc_min > adc_buffer[i + e * adc_channel_number]) ? adc_buffer[i + e * adc_channel_number] : adc_min;
					adc_max = (adc_max < adc_buffer[i + e * adc_channel_number]) ? adc_buffer[i + e * adc_channel_number] : adc_max;
				}

				new_adc_value[i] = (adc_add - adc_min - adc_max) / (adc_conversion_times - 2) / M;

				while (adc_value[i] != new_adc_value[i]) // 消抖滤波
				{
					count[i]++;
					if (count[i] >= N)
					{
						adc_value[i] = new_adc_value[i];
						count[i] = 0;
					}
				}
				ch_buffer[i] = adc_value[i] - zero_set[i];
				if (fabs((int)ch_buffer[i]) < static_error)//消除静态误差
				{
					ch_buffer[i] = 0;
				}
				if (i != 0)  //忽略第一个通道
				{

					if (ch_buffer[i] > 300)
					{
						ch_buffer[i] = 300;
					}
					if (ch_buffer[i] < -300)
					{
						ch_buffer[i] = -300;
					}
				}

				for (int c = 0; c < adc_channel_number; c++)
				{
					Remote_Data.ch[i] = ch_buffer[i];
				}
			}
			dma_flag = 0;
		}

		osDelay(10);
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) // 回调函数
{
	dma_flag = 1;
}
