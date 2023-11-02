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
	uint8_t ch_port[10];//低八位在前  高八位在后

} ch_transform;







#endif

