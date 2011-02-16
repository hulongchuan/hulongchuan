/******************************touch.c ducument was made by Li Kuan	***************************/
#include "touch.h"   	
#include "stdlib.h"
#include "stm32f10x_lib.h"
#include "stm32f10x_gpio.h"
#include "math.h"
#include "lcd.h"

////////////////////////////////////////////////////// 	

#define PEN  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define NPEN !(0x01&PEN)     //!PEN
Pen_Holder Pen_Point;//定义笔实体

void Touch_Start(void);
void start_spi(void);
void delay_ms(u16 nms);
void delay_us(u32 Nus);
//void WriteByteADS(u8 num);
void Select_Menu(u8 M_Type,u8 Cnt,u8 En);
u8 Read_Ads7846(void);

extern u16 SPI_Flash_SendByte(u8 byte);
extern u16 SPI_Flash_ReadByte(u8 a);
extern void drawbigpoint(unsigned int x,unsigned int y);
//extern unsigned int num;

//画笔颜色
u16  POINT_COLOR = Red;//默认红色    
u16  BACK_COLOR = White;//背景颜色.默认为白色

extern unsigned char _it0=0,_it1=0,_it2=0,_it3=0,num1=0;
unsigned char dw=0;
unsigned int Xs=0,Xe=0,Ys=0,Ye=0;
unsigned int X=0,Y=0; 
unsigned int count=0; 
float X2=0,Y2=0;

/*void touch(void)
{
  	unsigned char a = 0;
//	while (1)                  
//  	{    						   
		if(_it1 == 1)
		{
			delay_ms(10);
			a = PEN;
			if(a == 0)
			{
				while(a == 0)
				{
				    delay_us(10);
					Read_Ads7846();
					Xs = X; Ys = Y;
					a = PEN;
					_it1 = 0;
					num++;
					if (num == 2)
						num = 0;	
					break;
				}
			//	break;	 
			}
			else
			{
				_it1 = 0;
			}	
		}				
//  	}
//	ShowPicture();
//	_it1=0;	
}  */

void start_spi(void)   
{ 	   
	TCS_SET(0);   
}

//SPI写数据
//向7846写入1byte数据      
void WriteByteADS(u8 num)    
{  
	u8 count=0;  
	TCLK_SET(0);   
	for(count=0;count<8;count++)  
	{ 	  
		if(num&0x80)TDIN_SET(1);  
		else TDIN_SET(0);   
		num<<=1;    
		TCLK_SET(0);//上升沿有效  	 
		TCLK_SET(1);      
	} 			    
} 		
//SPI读数据 
//从7846读取adc值	   
u16 ReadWordADS(void)	  
{ 	 
	u8 count=0; 	  
	u16 Num1=0; 	 
	for(count=0;count<12;count++)  
	{ 				  
		Num1<<=1; 	 
		TCLK_SET(1);//下降沿有效 	   
		TCLK_SET(0);    
		if(DOUT)Num1++; 		 
	} 		  
	return(Num1);   
}
#define CMD_RDX 0X90  //0B10010000即用差分方式读X坐标
#define CMD_RDY	0XD0  //0B11010000即用差分方式读Y坐标 

 
//读取一次X,Y值
//读到的X,Y坐标值必须都大于100
//成功返回1,不成功返回0
//读数限制在100~3800之间.
u8 read_once(void)
{	
	unsigned int a,b;
	start_spi();//启动SPI  	 
	SPI_Flash_SendByte(CMD_RDY); 
	delay_us(3);	
	a=SPI_Flash_ReadByte(0);
	a=a<<8;
	a|=SPI_Flash_ReadByte(0);
	a>>=3; 
	Y=a;	  
    Pen_Point.Y=a;//读Y轴坐标
	SPI_Flash_SendByte(CMD_RDX);
	delay_us(3);	
	b=SPI_Flash_ReadByte(0);
	b=b<<8;
	b|=SPI_Flash_ReadByte(0);
	b>>=3; 
	Pen_Point.X=b;
	X=b;   

	TCS_SET(1); 
	if(Pen_Point.X>100&&Pen_Point.Y>100&&Pen_Point.X<4000&&Pen_Point.Y<4000)return 1;//读数成功(范围限制)
//	if(X>100&&Y>100&&X<4000&&Y<4000)return 1;//读数成功(范围限制)
	else return 0;
				                 //读数失败
}

/*******************************************************************************
* Function Name  : Read_Ads7846
* Description    : Read_Ads7846 program
* author         ：likuan
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/  	   
u8 Read_Ads7846(void)
{
	u8 t,t1,count=0;
	u16 databuffer[2][10];//数据组
	u16 temp=0;	 
	do					  //循环读数10次
	{		    		   
		if(read_once())//读数成功
		{	  
			databuffer[0][count]=Pen_Point.X;
			databuffer[1][count]=Pen_Point.Y;
			count++;  
		}
	}while(NPEN&&count<10);   
	if(count==10)//一定要读到10次数据,否则丢弃
	{  
	    do//将数据X升序排列
		{	
			t1=0;		  
			for(t=0;t<count-1;t++)
			{
				if(databuffer[0][t]>databuffer[0][t+1])//升序排列
				{
					temp=databuffer[0][t+1];
					databuffer[0][t+1]=databuffer[0][t];
					databuffer[0][t]=temp;
					t1=1; 
				}  
			}
		}while(t1); 	  
		do//将数据Y升序排列
		{	
			t1=0;		 
			for(t=0;t<count-1;t++)
			{
				if(databuffer[1][t]>databuffer[1][t+1])//升序排列
				{
					temp=databuffer[1][t+1];
					databuffer[1][t+1]=databuffer[1][t];
					databuffer[1][t]=temp;
					t1=1;	 
				}  
			}
		}while(t1);		   
		 	 		  
		Pen_Point.X=(databuffer[0][3]+databuffer[0][4]+databuffer[0][5])/3;
		Pen_Point.Y=(databuffer[1][3]+databuffer[1][4]+databuffer[1][5])/3;	  
		
		
	
		
																		  
	//	TFT_ShowString(100,140,"X read:");TFT_Show4Num(162,140,Pen_Point.X,16,0);	   //
	//	TFT_ShowString(100,172,"Y read:");TFT_Show4Num(162,172,Pen_Point.Y,16,0);
		return 1;									   
	}
	return 0;//读数失败
}	
	 

void delay_init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;//选择内部时钟 HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}								    
//延时Nms
//注意Nms的范围
//Nms<=0xffffff*8/SYSCLK
//对72M条件下,Nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01 ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
}   
//延时us								   
void delay_us(u32 Nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=Nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01 ;      //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	    
}	

//按键处理程序
//type:按键响应类型
//0,单点,定点,不扩展.一定要按键松开才返回
//1,单点,滑动,不扩展.滚动条操作/连加操作
//2,扩展按键支持:
//即:MOVE_LEFT,MOVE_RIGHT,MOVE_UP,MOVE_DOWN使能
u8 Touch_Key_Pro(u8 type)
{
	u16 tempx=0,tempy=0;//暂时保存X,Y坐标 	 	 
	u8 ml=0,mr=0,mu=0,md=0;//四个方向上移动次数  
	u8 first=1;	  		 	    					   		 
	//按键还是按下的
	//手动按触摸屏的时候,至少需要15ms才能退出这个循环	   	
	do
	{	    
		Pen_Point.Key_Sta=Key_Up;//按键状态变为松开    
		if(Read_Ads7846())//成功读数
		{	 
			if(first)
			{
				Pen_Point.X0=Pen_Point.X;Pen_Point.Y0=Pen_Point.Y;//得到初始按下的坐标
				tempx=Pen_Point.X;tempy=Pen_Point.Y;  
				//printf("X0:%d Y0:%d\n",Pen_Point.X,Pen_Point.Y);
				first=0;  //标记清空
			}else if(type==2) //扩展按键														  
			{	  
				if(tempx>Pen_Point.X)ml++;
				else mr++;	   	
				if(tempy>Pen_Point.Y)mu++;
				else md++;
				//设定一个门限值,不能让一次移动大于这个值,如果一次大于这个值
				//认为触摸屏误动作了.400的时候,反映比较慢
				if(abs(tempx-Pen_Point.X)>700||abs(tempy-Pen_Point.Y)>700)//有抖动
				{
					ml=mr=mu=md=0;//全部清掉
					tempx=Pen_Point.X=Pen_Point.X0;//坐标复位
					tempy=Pen_Point.Y=Pen_Point.Y0;
					break;//退出数据采集,结果为点采集
				}   
				tempx=Pen_Point.X;tempy=Pen_Point.Y;//转移临时坐标 
			}
			else if(type==1)break; 
			//printf("X:%d Y:%d\n",Pen_Point.X,Pen_Point.Y); 
		}
		delay_ms(10);//10ms消抖 						   		     								 	
	}while(NPEN||Pen_Point.Key_Sta==Key_Down);//PEN=0或者按键状态为按下状态;
	delay_ms(50);
	Pen_Point.Key_Sta=Key_Up;//按键状态变为松开	 
 	//单次/不扩展 键值处理  
	if(abs(tempx-Pen_Point.X0)<=200&&abs(tempy-Pen_Point.Y0)<=200||type<2)//单次按键/不扩展按键功能
	{	 
		if(Pen_Point.xfac!=0)//已经校准过了
		{
			Pen_Point.X0=Pen_Point.xfac*Pen_Point.X0+Pen_Point.xoff;
			Pen_Point.Y0=Pen_Point.yfac*Pen_Point.Y0+Pen_Point.yoff;
		}
		Pen_Point.X=Pen_Point.X0;Pen_Point.Y=Pen_Point.Y0;
		return CLICK_POINT;//没有移动  
	}	 
	//扩展键值处理
	if(abs(tempx-Pen_Point.X0)<=500&&abs(tempy-Pen_Point.Y0)<=500)return 0;//滑动距离最少要大于500
	else if(Pen_Point.xfac!=0)//已经校准过了
	{
		Pen_Point.X0=Pen_Point.xfac*Pen_Point.X0+Pen_Point.xoff;
		Pen_Point.Y0=Pen_Point.yfac*Pen_Point.Y0+Pen_Point.yoff;

		tempx=Pen_Point.xfac*tempx+Pen_Point.xoff;
		tempy=Pen_Point.yfac*tempy+Pen_Point.yoff;
	}
		
	if(abs(ml-mr)>abs(mu-md))//数量 满足
	{
		if(abs(tempx-Pen_Point.X0)>abs(tempy-Pen_Point.Y0))//质量满足
		{
			if(tempx>Pen_Point.X0)return MOVE_RIGHT;
			else return MOVE_LEFT; 
		}else						//质量不满足
		{
			if(tempy>Pen_Point.Y0)return MOVE_DOWN;
			else return MOVE_UP;
		}
	}else
	{
		if(abs(tempy-Pen_Point.Y0)>abs(tempx-Pen_Point.X0))//质量满足
		{	    
			if(tempy>Pen_Point.Y0)return MOVE_DOWN;
			else return MOVE_UP;			 
		}else						//质量不满足
		{	  
			if(tempx>Pen_Point.X0)return MOVE_RIGHT;
			else return MOVE_LEFT;
		}
	}   	  
}




//判断触点是不是在指定区域之内
//(x1,y1):起始坐标
//(x2,y2):结束坐标
//返回值 :1,在该区域内.0,不在该区域内.
u8 Is_In_Area(u8 x1,u16 y1,u8 x2,u16 y2)
{
	if(Pen_Point.X<=x2&&Pen_Point.X>=x1&&Pen_Point.Y<=y2&&Pen_Point.Y>=y1)return 1;
	else return 0;
}  

//把触摸屏得到的数据转换为数字(按钮值)
//M_Type:按钮模式;
//0,系统菜单	
//1,文件浏览模式 	
//2,时间模式下,按键的获取,连按支持! 
//3,音乐播放模式下
//4,功能选择模式下
//5,收音机模式下
//6,闹钟中断程序按键			  
//返回值:对应的按键值(1~n)
//返回0,则表示此次按键无效 
/*
u8 Touch_To_Num(u8 M_Type)
{
	u8 xtemp;
	u16 t,ytemp;
	switch(M_Type)
	{
		case 0://系统菜单下
			xtemp=Touch_Key_Pro(1);//不使用扩展按钮
			if(!(xtemp&CLICK_POINT))return 0;//不是点触直接退出
			ytemp=10;
			for(t=0;t<9;t++)
			{
				xtemp=80*(t%3)+10;
				if(t>5)ytemp=216;
				else if(t>2)ytemp=113;
				if(Is_In_Area(xtemp,ytemp,xtemp+59,ytemp+90))return t+1;//返回按键值 
			}
			break;
		case 1://1,文件浏览模式
			xtemp=Touch_Key_Pro(2);//支持扩展	 
			if(xtemp&CLICK_POINT)  //点触摸	 得到1~8的值
			{
				for(t=0;t<8;t++)
				{	  
					if(Is_In_Area(0,42+t*32,239,42+(t+1)*32))return t+1;
				}
				if(Is_In_Area(0,300,40,319))return 9;//选择按钮被按下
				if(Is_In_Area(200,300,239,319))return 10;//返回按钮被按下
				return 0;//按键无效
			}
			if(xtemp)return xtemp&0xf0;//滑动触摸了!! 
			break; 
		case 2://2,时间模式下,按键的获取,连按支持!
			xtemp=Touch_Key_Pro(1);//不扩展
			if(xtemp&CLICK_POINT)  //点触摸	 得到1~8的值
			{
				if(Is_In_Area(4,142,28,166))return 1;	    
				else if(Is_In_Area(60,142,84,166))return 2;
				else if(Is_In_Area(96,142,120,166))return 3;
				else if(Is_In_Area(136,142,160,166))return 4;
				else if(Is_In_Area(172,142,196,166))return 5;
				else if(Is_In_Area(212,142,236,166))return 6;

				else if(Is_In_Area(4,206,28,230))return 7;	    
				else if(Is_In_Area(60,206,84,230))return 8;
				else if(Is_In_Area(96,206,120,230))return 9;
				else if(Is_In_Area(136,206,160,230))return 10;
				else if(Is_In_Area(172,206,196,230))return 11;
				else if(Is_In_Area(212,206,236,230))return 12;
															   
				else if(Is_In_Area(0,300,40,319))return 13;//选择按钮被按下
				else if(Is_In_Area(200,300,239,319))return 14;//返回按钮被按下
				return 0;//按键无效
			}
			break;
		case 3://MP3界面下面的按钮值
			xtemp=Touch_Key_Pro(1);//不扩展
			if(xtemp&CLICK_POINT)  //点触摸	 得到1~8的值
			{
				if(Is_In_Area(214,72,240,96))return 1;//循环模式更改	    
				else if(Is_In_Area(87,103,153,119))return 2; //supper bass
				else if(Is_In_Area(8,223,56,247))return 3;   //音效存/取
				else if(Is_In_Area(64,223,112,247))return 4; //音量
				else if(Is_In_Area(120,223,168,247))return 5;//其他
				else if(Is_In_Area(178,224,204,276))return 6;//回车	 
				else if(Is_In_Area(214,224,238,248))return 7;//增加	    
				else if(Is_In_Area(214,252,238,276))return 8; //减少
					
				else if(Is_In_Area(28,288,52,312))return 9;	  //后一取
				else if(Is_In_Area(108,288,132,312))return 10;//播放
				else if(Is_In_Area(188,288,212,312))return 11;//上一曲

				else if(Is_In_Area(30,83,210,98))return 12;	  //进度条按下,y方向扩大了一点范围
															   
				//else if(Is_In_Area(0,300,40,319))return 13;//选择按钮被按下
				//else if(Is_In_Area(200,300,239,319))return 14;//返回按钮被按下
				return 0;//按键无效
			}
		case 4://4,功能选择模式下
			xtemp=Touch_Key_Pro(1);//不支持扩展	  
			if(xtemp&CLICK_POINT)  //点触摸	 得到1~8的值
			{
				for(t=0;t<8;t++)
				{	  
					if(Is_In_Area(0,42+t*32,239,42+(t+1)*32))return t+1;
				}
				if(Is_In_Area(0,300,40,319))return 9;//选择按钮被按下
				if(Is_In_Area(200,300,239,319))return 10;//返回按钮被按下
				return 0;//按键无效
			}										    
			break;
		case 5://5,收音机模式下
			xtemp=Touch_Key_Pro(1);//不支持扩展	
			if(xtemp&CLICK_POINT)  //点触摸	 得到1~8的值
			{
				if(Is_In_Area(37,215,61,239))return 1;//循环模式更改	    
				else if(Is_In_Area(93,215,117,239))return 2;//循环模式更改
				else if(Is_In_Area(152,218,203,236))return 3;   //音效存/取		 
					
				else if(Is_In_Area(28,261,52,285))return 4;	 //后一取
				else if(Is_In_Area(108,261,132,285))return 5;//播放
				else if(Is_In_Area(188,261,212,285))return 6;//上一曲
																		   
				else if(Is_In_Area(0,300,40,319))return 7;//选项按钮被按下
				else if(Is_In_Area(200,300,239,319))return 8;//返回按钮被按下
				return 0;//按键无效
			}  
			break; 
		case 6://6,闹钟中断程序按键
			xtemp=Touch_Key_Pro(1);//不支持扩展	
			if(xtemp&CLICK_POINT)  //点触摸	 得到1~8的值
			{
				if(Is_In_Area(111,151,153,169))return 1;//循环模式更改	       
				return 0;//按键无效
			}  
			break; 	  	    		 
	}
	return 0;
}	*/		
/*******************************************************************************
* Function Name  : touch_adjust
* Description    : 触摸屏校准
* author         ：李宽
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/ 
void touch_adjust(void)
{								 
	u16 pos_temp[4][2];//坐标缓存值
	u8  cnt=0;	
	u16 d1,d2;
	u32 tem1,tem2;
	float fac; 
	 
	cnt=0;				
	POINT_COLOR=Blue;
	BACK_COLOR =White;
	LCD_Clear(White);
	LCD_DisplayStringLine(110,"   Touch Screen Adjusting...");
	delay_ms(1000);	    
	POINT_COLOR=Red;//红色
	LCD_Clear(White);  
//	drow_touch_point(20,20);//画点1 
	Pen_Point.Key_Sta=Key_Up;//消除触发信号 
	Pen_Point.xfac=0;//xfac用来标记是否校准过,所以校准之前必须清掉!以免错误	 
	while(1)
	{
		if(Pen_Point.Key_Sta==Key_Down)//按键按下了
		{
			if(Touch_Key_Pro(1)&CLICK_POINT)//得到单次按键值
			{  								   
				pos_temp[cnt][0]=Pen_Point.X;
				pos_temp[cnt][1]=Pen_Point.Y;
				cnt++;
			}			 
			switch(cnt)
			{			   
				case 1:
					LCD_Clear(White);
				//	drow_touch_point(220,20);//画点2
					break;
				case 2:
					LCD_Clear(White);
				//	drow_touch_point(20,300);//画点3
					break;
				case 3:
					LCD_Clear(White);
				//	drow_touch_point(220,300);//画点4
					break;
				case 4:	 //全部四个点已经得到
	    		    //对边相等
					tem1=abs(pos_temp[0][0]-pos_temp[1][0]);//x1-x2
					tem2=abs(pos_temp[0][1]-pos_temp[1][1]);//y1-y2
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//得到1,2的距离
					
					tem1=abs(pos_temp[2][0]-pos_temp[3][0]);//x3-x4
					tem2=abs(pos_temp[2][1]-pos_temp[3][1]);//y3-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//得到3,4的距离
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//不合格
					{
						cnt=0;
						LCD_Clear(White); 
//						drow_touch_point(20,20);
						continue;
					}
					tem1=abs(pos_temp[0][0]-pos_temp[2][0]);//x1-x3
					tem2=abs(pos_temp[0][1]-pos_temp[2][1]);//y1-y3
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//得到1,3的距离
					
					tem1=abs(pos_temp[1][0]-pos_temp[3][0]);//x2-x4
					tem2=abs(pos_temp[1][1]-pos_temp[3][1]);//y2-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//得到2,4的距离
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//不合格
					{
						cnt=0;
						LCD_Clear(White);
//						drow_touch_point(20,20);
						continue;
					}//正确了
								   
					//对角线相等
					tem1=abs(pos_temp[1][0]-pos_temp[2][0]);//x1-x3
					tem2=abs(pos_temp[1][1]-pos_temp[2][1]);//y1-y3
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//得到1,4的距离
	
					tem1=abs(pos_temp[0][0]-pos_temp[3][0]);//x2-x4
					tem2=abs(pos_temp[0][1]-pos_temp[3][1]);//y2-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//得到2,3的距离
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//不合格
					{
						cnt=0;
						LCD_Clear(White); 
					//	drow_touch_point(20,20);
						continue;
					}//正确了
					//计算结果
					Pen_Point.xfac=(float)200/(pos_temp[1][0]-pos_temp[0][0]);//得到xfac		 
					Pen_Point.xoff=(240-Pen_Point.xfac*(pos_temp[1][0]+pos_temp[0][0]))/2;//得到xoff
						  
					Pen_Point.yfac=(float)280/(pos_temp[2][1]-pos_temp[0][1]);//得到yfac
					Pen_Point.yoff=(320-Pen_Point.yfac*(pos_temp[2][1]+pos_temp[0][1]))/2;//得到yoff  
					
					POINT_COLOR=Blue;
					LCD_Clear(White);
					LCD_DisplayStringLine(110,"   Touch Screen Adjust OK!");
					delay_ms(1800);
					LCD_Clear(White);  
				//	save_adjdata();
					return;//校正完成				 
			}
		}
	} 
}




/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/


