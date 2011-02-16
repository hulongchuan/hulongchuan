/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : lcd.h
* Author             : MCD Application Team
* Version            : V1.1
* Date               : 11/26/2007
* Description        : This file contains all the functions prototypes for the
*                      lcd firmware driver.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define Line0          0
#define Line1          24
#define Line2          48
#define Line3          72
#define Line4          96
#define Line5          120
#define Line6          144
#define Line7          168
#define Line8          192
#define Line9          216

#define Horizontal     0x00
#define Vertical       0x01

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/*----- High layer function -----*/
void LCD_Setup(void);               /*初始化LCD*/
void LCD_SetTextColor(vu16 Color);  /*设置前景色*/
void LCD_SetBackColor(vu16 Color);  /*设置背景色*/
void LCD_ClearLine(u8 Line);        /*清行*/
void LCD_Clear(u16 Color);          /*清屏*/
void LCD_SetCursor(u8 Xpos, u16 Ypos);   /*设置光标位置*/
void LCD_DrawChar(u8 Xpos, u16 Ypos, uc16 *c);   /*写字符*/
void LCD_DisplayChar(u8 Line, u16 Column, u8 Ascii);  /*写ascii字符*/
void LCD_DisplayStringLine(u8 Line, u8 *ptr);   /*显示字符串*/
void LCD_SetDisplayWindow(u8 Xpos, u16 Ypos, u8 Width, u16 Height);/*设置窗口模式*/
void LCD_WindowModeDisable(void);/*关闭窗口模式*/
/*-------Draw function-------------*/
void LCD_DrawLine(u8 Xpos, u16 Ypos, u16 Length, u8 Direction);/*画线*/
void LCD_DrawRect(u8 Xpos, u16 Ypos, u8 Height, u16 Width);/*画圆*/
void LCD_DrawRectFill(u8 Xpos, u16 Ypos, u8 Width, u16 Height,u16 fill);/*画矩形*/
void LCD_DrawCircle(u8 Xpos, u16 Ypos, u16 Radius);/*填充矩形*/
void LCD_DrawMonoPict(uc8 *Pict);/*显示单色图片*/
void LCD_DrawBMP(u32 BmpAddress);/*显示BMP图片*/
void dis_juanxing(void); /*巻形特效*/
void dis_zhongkai(void); /*中开特效*/
void dis_circle(void);  /*圆形特效*/
void dis_baiye(void);/* 百叶窗特效*/
/*----- Medium layer function -----*/
void LCD_WriteReg(unsigned int LCD_Reg, unsigned int LCD_RegValue);/*写控制寄存器*/
void LCD_WriteRAMWord(u16 RGB_Code);/*写GRAM*/
void LCD_PowerOn(void);/*上电周期*/
void LCD_DisplayOn(void);/*启动显示*/
void LCD_DisplayOff(void);/*关闭显示*/

/*----- Low layer function -----*/
void LCD_CtrlLinesConfig(void);/*硬件初始化*/
void LCD_DisplayString(u8 Line, u8 *ptr);/*显示字符串*/
void test(void);

void  Delay (u32 nCount);
#endif /* __LCD_H */

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
