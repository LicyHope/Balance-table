#ifndef __MATRIX_KEY_H
#define __MATRIX_KEY_H
#include "stm32f10x.h"

#define 	KEY_RCC			RCC_APB2Periph_GPIOA		//时钟
#define 	KEY_PORT		GPIOA						//端口


#define 	KEY1_RCC		RCC_APB2Periph_GPIOA		//时钟
#define 	KEY1_PORT		GPIOA						//端口
#define 	KEY1_PIN		GPIO_Pin_0					//引脚

#define 	KEY2_RCC		RCC_APB2Periph_GPIOA		//时钟
#define 	KEY2_PORT		GPIOA						//端口
#define 	KEY2_PIN		GPIO_Pin_1					//引脚

#define 	KEY3_RCC		RCC_APB2Periph_GPIOA		//时钟
#define 	KEY3_PORT		GPIOA						//端口
#define 	KEY3_PIN		GPIO_Pin_2					//引脚

#define 	KEY4_RCC		RCC_APB2Periph_GPIOA		//时钟
#define 	KEY4_PORT		GPIOA						//端口
#define 	KEY4_PIN		GPIO_Pin_3					//引脚

#define 	KEY5_RCC		RCC_APB2Periph_GPIOA		//时钟
#define 	KEY5_PORT		GPIOA						//端口
#define 	KEY5_PIN		GPIO_Pin_4					//引脚

#define 	KEY6_RCC		RCC_APB2Periph_GPIOA		//时钟
#define 	KEY6_PORT		GPIOA						//端口
#define 	KEY6_PIN		GPIO_Pin_5					//引脚

#define 	KEY7_RCC		RCC_APB2Periph_GPIOA		//时钟
#define 	KEY7_PORT		GPIOA						//端口
#define 	KEY7_PIN		GPIO_Pin_6					//引脚

#define 	KEY8_RCC		RCC_APB2Periph_GPIOA		//时钟
#define 	KEY8_PORT		GPIOA						//端口
#define 	KEY8_PIN		GPIO_Pin_7					//引脚


#define		ROW_INT_MODE	key_set_row_input_mode()
#define		ROW_OUT_MODE	key_set_row_output_mode()

#define		LIST_INT_MODE	key_set_list_input_mode()
#define		LIST_OUT_MODE	key_set_list_output_mode()

#define 	LIST_SET_HIGH	{GPIO_SetBits(KEY_PORT,KEY5_PIN);GPIO_SetBits(KEY_PORT,KEY6_PIN);GPIO_SetBits(KEY_PORT,KEY7_PIN);GPIO_SetBits(KEY_PORT,KEY8_PIN);}
#define 	LIST_SET_LOW	{GPIO_ResetBits(KEY_PORT,KEY5_PIN);GPIO_ResetBits(KEY_PORT,KEY6_PIN);GPIO_ResetBits(KEY_PORT,KEY7_PIN);GPIO_ResetBits(KEY_PORT,KEY8_PIN);}

#define 	ROW_SET_HIGH	{GPIO_SetBits(KEY_PORT,KEY1_PIN);GPIO_SetBits(KEY_PORT,KEY2_PIN);GPIO_SetBits(KEY_PORT,KEY3_PIN);GPIO_SetBits(KEY_PORT,KEY4_PIN);}
#define 	ROW_SET_LOW		{GPIO_ResetBits(KEY_PORT,KEY1_PIN);GPIO_ResetBits(KEY_PORT,KEY2_PIN);GPIO_ResetBits(KEY_PORT,KEY3_PIN);GPIO_ResetBits(KEY_PORT,KEY4_PIN);}



extern const uint8_t key_tab[4][5];
extern uint8_t key_flag;



void key_set_list_input_mode(void);		//按键 列 设置输入模式
void key_set_list_output_mode(void);	//按键 列 设置输出模式
void key_set_row_input_mode(void);		//按键 行 设置输入模式
void key_set_row_output_mode(void);		//按键 行 设置输出模式

void matrix_key_init(void);		//按键初始化
uint8_t matrix_key_scanf(void);	//获取按键键值
void matrix_key_process(void);
char myGetKey(void);
#endif


