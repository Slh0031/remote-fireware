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

void Music_power_on(void) // ����
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
void Music_step(void) // ����
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
void Music_step2(void) // ����
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

//    int length = sizeof(promising_young)/sizeof(promising_young[0]);//�������鳤��
//    for(int i=0; i<(length/2); i++)//ȡ��������
//    {
//        buzzer_on(promising_young[2*i], 200);
//        osDelay(5*promising_young[2*i+1]);//������ʱ�䶼����5��һ��Ϊ500΢�룬��ֵ"5"�ɵ�����ֻ�ǲ��ŵ������������ѣ��е���������Ƶ����ͺ���
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
//		M6,50,M7,50,H1,50,H2,50,M7,50,H1,50,H1,100,Z0,10,	//��������߰���
//		H1,50,M7,50,H1,50,H2,50,M7,50,H1,50,H1,100,Z0,10, 	//���㲻���ģ��
//		H1,50,H2,50,H3,50,H2,50,H3,50,H2,50,H3,100,H3,50,H3,50,H2,50,H3,100,H5,100,H3,100,Z0,10 //������Ź��������Ͽ�һ��
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
//	{	//��һ·������ͣͣ ˳������Ư���ĺۼ�
////	//	M2,50,M2,50,M1,25,M2,50,M2,50,M1,25,M2,50,M3,50,M5,50,M3,50, M2,50,M2,50,M1,25,M2,50,M2,50,M1,25,M2,25,M3,25,M2,25,M1,25,L6,100,Z0,10,
////	//	//������վ��ǰһ�� ����Щ��ԥ
////	//	M2,50,M2,50,M1,25,M2,50,M2,50,M1,25,M2,50,M3,50,M5,50,M3,50, M2,50,M2,50,M3,25,M2,50,M1,50,M2,100,Z0,50,
////	//	//����Ц����������� ���޷�����
////	//	M2,50,M2,50,M1,25,M2,50,M2,50,M1,25,M2,50,M3,50,M5,50,M3,50, M2,50,M2,50,M3,25,M2,50,M1,50,L6,100,Z0,10,
//		//����Ұ���� ������ôů �紵���˴�ǰ
////		M3,25,M2,25,M1,25,M2,25,M1,100, M3,25,M2,25,M1,25,M2,25,M1,50,M1,50, M5,25,M3,25,M2,25,M1,25,M2,25,M1,100,M1,150,Z0,30,
////		//��ǰ��ʶ������ ������� �������������ǰ Ҳ��Ը��������ȥ����һ��
////		M1,50,M2,50,M3,50,M1,50,M6,50,M5,25,M6,25,M6,50,M6,50, M1,25,M7,50,M6,25,M7,25,M7,100,Z0,5, M7,50,M6,25,M7,25,M7,50,M3,50,H1,25,H2,25,H1,25,M7,25,M6,50,M5,50, M6,50,M5,25,M6,25,M6,25,M5,25,M6,25,M5,25,M6,50,M5,25,M2,25,M2,25,M5,50,M5,50,M3,100,M3,100,Z0,25,
////		//����߹������� ������� �������²�ͬ���� �벻�����������Ц��
////		M1,50,M2,50,M3,50,M1,50,M6,50,M5,25,M6,25,M6,50,M6,50, M1,25,M7,50,M6,25,M7,25,M7,100,Z0,5, M7,50,M6,25,M7,25,M7,50,M3,50,H1,25,H2,25,H1,25,M7,25,M6,50,M5,50, M6,50,H3,25,H3,25,H3,50,M5,50,M6,50,H3,25,H3,25,H3,25,M5,50,M6,25,M6,100,M6,100,M6,100,Z0,25,
////		//�������԰�������֮�� Ҳ�����������λ�
////		H1,50,H2,50,H3,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H2,25,H3,25,H3,50, H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,25,H3,50,H3,50,
////		//������� �������� ����Ц��
//		H2,50,H1,25,M6,25,M6,25,H1,50, M6,25,H2,25,H1,25,M6,50,M6,25,H1,50,H1,50, H3,100,H3,25,H4,25,H3,50,H3,25,H2,50,H2,50,Z0,25,
//		//�������ഺ��ӿ���� Ҳ��ָ�ⵯ��ʢ�� ��֮�����Ҿ���Եȥ��
////		H1,50,H2,50,H3,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H2,50, H3,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H6,25,H5,25,H5,50,H3,50,H3,50, H2,50,H1,25,M6,25,M6,25,H3,50,H3,50, H2,50,H1,25,M6,25,M6,25,H1,50,H1,50,H1,100,H1,100,Z0,10,
////		//���Ź������η紵����
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
