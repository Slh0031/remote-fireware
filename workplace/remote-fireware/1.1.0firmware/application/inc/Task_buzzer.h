#ifndef _buzzer_
#define _buzzer_

#include "includes.h"


#define  proport          72000 	//Tclk/(arr+1)=72000000/(1000)

//����Tout= ((arr+1)*(psc+1))/Tclk�Ƴ�pscֵ���Ǳ���define�����ֵ��ToutΪ����Ƶ��131Hz�ĵ�����Tclk=72MHz                                                
#define  L1       ((proport/262)-1)//�͵���do ��Ƶ��
#define  L2       ((proport/296)-1)//�͵���re ��Ƶ��
#define  L3       ((proport/330)-1)//�͵���mi ��Ƶ��
#define  L4       ((proport/349)-1)//�͵���fa ��Ƶ��
#define  L5       ((proport/392)-1)//�͵���sol��Ƶ��
#define  L6       ((proport/440)-1)//�͵���la ��Ƶ��
#define  L7       ((proport/494)-1)//�͵���si ��Ƶ��
                                               
#define  M1       ((proport/523)-1)//�е���do ��Ƶ��
#define  M2       ((proport/587)-1)//�е���re ��Ƶ��
#define  M3       ((proport/659)-1)//�е���mi ��Ƶ��
#define  M4       ((proport/699)-1)//�е���fa ��Ƶ��
#define  M5       ((proport/784)-1)//�е���sol��Ƶ��
#define  M6       ((proport/880)-1)//�е���la ��Ƶ��
#define  M7       ((proport/988)-1)//�е���si ��Ƶ��

#define  H1       ((proport/1048)-1)//�ߵ���do ��Ƶ��
#define  H2       ((proport/1176)-1)//�ߵ���re ��Ƶ��
#define  H3       ((proport/1320)-1)//�ߵ���mi ��Ƶ��
#define  H4       ((proport/1480)-1)//�ߵ���fa ��Ƶ��
#define  H5       ((proport/1640)-1)//�ߵ���sol��Ƶ��
#define  H6       ((proport/1760)-1)//�ߵ���la ��Ƶ��
#define  H7       ((proport/1976)-1)//�ߵ���si ��Ƶ��

#define  Z0       0//

void Solitary_brave(void);
void Wind_Rises(void);

extern void buzzer_on(uint16_t psc, uint16_t pwm);
extern void buzzer_off(void);

void Music_step(void);
 



















#endif
