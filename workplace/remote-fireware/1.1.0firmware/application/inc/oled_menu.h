#ifndef _oled_menu_
#define _oled_menu_

#include "includes.h"
typedef struct
{
    uint8_t current;//��ǰ״̬������
    uint8_t next; //����һ��
    uint8_t enter; //ȷ��
    void (*current_operation)(void); //��ǰ״̬Ӧ��ִ�еĲ���  ִֻ��һ�Σ���̬������
	void (*current_operation_dynamics)(void);//��ǰҳ�涯̬ ��ʾ���� ����̬������
} Menu ;



#endif
