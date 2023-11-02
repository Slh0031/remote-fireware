#include "gift.h"
#include "oled_menu.h"
extern remote_data Remote_Data;
extern key_data key1;
extern uint8_t buzzer_mode; // 蜂鸣器声音模式控制
uint8_t func_index, last_index;
u8g2_t u8g2;
// start
void draw_start(void); // start menu
// 一级菜单
void draw_work(void);
void draw_set(void);
// 二级菜单
void draw_back1(void);

void draw_calibration(void); // 校准
void draw_volume(void);      // 音量

void draw_workplace(void); // workplace （dynamics）   display variable
void draw_volume_subject(void);
void draw_calibration_subject(void);
void draw_null(void); // null action
Menu TABLE[] =
    {
        // 开始界面
        {0, 1, 1, draw_start, draw_null},
        // 一级菜单
        {1, 2, 3, draw_set, draw_null},   // set
        {2, 1, 6, draw_work, draw_null},  // work
		          // 二级菜单
        {3, 4, 1, draw_back1, draw_null}, // set->back1
        {4, 5, 8, draw_calibration, draw_null},
        {5, 3, 7, draw_volume, draw_null},
        {6, 6, 2, draw_workplace, draw_workplace},
        {7, 7, 5, draw_volume_subject, draw_null},
        {8, 8, 4, draw_calibration_subject, draw_null},

        //
};

void Task_oled_gui(void const *argument)
{
	osDelay(10);
	u8g2Init(&u8g2);
	for (;;)
	{
		if ((key1.key[0] == 0) || (key1.key[1] == 0))
		{
			osDelay(10);
			if (key1.key[1] == 0) // 按下   向下
			{
				func_index = TABLE[func_index].next;
				while (!key1.key[1]) // 删除此while循环是另一种按键效果
				{
					osDelay(1);
				}
			}
			else if (key1.key[0] == 0) // 按下  确定
			{
				func_index = TABLE[func_index].enter;
				while (!key1.key[0])
				{
					osDelay(1);
				}
			}
		}
		if (func_index == 0) // start
		{
			static uint8_t pages;
			u8g2_ClearBuffer(&u8g2);
			u8g2_SetFont(&u8g2, u8g2_font_unifont_t_polish);
			u8g2_SetFontDirection(&u8g2, 0); /*字体方向选择*/
			u8g2_DrawStr(&u8g2, 72, 10, "Vinci");
			u8g2_DrawStr(&u8g2, 72, 30, "1.1.0");
			u8g2_DrawStr(&u8g2, 72, 50, "By Slh");

			u8g2_DrawXBM(&u8g2, 0, 0, 64, 64, gImage_IMG00000[pages]);
			u8g2_SendBuffer(&u8g2);
			pages++;
			if (pages == 4)
			{
				pages = 0;
			}
			buzzer_mode = 1;
		}

		if (func_index != last_index)
		{

			u8g2_ClearBuffer(&u8g2);
			(*TABLE[func_index].current_operation)(); // 执行当前操作函数
			u8g2_SendBuffer(&u8g2);
			last_index = func_index;
		}
		if (TABLE[func_index].current_operation_dynamics != draw_null) // 如果动态操作的指针函数不为空，执行动态显示变量
		{
			u8g2_ClearBuffer(&u8g2);
			(*TABLE[func_index].current_operation_dynamics)();
			u8g2_SendBuffer(&u8g2);
		}

		osDelay(10);
	}
}

/*	好看的字体
	u8g2_font_7x13O_tf
	u8g2_font_7x13B_mf
	u8g2_font_crox1t_tr
	u8g2_font_unifont_t_polish
*/

void draw_start(void)
{

	u8g2_SetFont(&u8g2, u8g2_font_unifont_t_polish); // 字体选择
	u8g2_SetFontDirection(&u8g2, 0);	 // 字体方向设置
	u8g2_DrawStr(&u8g2, 72, 10, "Vinci");
	u8g2_DrawStr(&u8g2, 72, 30, "1.1.0");
	u8g2_DrawStr(&u8g2, 72, 50, "By Slh");

	buzzer_mode = 2; // buzzer mode 1

	for (int i = 0; i < 5; i++)
	{
		u8g2_DrawXBM(&u8g2, 0, 0, 64, 64, gImage_IMG00000[i]);
		u8g2_SendBuffer(&u8g2);
	}
}

void draw_null(void)
{ // null
}
void draw_work(void)
{
	buzzer_mode = 2;
	u8g2_SetFont(&u8g2, u8g2_font_unifont_t_polish);
	u8g2_DrawStr(&u8g2, 5, 15, "set");
	u8g2_DrawStr(&u8g2, 5, 30, "work");
	u8g2_DrawXBMP(&u8g2, 40, 15, 25, 18, gImage_CAT_25_18);
}
void draw_set(void)
{
	buzzer_mode = 2;
	u8g2_SetFont(&u8g2, u8g2_font_unifont_t_polish);
	u8g2_DrawStr(&u8g2, 5, 15, "set");
	u8g2_DrawStr(&u8g2, 5, 30, "work");
	u8g2_DrawXBMP(&u8g2, 40, 0, 25, 18, gImage_CAT_25_18);
}
// 二级菜单
void draw_back1(void)
{
	buzzer_mode = 2;
	u8g2_SetFont(&u8g2, u8g2_font_unifont_t_polish);
	u8g2_DrawStr(&u8g2, 5, 15, "back");
	u8g2_DrawStr(&u8g2, 5, 30, "calibration");
	u8g2_DrawStr(&u8g2, 5, 45, "volume");
	u8g2_DrawXBMP(&u8g2, 40, 0, 25, 18, gImage_CAT_25_18);
}

void draw_calibration(void) // 校准
{
	buzzer_mode = 2;
	u8g2_SetFont(&u8g2, u8g2_font_unifont_t_polish);
	u8g2_DrawStr(&u8g2, 5, 15, "back");
	u8g2_DrawStr(&u8g2, 5, 30, "calibration");
	u8g2_DrawStr(&u8g2, 5, 45, "volume");
	u8g2_DrawXBMP(&u8g2, 95, 15, 25, 18, gImage_CAT_25_18);
}
void draw_volume(void)
{
	buzzer_mode = 2;
	u8g2_SetFont(&u8g2, u8g2_font_unifont_t_polish);
	u8g2_DrawStr(&u8g2, 5, 15, "back");
	u8g2_DrawStr(&u8g2, 5, 30, "calibration");
	u8g2_DrawStr(&u8g2, 5, 45, "volume");
	u8g2_DrawXBMP(&u8g2, 55, 30, 25, 18, gImage_CAT_25_18);
}

void draw_workplace(void)
{
	
	static char buffer[5][10];
	for (int i = 0; i < 5; i++)
	{
		sprintf(buffer[i], "%d", Remote_Data.ch[i]);
	}

	u8g2_SetFont(&u8g2, u8g2_font_profont11_mr);

	u8g2_DrawStr(&u8g2, 2, 10, "ch[1]:");
	u8g2_DrawStr(&u8g2, 38, 10, buffer[0]);

	u8g2_DrawStr(&u8g2, 2, 20, "ch[2]:");
	u8g2_DrawStr(&u8g2, 38, 20, buffer[1]);

	u8g2_DrawStr(&u8g2, 2, 30, "ch[3]:");
	u8g2_DrawStr(&u8g2, 38, 30, buffer[2]);

	u8g2_DrawStr(&u8g2, 2, 40, "ch[4]:");
	u8g2_DrawStr(&u8g2, 38, 40, buffer[3]);

	u8g2_DrawStr(&u8g2, 2, 50, "ch[5]:");
	u8g2_DrawStr(&u8g2, 38, 50, buffer[4]);

	u8g2_DrawVLine(&u8g2, 65, 2, 60);
	u8g2_DrawVLine(&u8g2, 80, 2, 60);
	u8g2_DrawVLine(&u8g2, 95, 2, 60);
	u8g2_DrawVLine(&u8g2, 110, 2, 60);
	u8g2_DrawVLine(&u8g2, 125, 2, 60);

	u8g2_DrawHLine(&u8g2, 66, 2, 60);
	u8g2_DrawHLine(&u8g2, 66, 17, 60);
	u8g2_DrawHLine(&u8g2, 66, 32, 60);
	u8g2_DrawHLine(&u8g2, 66, 47, 60);
	u8g2_DrawHLine(&u8g2, 66, 62, 60);
	u8g2_DrawStr(&u8g2, 83, 13, "DN");
	u8g2_DrawStr(&u8g2, 67, 13, "SE");
	if (!key1.key[2])
		u8g2_DrawBox(&u8g2, 95, 2, 15, 15);
	if (!key1.key[3])
		u8g2_DrawBox(&u8g2, 110, 2, 15, 15);
	if (!key1.key[4])
		u8g2_DrawBox(&u8g2, 65, 17, 15, 15);
	if (!key1.key[5])
		u8g2_DrawBox(&u8g2, 80, 17, 15, 15);
	if (!key1.key[6])
		u8g2_DrawBox(&u8g2, 95, 17, 15, 15);
	if (!key1.key[7])
		u8g2_DrawBox(&u8g2, 110, 17, 15, 15);
	if (!key1.key[8])
		u8g2_DrawBox(&u8g2, 65, 32, 15, 15);
	if (!key1.key[9])
		u8g2_DrawBox(&u8g2, 80, 32, 15, 15);
	if (!key1.key[10])
		u8g2_DrawBox(&u8g2, 95, 32, 15, 15);
	if (!key1.key[11])
		u8g2_DrawBox(&u8g2, 110, 32, 15, 15);
	if (!key1.key[12])
		u8g2_DrawBox(&u8g2, 65, 47, 15, 15);
	if (!key1.key[13])
		u8g2_DrawBox(&u8g2, 80, 47, 15, 15);
	if (!key1.key[14])
		u8g2_DrawBox(&u8g2, 95, 47, 15, 15);
	if (!key1.key[15])
		u8g2_DrawBox(&u8g2, 110, 47, 15, 15);
}
void draw_volume_subject(void)
{
	buzzer_mode = 2;
	u8g2_SetFont(&u8g2, u8g2_font_unifont_t_polish);
	u8g2_DrawStr(&u8g2, 30, 20, "|volume|");
}
void draw_calibration_subject(void)
{
	buzzer_mode = 2;
	u8g2_SetFont(&u8g2, u8g2_font_unifont_t_polish);
	u8g2_DrawStr(&u8g2, 10, 28, "|calibrating|");
}
