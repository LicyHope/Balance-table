#include "led.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "lcd_init.h"
#include "matrix_key.h"

int main(void)
{
    char keyval = '\0';
    float pitch, roll, yaw;    //欧拉角
    short aacx, aacy, aacz;    //加速度传感器原始数据
    short gyrox, gyroy, gyroz; //陀螺仪原始数据

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    uart_init(115200);                              //串口初始化为115200
    delay_init();                                   //延时初始化
    LED_Init();                                     //初始化与LED连接的硬件接口
    MPU_Init();
    LCD_Init();
    matrix_key_init();
    LCD_Fill(0, 0, 140, 140, WHITE);

    LCD_ShowString(0, 0, "JLU", RED, WHITE, 16, 0);
    LCD_ShowString(0, 20, "roll:", DARKBLUE, WHITE, 16, 0);
    LCD_ShowString(0, 40, "pitch:", DARKBLUE, WHITE, 16, 0);
    LCD_ShowString(0, 60, "yaw:", DARKBLUE, WHITE, 16, 0);
    LCD_ShowString(0, 80, "Hello!,World!", BLUE, WHITE, 16, 0);

    // keyval = matrix_key_scanf();

    while (mpu_dmp_init() != 0)
        ;
    while (1)
    { // LED =~LED;
        // keyval = myGetKey();
        // keyval = matrix_key_scanf();

        while (mpu_dmp_get_data(&pitch, &roll, &yaw) != 0)
            ;
        // temp = MPU_Get_Temperature();                             //得到温度值
        MPU_Get_Accelerometer(&aacx, &aacy, &aacz); //得到加速度传感器数据
        MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);  //得到陀螺仪数据

        // LCD显示三个角度
        if (roll < 0)
        {
            LED = 0;
            roll = -roll;
            LCD_ShowChar(50, 20, '-', BLUE, WHITE, 16, 0);
        }
        else
        {
            LED = 1;
            LCD_ShowChar(50, 20, ' ', BLUE, WHITE, 16, 0);
        }

        LCD_ShowFloatNum1(60, 20, roll, 5, BLUE, WHITE, 16);
        if (pitch < 0)
        {
            pitch = -pitch;
            LCD_ShowChar(50, 40, '-', BLUE, WHITE, 16, 0);
        }
        else
        {
            LCD_ShowChar(50, 40, ' ', BLUE, WHITE, 16, 0);
        }

        LCD_ShowFloatNum1(60, 40, pitch, 4, BLUE, WHITE, 16);
        if (yaw < 0)
        {
            yaw = -yaw;
            LCD_ShowChar(50, 60, '-', BLUE, WHITE, 16, 0);
        }
        else
        {
            LCD_ShowChar(50, 60, ' ', BLUE, WHITE, 16, 0);
        }

        LCD_ShowFloatNum1(60, 60, yaw, 5, BLUE, WHITE, 16);

        // keyval = matrix_key_scanf();
        // matrix_key_process();
        // printf("roll:%.2f pitch:%.2f yaw:%.2f \r\n", roll, pitch, yaw);
        // keyval = myGetKey();
        while (keyval = myGetKey())
        {
            MPU_Get_Accelerometer(&aacx, &aacy, &aacz); //得到加速度传感器数据
            MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);  //得到陀螺仪数据
            if (roll < 0)
            {
                LED = 0;
                roll = -roll;
                LCD_ShowChar(50, 20, '-', BLUE, WHITE, 16, 0);
            }
            else
            {
                LED = 1;
                LCD_ShowChar(50, 20, ' ', BLUE, WHITE, 16, 0);
            }

            LCD_ShowFloatNum1(60, 20, roll, 5, BLUE, WHITE, 16);
            if (keyval == 'A')
            {
                LED2 = 0;
            }
            if (keyval == '*')
            {
                break;
            }
        }

        printf("keyval：%c", keyval);

        delay_ms(100);
    }
}
