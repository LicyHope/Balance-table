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
    float pitch, roll, yaw;    //ŷ����
    short aacx, aacy, aacz;    //���ٶȴ�����ԭʼ����
    short gyrox, gyroy, gyroz; //������ԭʼ����

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(115200);                              //���ڳ�ʼ��Ϊ115200
    delay_init();                                   //��ʱ��ʼ��
    LED_Init();                                     //��ʼ����LED���ӵ�Ӳ���ӿ�
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
        // temp = MPU_Get_Temperature();                             //�õ��¶�ֵ
        MPU_Get_Accelerometer(&aacx, &aacy, &aacz); //�õ����ٶȴ���������
        MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);  //�õ�����������

        // LCD��ʾ�����Ƕ�
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
            MPU_Get_Accelerometer(&aacx, &aacy, &aacz); //�õ����ٶȴ���������
            MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);  //�õ�����������
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

        printf("keyval��%c", keyval);

        delay_ms(100);
    }
}
