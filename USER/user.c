
/**
  ******************************************************************************
  * @file    user.c
  * @author  ����
  * @date    2016��5��5��
  * @brief   ϵͳ����ʵ���ڴ��ļ���
  ******************************************************************************
  * @attention
  *    ע������:
  *
  *
  *
  *                COPYRIGHT 2016 ���������������豸�з�����
  ******************************************************************************
  */

#include "user.h"

#include "delay.h"
#include "tools.h"
#include "peripheral.h"
#include "lcd.h"
#include "qr_encode.h"
#include "HX711.h"
#include "sim900a.h"

#define QRCODE_Y    240      //TFT��ά����ʾ����y


float  verison = 0;

uint16_t DS0_TimeCnt = 0;

uchar keyPadRowScan = 0;
uint16_t keyPadCnt = 0;
uchar keyTouch = 0;
uchar getWeightService = 0;
uchar getWeightCnt = 0;
char weightStr[10] = {0};
char unitPrice[8] = {0};
char totalMoney[8] = {0};
char gprsSendBuff[50] = {0};
uchar tradeLock = 0;
uchar  ledFlickFlag = 0;
uchar gprsService = 0;
uint16_t heartbeat = 0;
uchar cunnectFlag = 0;
uchar heartbeatService = 0;

const uint8_t codetest[] = //΢����Ƭ������ȥ�ٶ���������ά����Ƭ �鿴
{
    "URL:http:www.baidu.com"
//    "��˯���ʴ�����ҹ����˼��\r\nƾ������Զ�����������ޡ�\r\n "
//    "�ε�ӵ����ɽ���ƹ����ڣ�ȴ�������з���������ڣ�\r\n"
//    "                    ��������"
//  "��Ҫɨ��"
};

void RCC_Config(void);
void DISPLAY_RENCODE_TO_TFT(uint8_t *qrcode_data);
/************************************************
*������ :       RCC_Config

*�������� :      ��

*��������ֵ :     ��

*������������ :   ��Ҫ�ĸ���ʱ�� ͳһ�����￪������

*ע�� :
*************************************************/
void RCC_Config(void)
{
    /*      ��APB2ʱ�� ���72M�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,
                           ENABLE); /* �κ�һ���˿ڣ����з�������ӳ�� Ҫ������ʱ��
                           GPIO�����ⲿ�ж�EXTI��ʱ�򣬱��뿪��AFIOʱ�ӣ�*/


    /*                                                         */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); /*  */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); /* ����3 PB10 PB11*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); /*  */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); /*  */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    //  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    /*  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);  */
    /*                                                         */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    /*  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);   */
    /*  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);   */
    /*                                                         */
    /*  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);   */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); /* ����1 485ͨ��*/
    /*                                                         */
    /*  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   */
    /*  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);   */
    /*  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);   */
    /*  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);  */
    /*  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);  */
    /*  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);  */
    /*  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);  */
    /*  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);  */


    /*      ��APB1ʱ�� ���36M�� */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); /* ͨ�ö�ʱ��4 ʱ���׼*/
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);   */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);   */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);   */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);  */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);  */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);  */
    /*                                                         */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);   */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);   */
    /*                                                         */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);   */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);   */
    /*                                                         */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
// RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,
    //                       ENABLE); /* ��Ƭ�����ֻ�ģ���ͨ���ô���3*/

    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART4, ENABLE); */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART5, ENABLE); */
    /*                                                         */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);   */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);    */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);   */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);    */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);    */
    /*  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CEC, ENABLE);    */



    /*  ��AHB����ʱ�ӡ�   ����ϸ��� д��ʱ���Լ���ѯע��*/
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);


}

/********************************************************************
*������ ��        HeadFirst

*�������� ��      ��

*��������ֵ :     ��

*������������ ��  HeadFirst �˺������ǵ�Ƭ���ϵ�ʱִ�е�һЩ�����ĳ�ʼ��������
*********************************************************************/
void  HeadFirst(void)
{
    Delay_init();
    Delay_ms(100);

    verison = 1.00;

    RCC_Config(); //�����������ص�һЩ�����ʱ��


    LED_Config();



    USART1_Config();
    USART2_Config();

//    printf("==����ʦ-����==\r\n��������:2017��5��11��==\r\n");
//    printf("�������С�����:%.2f\r\n", verison);

//    SendStringBy_USART1("OK\r\n");
//    printf("����2�������");






    HX711_Config();


    GetMaopi();
    Delay_ms(1000);
    Delay_ms(1000);
    GetMaopi();


    LCD_Config();


    LCD_Clear(BLACK);//GBLUE
    POINT_COLOR = BLACK;

    /*24���ַ��Ĵ�С��һ���ַ��Ŀ���Ϊ320/26*/

    LCD_ShowString(60, 10, 264, 24, 24, "Electronic Scale"); //��ʾLCD ID  11*24=

    LCD_ShowString(0, 40, 123, 24, 24, "Weight(g):");//10*12=120
    LCD_ShowString(0, 80, 209, 24, 24, "Unit Price(Y/Kg):");//17*12=204

    POINT_COLOR = BLUE;

    LCD_ShowString(120, 40, 123, 24, 24, "0");//��������Ĭ����ʾ0
    LCD_ShowString(204, 80, 123, 24, 24, "0");//����Ĭ����ʾ0





    DISPLAY_RENCODE_TO_TFT((uint8_t *)codetest);

    KeyPadConfig();
    TIM4_Config(); //���ͨ�ö�ʱ��4�����������ҳ����ܵ�ʱ���׼��

    TCP_ConnectServer();//TCP���ӷ�����
    // printf("����ϵͳ");

    // IWDG_Configuration();
}

void KeyTest()
{
    if(KEY_Row1)
    {
        printf("1�ߵ�ƽ");
    }
    else
    {
        printf("1�͵�ƽ");
    }
    if(KEY_Row2)
    {
        printf("2�ߵ�ƽ");
    }
    else
    {
        printf("2�͵�ƽ");
    }

    if(KEY_Row3)
    {
        printf("3�ߵ�ƽ");
    }
    else
    {
        printf("3�͵�ƽ");
    }

    if(KEY_Row4)
    {
        printf("4�ߵ�ƽ");
    }
    else
    {
        printf("4�͵�ƽ");
    }



    if(KEY_Col1_IN)
    {
        printf("=========\r1�ߵ�ƽ");
    }
    else
    {
        printf("1�͵�ƽ");
    }
    if(KEY_Col2_IN)
    {
        printf("2�ߵ�ƽ");
    }
    else
    {
        printf("2�͵�ƽ");
    }
    if(KEY_Col3_IN)
    {
        printf("3�ߵ�ƽ");
    }
    else
    {
        printf("3�͵�ƽ");
    }
    if(KEY_Col4_IN)
    {
        printf("4�ߵ�ƽ");
    }
    else
    {
        printf("4�͵�ƽ");
    }


}
void LedFlick()
{
    static uint8_t Su8_ledStep = 0;
    static uint8_t Su8_ledFlickNum = 0;


    if(!ledFlickFlag ) return;

    switch (Su8_ledStep)
    {
        case 0:
            if (DS0_TimeCnt >= 100)
            {
                DS0_TimeCnt = 0;
                if (DS0_IN == 1)
                {
                    DS0 = 0;
                }
                else
                {
                    DS0 = 1;
                }

                Su8_ledStep = 1;
            }
            break;
        case 1:
            if (DS0_TimeCnt >= 500)
            {
                DS0_TimeCnt = 0;
                if (DS0_IN == 1)
                {
                    DS0 = 0;
                }
                else
                {
                    DS0 = 1;
                }
                Su8_ledStep = 0;

                if (++Su8_ledFlickNum >= 2)
                {
                    Su8_ledFlickNum = 0;
                    ledFlickFlag = 0;
                }
            }
            break;
        default:
            break;
    }

}


void DISPLAY_RENCODE_TO_TFT(uint8_t *qrcode_data)
{
    u8 i, j;
    u16 x, y, p;
//    u8 qrencode_buff[12];           //���LCD ID�ַ���
    EncodeData((char *)qrcode_data);
    //LCD_Fill(10,110,15,115,BLACK);
    //  LCD_Fill(0, 40, 240, 320, WHITE); //3.5��ֱ����� 480X320   2.8��ֱ����� 320X240

    LCD_Fill(10, 200, 310, 470, WHITE);
    //   sprintf((char*)qrencode_buff, "size:%d",
    //         m_nSymbleSize); //��LCD ID��ӡ��lcd_id���顣
//    LCD_ShowString(10, 40, 200, 16, 16, qrencode_buff); //��ʾLCD ID
    if(m_nSymbleSize * 2 > 240)
    {
        LCD_ShowString(10, 60, 200, 16, 16,
                       (u8 *)"The QR Code is too large!"); //̫����ʾ����
        return;
    }
    for(i = 0; i < 10; i++)
    {
        if((m_nSymbleSize * i * 2) > 240) break;
    }
    p = (i - 1) * 2; //���С
    x = (320 - m_nSymbleSize * p) / 2;
    y = QRCODE_Y;
    //  sprintf((char*)qrencode_buff, "piont:%d", p); //��LCD ID��ӡ��lcd_id���顣
//  LCD_ShowString(10, 60, 200, 16, 16, qrencode_buff);
    //  LCD_ShowString(20, 240, 200, 16, 16, qrencode_buff);

    for(i = 0; i < m_nSymbleSize; i++)
    {
        for(j = 0; j < m_nSymbleSize; j++)
        {
            //USART1_SendData(m_byModuleData[j][i]);
            if(m_byModuleData[i][j] == 1)
                LCD_Fill(x + p * i, y + p * j, x + p * (i + 1) - 1, y + p * (j + 1) - 1, BLACK);

        }

    }
}





/************************************************
*������ :       KeyPadScan

*�������� :      ��

*��������ֵ :     ��

*������������ :

* 4��4��   ��ƽʱ�Ǹߵ�ƽ ��ƽʱҲ�Ǹߵ�ƽ

  �����θ�������͵�ƽʱ�����ĳ���еĵ�ƽ��Ϊ�͵�ƽ����˵����������

  ����ȥ�� 20ms ����     20/2.5=8
*************************************************/

void KeyPadScan()
{
    static uchar step = 0, keyPadLock = 0;

    switch(step)
    {
        case 0:
            switch(keyPadRowScan)
            {
                case 0: //��ֵ��һ�� ����ɨ��
                    KEY_Col1 = 0;
                    KEY_Col2 = 1;
                    KEY_Col3 = 1;
                    KEY_Col4 = 1;
                    break;
                case 1://��ֵ�ڶ��� ����ɨ��
                    KEY_Col1 = 1;
                    KEY_Col2 = 0;
                    KEY_Col3 = 1;
                    KEY_Col4 = 1;
                    break;
                case 2://��ֵ������ ����ɨ��
                    KEY_Col1 = 1;
                    KEY_Col2 = 1;
                    KEY_Col3 = 0;
                    KEY_Col4 = 1;
                    break;
                case 3://��ֵ������ ����ɨ��
                    KEY_Col1 = 1;
                    KEY_Col2 = 1;
                    KEY_Col3 = 1;
                    KEY_Col4 = 0;
                    break;
                default:
                    break;
            }
            step = 1;
            break;
        case 1:
            if(KEY_Row1 == 1 && KEY_Row2 == 1 && KEY_Row3 == 1 &&
               KEY_Row4 == 1)//û�а���������
            {
                keyPadRowScan++;
                if(keyPadRowScan >= 4)
                {
                    keyPadRowScan = 0;
                }
                step = 0;
                keyPadCnt = 0;
                keyPadLock = 0;
            }
            else if(keyPadLock == 0)//�а���������
            {
                keyPadCnt++;
                if(keyPadCnt >= 5) //��������  2.5X8=20ms
                {
                    keyPadLock = 1;

                    if(KEY_Row1 == 0) //��һ�б���⵽�͵�ƽ
                    {
                        switch(keyPadRowScan)//��ǰɨ��ڼ���
                        {
                            case 0:
                                keyTouch = 1;
                                break;
                            case 1:
                                keyTouch = 2;
                                break;
                            case 2:
                                keyTouch = 3;
                                break;
                            case 3:
                                keyTouch = 10;
                                break;
                        }
                    }
                    else if(KEY_Row2 == 0) //�ڶ��б���⵽�͵�ƽ
                    {
                        switch(keyPadRowScan)//��ǰɨ��ڼ���
                        {
                            case 0:
                                keyTouch = 4;
                                break;
                            case 1:
                                keyTouch = 5;
                                break;
                            case 2:
                                keyTouch = 6;
                                break;
                            case 3:
                                keyTouch = 11;
                                break;
                        }
                    }
                    else if(KEY_Row3 == 0) //�����б���⵽�͵�ƽ
                    {
                        switch(keyPadRowScan)//��ǰɨ��ڼ���
                        {
                            case 0:
                                keyTouch = 7;
                                break;
                            case 1:
                                keyTouch = 8;
                                break;
                            case 2:
                                keyTouch = 9;
                                break;
                            case 3:
                                keyTouch = 12;
                                break;
                        }
                    }
                    else if(KEY_Row4 == 0) //�����б���⵽�͵�ƽ
                    {
                        switch(keyPadRowScan)//��ǰɨ��ڼ���
                        {
                            case 0:
                                keyTouch = 14;
                                break;
                            case 1:
                                keyTouch = 16;
                                break;
                            case 2:
                                keyTouch = 15;
                                break;
                            case 3:
                                keyTouch = 13;
                                break;
                        }
                    }
                }
            }
            break;
        default:

            break;
    }
}

void KeyPadService(void)
{
    static uchar cursorIndex = 0;
    uchar num = 0;

    if(!keyTouch )// ||
    {
        return;
    }

    if((keyTouch >= 1 && keyTouch <= 9) || keyTouch == 14 || keyTouch == 16)
    {
        if(cursorIndex < 7 &&
           tradeLock == 0) //����û�йر�  ���㰴�������׹رպ󣬲��������뵥������
        {
            cursorIndex++;
            //printf("����%d\r\n",keyTouch);
            if(keyTouch >= 1 && keyTouch <= 9)
            {
                num = keyTouch;
                LCD_ShowNum(204 + 12 * (cursorIndex - 1), 80, num, 1 , 24);
                unitPrice[cursorIndex - 1] = num + 48;
            }
            else if(keyTouch == 16)
            {
                num = 0;
                LCD_ShowNum(204 + 12 * (cursorIndex - 1), 80, 0, 1 , 24);
                unitPrice[cursorIndex - 1] = num + 48;
            }
            else
            {
                if(cursorIndex > 1)
                {
                    //��ֹ2��С����ĳ���û�����ӣ������п��Ż�ʵ��
                    LCD_ShowString(204 + 12 * (cursorIndex - 1), 80, 24, 24, 24, ".");
                    unitPrice[cursorIndex - 1] = 46;
                }
                else
                {
                    cursorIndex = 0;
                }
            }
        }
        keyTouch = 0;
    }

    switch(keyTouch)
    {
        case 10:
            //  printf("A:ȥƤ\r\n");
            GetMaopi();
            keyTouch = 0;
            break;
        case 11:
            //    printf("B:����\r\n");
            memset(unitPrice, 0, 8);//���۸�����Ϊ��
            LCD_ShowString(120, 40, 123, 24, 24, "0");//��������Ĭ����ʾ0
            LCD_Fill(132, 40, 350, 64, BLACK);

            LCD_ShowString(204, 80, 123, 24, 24, "0");//����Ĭ����ʾ0
            LCD_Fill(216, 80, 350, 104, BLACK);

            LCD_Fill(0, 120, 400, 144, BLACK); //�ܶ���ʾ�����
            cursorIndex = 0;//��긴ԭ

            keyTouch = 0;
            tradeLock = 0;//��������
            break;
        case 12:
            //    printf("C:ɾ��\r\n");
            if(cursorIndex > 0 && tradeLock == 0)//����û�йر�
            {
                LCD_Fill(204 + 12 * (cursorIndex - 1), 80, 216 + 12 * (cursorIndex - 1), 104,
                         BLACK);
                cursorIndex--;
            }
            keyTouch = 0;
            break;
        case 13:
            //    printf("D:����\r\n");

            sprintf(totalMoney, "%.2f", atof(unitPrice) * (Weight_Shiwu / 1000.0) - 0.005);

            tradeLock =
                1; //���ν��׽�������������ʾҳ�棬�����ٸĶ��޸����ݣ����¿�ʼ�����밴B��

            keyTouch = 0;

            POINT_COLOR = BLACK;
            LCD_ShowString(0, 120, 209, 24, 24, "Total(yuan):");//12*12=144

            POINT_COLOR = RED;
            LCD_ShowString(144, 120, 209, 24, 24, (u8*)totalMoney);//17*12=204
            POINT_COLOR = BLUE;


            gprsService = 1;
            sprintf(gprsSendBuff, "get?jiage=%s&name=HouXiao\r\n", totalMoney);
            ledFlickFlag = 1;


            break;

        case 15:
            //  printf("#\r\n");





            keyTouch = 0;
            break;

    }
}




void  GetWeightService(void)
{
    static uchar lastLength = 0, newLength = 0;

    if(getWeightService)
    {
        if(tradeLock == 0)
        {
            GetWeight();

            newLength = NumLength(Weight_Shiwu);


            if(lastLength !=
               newLength)//�����ǽ�����ݴ�3λ ��2λ �ȱ�Ϊ1λ����ʱ�����ʾ�����
            {
                LCD_Fill(120, 40, 180, 64, BLACK);
                lastLength = newLength;
            }

            LCD_ShowNum(120, 40, Weight_Shiwu, newLength ,
                        24); //NumLength(Weight_Shiwu)��������ݵ�����λ��

            //    printf("%d ",Weight_Shiwu);
        }
        getWeightService = 0;
    }

}


void  GPRS_Service()
{
    static uchar step = 0;

    uint8_t   temp = 0;
    if(gprsService == 0 && heartbeatService == 0) return;

    switch(step)
    {
        case 0:
            temp = Send_AT_Cmd("AT+CIPSEND\r\n", ">", 150);
            if (temp == 2) //�������ָ���?���ص�������OK��ʾ�ɹ�?��ʱtemp=2
            {
                if(gprsService)//��Чͨ��
                {
                    printf(gprsSendBuff);
                }
                else if(heartbeatService)  //��Чͨ�ŵ�ʱ�� �Ͳ�Ҫ��������  ����6sһ��
                {
                    heartbeatService = 0;

                    USART_ClearFlag(USART2, USART_FLAG_TC);
                    USART_SendData(USART2, 0x00);
                    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
									  SendStringBy_USART1("Heart\r\n");
                }

                USART_ClearFlag(USART2, USART_FLAG_TC);
                USART_SendData(USART2, 0x1A);
                while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);

                gprsService = 0;
            }
            if (temp == 3) //�������ζ�����
            {

                USART_ClearFlag(USART2, USART_FLAG_TC);
                USART_SendData(USART2, 0x1B);
                while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);

                SendStringBy_USART1("GPRS Send Err\r\n");
                gprsService = 0;
            }
            break;

        case 1:


            break;

    }



}
