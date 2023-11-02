#ifndef _oled_menu_
#define _oled_menu_

#include "includes.h"
typedef struct
{
    uint8_t current;//当前状态索引号
    uint8_t next; //向下一个
    uint8_t enter; //确定
    void (*current_operation)(void); //当前状态应该执行的操作  只执行一次（静态操作）
	void (*current_operation_dynamics)(void);//当前页面动态 显示变量 （动态操作）
} Menu ;



#endif
