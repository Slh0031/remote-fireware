#include "Task_buzzer.h"

extern TIM_HandleTypeDef htim3;
uint8_t buzzer_mode = 0;

void buzzer_on(uint16_t psc, uint16_t pwm)
{
	__HAL_TIM_PRESCALER(&htim3, psc);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, pwm);
}
void buzzer_off(void)
{
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
}

void Music_power_on(void) // 开机
{

	int16_t music[] =
	    {
	        M5, 50, M6, 50, M7, 50, Z0, 10};
	int length = sizeof(music) / sizeof(music[0]);
	for (uint8_t i = 0; i < (length / 2); i++)
	{
		buzzer_on(music[i * 2], 500);
		osDelay(5 * music[i * 2 + 1]);
	}
	buzzer_off();
}
void Music_step(void) // 开机
{

	int16_t music[] =
	    {
	        H7, 40, Z0, 100};
	int length = sizeof(music) / sizeof(music[0]);
	for (uint8_t i = 0; i < (length / 2); i++)
	{
		buzzer_on(music[i * 2], 500);
		osDelay(3 * music[i * 2 + 1]);
	}
	buzzer_off();
}
void Music_step2(void) // 开机
{

	int16_t music[] =
	    {
	        M7, 40, Z0, 100};
	int length = sizeof(music) / sizeof(music[0]);
	for (uint8_t i = 0; i < (length / 2); i++)
	{
		buzzer_on(music[i * 2], 500);
		osDelay(3 * music[i * 2 + 1]);
	}
	buzzer_off();
}

void myTask_buzzer(void const *argument)
{

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	Music_power_on();

	while (1)
	{
		if (buzzer_mode == 1)
		{
			Music_step();
			buzzer_mode = 0;
			osDelay(800);
			
		}
		else if (buzzer_mode == 2)
		{
			Music_step2();
			buzzer_mode = 0;
		}

		osDelay(20);
	}
}

/**
 * NAME: void promising_young(void)
 * FUNCTION : promising_young
 */
// void promising_young(void)
//{
//     int promising_young[]=
//     {
//         M5,50,M6,50,H1,50,Z0,10,H2,50,   Z0,10,H2,50,Z0,1,H2,50, Z0,1, H1,50, Z0,1,H2,50,   Z0,15, H1,50, Z0,15,H3,50,  Z0,15,Z0,50,
//         M7,40,Z0,10,M7,40,Z0,10,M7,40,Z0,10,M7,75,Z0,15,M7,50, Z0,25, M6,25, Z0,25, H1,25,Z0,25

//    };

//    int length = sizeof(promising_young)/sizeof(promising_young[0]);//计算数组长度
//    for(int i=0; i<(length/2); i++)//取数组数据
//    {
//        buzzer_on(promising_young[2*i], 200);
//        osDelay(5*promising_young[2*i+1]);//音长的时间都乘以5即一拍为500微秒，此值"5"可调整，只是播放的整个快慢而已，有点类似于视频快进和后退
//    }
//}

/**
 * NAME: void Solitary_brave(void)
 * FUNCTION : Solitary_brave
 */
// void Solitary_brave(void)
//{
//	int16_t solitary_brave[]=
//	{
//		M6,50,M7,50,H1,50,H2,50,M7,50,H1,50,H1,100,Z0,10,	//爱你孤身走暗巷
//		H1,50,M7,50,H1,50,H2,50,M7,50,H1,50,H1,100,Z0,10, 	//爱你不跪的模样
//		H1,50,H2,50,H3,50,H2,50,H3,50,H2,50,H3,100,H3,50,H3,50,H2,50,H3,100,H5,100,H3,100,Z0,10 //爱你对峙过绝望不肯哭一场
//
//	};
//	int length = sizeof(solitary_brave)/sizeof(solitary_brave[0]);
//	for(uint8_t i=0;i<(length/2);i++)
//	{
//		buzzer_on(solitary_brave[i*2],500);
//		osDelay(5*solitary_brave[i*2+1]);
//	}
// }

/**
 * NAME: void Wind_Rises(void)
 * FUNCTION : Wind_Rises
 */
// void Wind_Rises(void)
//{
//	int wind_rise[]=
//	{	//这一路上走走停停 顺着少年漂流的痕迹
////	//	M2,50,M2,50,M1,25,M2,50,M2,50,M1,25,M2,50,M3,50,M5,50,M3,50, M2,50,M2,50,M1,25,M2,50,M2,50,M1,25,M2,25,M3,25,M2,25,M1,25,L6,100,Z0,10,
////	//	//迈出车站的前一刻 竟有些犹豫
////	//	M2,50,M2,50,M1,25,M2,50,M2,50,M1,25,M2,50,M3,50,M5,50,M3,50, M2,50,M2,50,M3,25,M2,50,M1,50,M2,100,Z0,50,
////	//	//不仅笑着这近乡情怯 仍无法避免
////	//	M2,50,M2,50,M1,25,M2,50,M2,50,M1,25,M2,50,M3,50,M5,50,M3,50, M2,50,M2,50,M3,25,M2,50,M1,50,L6,100,Z0,10,
//		//而长野的天 依旧那么暖 风吹起了从前
////		M3,25,M2,25,M1,25,M2,25,M1,100, M3,25,M2,25,M1,25,M2,25,M1,50,M1,50, M5,25,M3,25,M2,25,M1,25,M2,25,M1,100,M1,150,Z0,30,
////		//从前初识这世间 万般留恋 看着天边似在眼前 也甘愿赴汤蹈火去走它一遍
////		M1,50,M2,50,M3,50,M1,50,M6,50,M5,25,M6,25,M6,50,M6,50, M1,25,M7,50,M6,25,M7,25,M7,100,Z0,5, M7,50,M6,25,M7,25,M7,50,M3,50,H1,25,H2,25,H1,25,M7,25,M6,50,M5,50, M6,50,M5,25,M6,25,M6,25,M5,25,M6,25,M5,25,M6,50,M5,25,M2,25,M2,25,M5,50,M5,50,M3,100,M3,100,Z0,25,
////		//如今走过这世间 万般留恋 翻过岁月不同侧脸 措不及防闯入你的笑颜
////		M1,50,M2,50,M3,50,M1,50,M6,50,M5,25,M6,25,M6,50,M6,50, M1,25,M7,50,M6,25,M7,25,M7,100,Z0,5, M7,50,M6,25,M7,25,M7,50,M3,50,H1,25,H2,25,H1,25,M7,25,M6,50,M5,50, M6,50,H3,25,H3,25,H3,50,M5,50,M6,50,H3,25,H3,25,H3,25,M5,50,M6,25,M6,100,M6,100,M6,100,Z0,25,
////		//我曾难自拔与世界之大 也沉溺于其中梦话
////		H1,50,H2,50,H3,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H2,25,H3,25,H3,50, H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,25,H3,50,H3,50,
////		//不得真假 不做挣扎 不惧笑话
//		H2,50,H1,25,M6,25,M6,25,H1,50, M6,25,H2,25,H1,25,M6,50,M6,25,H1,50,H1,50, H3,100,H3,25,H4,25,H3,50,H3,25,H2,50,H2,50,Z0,25,
//		//我曾将青春翻涌成她 也曾指尖弹出盛夏 心之所动且就随缘去吧
////		H1,50,H2,50,H3,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H2,50, H3,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H3,50,H3,50, H2,50,H1,25,M6,25,M6,25,H3,50,H3,50, H2,50,H1,25,M6,25,M6,25,H1,50,H1,50,H1,100,H1,100,Z0,10,
////		//逆着光行走任风吹雨打吧
////		M6,25,H3,50,H3,50,H2,50,H1,25,M6,25,M6,25,H3,50,H2,50,H1,25,M6,25,M6,25,H1,50,H1,50,H1,50,H1,100,Z0,10,
//	};
//	int length = sizeof(wind_rise)/sizeof(wind_rise[0]);
//
//	for(int i=0;i<(length/2);i++)
//	{
//		buzzer_on(wind_rise[i*2],260);
//		osDelay(wind_rise[i*2+1]*5);
//	}
//}
