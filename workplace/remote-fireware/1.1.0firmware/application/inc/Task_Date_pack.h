#ifndef _date_pack_
#define _date_pack_



#include "includes.h"


typedef __packed struct
{
	int16_t  ch[5];
	uint8_t  key[16];
	uint8_t	 cmd;
}remote_data;


typedef union
{
	int16_t ch[5];
	uint8_t ch_port[10];//�Ͱ�λ��ǰ  �߰�λ�ں�

} ch_transform;







#endif

