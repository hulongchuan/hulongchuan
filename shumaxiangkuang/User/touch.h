//#include "lcd.h"
//void drow_touch_point(unsigned int x,unsigned int y);
#define __TOUCH_H  
//触摸屏初始化
//使用外部8M晶振,PLL到72M频率		    

//2008/12/14 
//V1.0  

/*-------------------------------
管脚对应
PC.1 PEN
PC.2 DIN
PC.3 CLK
PB.8 CS
PB.9 DOUT
//ADS7846有温度测量和压力测量功能
//可以参考PDF资料自己写	 
--------------------------------*/
#define GPIO_Pin_6                 ((u16)0x0040)  /* Pin 6 selected */

#define DOUT GPIOA->IDR&1<<6 //PA6数据输入

#define TDIN  (1<<7)  // PA7
#define TCLK  (1<<5)  // PA5
#define TCS   (1<<7)  // PB7   			    
#define TDIN_SET(x) GPIOA->ODR=(GPIOA->ODR&~TDIN)|(x ? TDIN:0)
#define TCLK_SET(x) GPIOA->ODR=(GPIOA->ODR&~TCLK)|(x ? TCLK:0)													    
#define TCS_SET(x)  GPIOB->ODR=(GPIOB->ODR&~TCS)|(x ? TCS:0)  

//笔杆结构体
typedef struct 
{
	unsigned int X0;//原始坐标
	unsigned int Y0;
	unsigned int X; //最终/暂存坐标
	unsigned int Y;						   	    
	unsigned char  Key_Sta;//笔的状态
	unsigned char  Key_LSta;//上一次笔的状态
//触摸屏校准参数
	float xfac;
	float yfac;
	short xoff;
	short yoff;
}Pen_Holder;


//按键状态	 
#define Key_Down 0x01
#define Key_Up   0x00 
//触摸屏按键处理
#define CLICK_POINT 0X01   
#define MOVE_LEFT   0X10
#define MOVE_RIGHT  0X20
#define MOVE_UP     0X40
#define MOVE_DOWN   0X80

//TFTLCD里面颜色的定义
		
#define RED	  0XF800
#define GREEN 0X07E0
#define BLUE  0X001F  
#define BRED  0XF81F
#define GRED  0XFFE0
#define GBLUE 0X07FF
#define WHITE 0XFFFF //白色
#define BLACK 0X0000 //黑色
#define BROWN 0XBC40 //棕色
#define BRRED 0XFC07 //棕红色
#define GRAY  0X8430 //灰色
#define LGRAY 0XC618 //浅灰色


static unsigned char  fac_us=0;//us延时倍乘数
static unsigned int fac_ms=0;//ms延时倍乘数



