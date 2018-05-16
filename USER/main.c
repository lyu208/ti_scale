/******************** (C) COPYRIGHT 2018 梦之创物联网设备研发中心 **************************
 * 实验平台：STM32开发板
 * 库版本  ：ST3.5.0
 * UCOS版本：无
 * MDK版本 ：4.72a
 *
 * 描述   ：
 *
 * 硬件连接： 3.5寸液晶屏  320 X 480
 *
 *
 * 日期 :   2018年5月16日
 * 作者 :   梦之创
 * 版本号 : v0.1
 *
 ********************************************************************************************
 * 1、单价的输入最多7个字符 比如单价  9999.99  足够使用了，请问有什么单价是9999.99元这么高  除了老婆！
 *
 *
 *
 *
 *
 ********************************************************************************************/

#include "includes.h"
#include "string.h"

extern void KeyTest(void);
 
int main()
{
    HeadFirst();
 
    while (1)
    {
        GetWeightService();

        LedFlick();
        KeyPadService();
			
			  GPRS_Service();
			  
    }
}
 
/************************************************
*函数名 ：        assert_failed

*函数参数 ：      出错的文件，出错的行

*函数返回值 :     无

*函数功能描述 ：  断言检查机制，通过串口打印出错误，不会在Build Output输出！！
                  调试使用的时候，取消注释 并开启 断言机制就可以了！
*************************************************/
//void assert_failed(uint8_t *file, uint32_t line)
//{
// printf("Wrong parameters value: file %s on line %d\r\n", file, line);
// while(1);
//}






/******************** (C) COPYRIGHT 2018 梦之创物联网设备研发中心 **************************
 * 实验平台：STM32开发板
 * 库版本  ：ST3.5.0
 * UCOS版本：无
 * MDK版本 ：4.72a
 *
 * 描述   ：
 *
 * 硬件连接：
 *
 *
 * 日期 :   2018年5月16日
 * 作者 :   梦之创
 * 版本号 : v0.1
 ********************************************************************************************/


/**
  ******************************************************************************
  * @file    base.c
  * @author  梦之创
  * @date    2016年5月4日
  * @brief   提供点简单的 工具代码 和 基本的外设实现
  ******************************************************************************
  * @attention
  *    此文件函数功能:
  *
  *
  *
  *                COPYRIGHT 2016 梦之创物联网设备研发中心
  ******************************************************************************
  */


/************************************************
*              私有函数声明                       *
*************************************************/


/************************************************
*             对外开放-变量                     *
*************************************************/

/************************************************
*             对外开放-函数                     *
*************************************************/


/************************************************
*函数名 :       ReadKeyValue

*函数参数 :      无

*函数返回值 :     无

*函数功能描述 :   FUCK YOU??

*注意 :
*************************************************/



