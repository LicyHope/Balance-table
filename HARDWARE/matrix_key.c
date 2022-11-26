#include "matrix_key.h"
#include "usart.h"

uint8_t key_flag;

/*4X4矩阵按键的表盘设置*/
const uint8_t matrix_key_tab[4][4] =
    {
        '1',
        '2',
        '3',
        'A',
        '4',
        '5',
        '6',
        'B',
        '7',
        '8',
        '9',
        'C',
        '*',
        '0',
        '#',
        'D',
};

/***********************************************************************
描述: 按键 列 设置输入模式（前4个）
************************************************************************/
void key_set_list_input_mode(void)
{
    GPIO_InitTypeDef KEY_InitStruction;
    RCC_APB2PeriphClockCmd(KEY_RCC, ENABLE);

    //列引脚
    KEY_InitStruction.GPIO_Pin = KEY5_PIN | KEY6_PIN | KEY7_PIN | KEY8_PIN; //引脚
    KEY_InitStruction.GPIO_Mode = GPIO_Mode_IPU;                            //上拉输入
    GPIO_Init(KEY_PORT, &KEY_InitStruction);
}

/***********************************************************************
描述: 按键 列 设置输出模式
************************************************************************/
void key_set_list_output_mode(void)
{
    GPIO_InitTypeDef KEY_InitStruction;
    RCC_APB2PeriphClockCmd(KEY_RCC, ENABLE);

    //列引脚
    KEY_InitStruction.GPIO_Pin = KEY5_PIN | KEY6_PIN | KEY7_PIN | KEY8_PIN; //引脚
    KEY_InitStruction.GPIO_Mode = GPIO_Mode_Out_PP;                         //推挽输出
    KEY_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;                        //速率

    GPIO_Init(KEY_PORT, &KEY_InitStruction);
}

/***********************************************************************
描述: 按键 行 设置输入模式
************************************************************************/
void key_set_row_input_mode(void)
{
    GPIO_InitTypeDef KEY_InitStruction;
    RCC_APB2PeriphClockCmd(KEY_RCC, ENABLE);

    //列引脚
    KEY_InitStruction.GPIO_Pin = KEY1_PIN | KEY2_PIN | KEY3_PIN | KEY4_PIN; //引脚
    KEY_InitStruction.GPIO_Mode = GPIO_Mode_IPU;                            //上拉输入
    GPIO_Init(KEY_PORT, &KEY_InitStruction);
}

/***********************************************************************
描述: 按键 行 设置输出模式
************************************************************************/
void key_set_row_output_mode(void)
{
    GPIO_InitTypeDef KEY_InitStruction;
    RCC_APB2PeriphClockCmd(KEY_RCC, ENABLE);

    //列引脚
    KEY_InitStruction.GPIO_Pin = KEY1_PIN | KEY2_PIN | KEY3_PIN | KEY4_PIN; //引脚
    KEY_InitStruction.GPIO_Mode = GPIO_Mode_Out_PP;                         //推挽输出
    KEY_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;                        //速率

    GPIO_Init(KEY_PORT, &KEY_InitStruction);
}

/***********************************************************************
描述: 按键初始化函数
************************************************************************/
void matrix_key_init(void)
{
    ROW_OUT_MODE;  //行设置输出模式
    LIST_INT_MODE; //列设置输入模式
}

/***********************************************************************
描述: 获取键值 函数
返回: 返回表盘对应键值
************************************************************************/
uint8_t matrix_key_scanf(void)
{
    static uint8_t key_status;
    uint8_t R, L;
    uint8_t key_temp;

    //检测列 所以我们让行拉低 列拉高
    LIST_INT_MODE;
    LIST_SET_HIGH;
    ROW_OUT_MODE;
    ROW_SET_LOW;

    key_temp = ~GPIO_ReadInputData(KEY_PORT) & 0XF0;
    if (key_temp == 0)
    {
        key_status = 0;
        return 0;
    }

    //第一次检测到
    if (key_status == 0)
    {
        key_status = 1;
        return 0;
    }
    //第二次检测到
    else if (key_status == 1)
    {
        key_status = 2;

        //读取列
        switch (key_temp)
        {
        case 0x10:
            L = 0;
            break;
        case 0x20:
            L = 1;
            break;
        case 0x40:
            L = 2;
            break;
        case 0x80:
            L = 3;
            break;
        default:
            return 0;
        }
        //快速转换模式
        //再检测行是否有按键按下 所以先让列拉低 行拉高
        LIST_OUT_MODE;
        LIST_SET_LOW; // PA4 ~ PA7
        ROW_INT_MODE;
        ROW_SET_HIGH; // PA0 ~ PA3

        key_temp = ~GPIO_ReadInputData(KEY_PORT) & 0X0F;
        //读取行
        switch (key_temp)
        {

        case 0x01:
            R = 0;
            break;
        case 0x02:
            R = 1;
            break;
        case 0x04:
            R = 2;
            break;
        case 0x08:
            R = 3;
            break;
        default:
            return 0;
        }

        return matrix_key_tab[R][L];
        ;
    }
    //证明没松开按键
    else if (key_status == 2)
    {
        return 0;
    }
    key_status = 0;
    return 0;
}

/***********************************************************************
描述: 矩阵键盘处理 函数
************************************************************************/
void matrix_key_process(void)
{
    uint8_t key_val;

    if (key_flag)
    {
        key_flag = 0;
        key_val = matrix_key_scanf(); //获取键值
        if (key_val == 0)
            return;
        printf("KEY:%c\r\n", key_val);
    }
}

char myGetKey()
{
    char key = '\0';
    do
    {
        key = matrix_key_scanf();
    } while (!key);
    return key;
}
