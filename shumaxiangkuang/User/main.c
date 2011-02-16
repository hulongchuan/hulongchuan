/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.0
* Date               : 05/23/2008
* DescriptWHY8W-QT9DJ-P0VNX-L15PE-W4DCR-VP3FMion        : Main program body
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED 
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "stm32f10x_gpio.h"
//#include "fonts.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_nvic.h"
#include "SPI_Flash.h"
#include "touch.h"
#include "lcd.h"



void SystemInit(void);
static void SetSysClock(void);
void FSMC_LCD_Init(void);
void NVIC_Configuration(void);
void GPIO_Config(void);
void EXTI_Config(void);
void Timer_Config(void);

extern void touch(void);
extern void touch_adjust(void);
extern void delay_init(u8 SYSCLK);

void  Delay (u32 nCount)
{
  for(; nCount != 0; nCount--);
}

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;

/* Private typedef -----------------------------------------------------------*/
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main
* Description    : main program
* author         ：hulongchuan
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
extern int num , flag;
int main(void)
{
	SystemInit();				  // initial the system
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	delay_init(72);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);    
	GPIO_Config();
	SPI_Flash_Init();
	FSMC_LCD_Init(); 
	EXTI_Config(); 
	LCD_Setup();			  	
	NVIC_Configuration();
		
	while (1)				//always running the test
	{
		test();
	}	
}

/*******************************************************************************
* Function Name  : SystemInit
* Description    : Init the system
* author         ：wangxiaotao
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void SystemInit (void)
{
  /*!< RCC system reset(for debug purpose) */
  /*!< Set HSION bit 复位值是83H   内部8M*/			  
  RCC->CR |= (uint32_t)0x00000001;	  
  /*!< Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], ADCPRE[1:0] and MCO[2:0] bits */
  RCC->CFGR &= (uint32_t)0xF8FF0000;  
  /*!< Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;
  /*!< Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;
  /*!< Reset PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;
  /*!< Disable all interrupts */
  RCC->CIR = 0x00000000;
    
  /*!< Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
  /*!< Configure the Flash Latency cycles and enable prefetch buffer */
  SetSysClock();

}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : NVIC_Configuration  program
* author         ：hulongchuan
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* Enable the EXTI9_5 Interrupt */
  

 // NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn  ;
  	NVIC_InitStructure.NVIC_IRQChannel = 23  ;

  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);

    /* Configure Key Button EXTI Line to generate an interrupt on falling edge */  
  	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);


  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;	  //通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	  //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  													
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQChannel;	  //通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	  //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  													
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQChannel;	  //通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	  //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
}


static void SetSysClock(void)
{
	#ifdef SYSCLK_FREQ_HSE
	  SetSysClockToHSE();
	#elif defined SYSCLK_FREQ_20MHz
	  SetSysClockTo20();
	#elif defined SYSCLK_FREQ_36MHz
	  SetSysClockTo36();
	#elif defined SYSCLK_FREQ_48MHz
	  SetSysClockTo48();
	#elif defined SYSCLK_FREQ_56MHz
	  SetSysClockTo56();  
	#elif defined SYSCLK_FREQ_72MHz
	  SetSysClockTo72();
	#endif
 
 /*!< If none of the define above is enabled, the HSI is used as System clock
    source (default after reset) */ 
}

/*******************************************************************************
* Function Name  : EXTI_Config
* Description    : EXTI_Config  program
* author         ：hulongchuan
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
			 	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);	//管脚选择
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);
	EXTI_ClearITPendingBit(EXTI_Line3);
	EXTI_ClearITPendingBit(EXTI_Line2);

	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

/*******************************************************************************
* Function Name  : FSMC_LCD_Init
* Description    : FSMC_LCD_Init  program
* author         ：hulongchuan
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void FSMC_LCD_Init(void)
{
	  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	  FSMC_NORSRAMTimingInitTypeDef  FSMC_TimingInitStructure;
	
	  FSMC_TimingInitStructure.FSMC_AddressSetupTime = 0x02;
	  FSMC_TimingInitStructure.FSMC_AddressHoldTime = 0x00;
	  FSMC_TimingInitStructure.FSMC_DataSetupTime = 0x05;
	  FSMC_TimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
	  FSMC_TimingInitStructure.FSMC_CLKDivision = 0x00;
	  FSMC_TimingInitStructure.FSMC_DataLatency = 0x00;
	  FSMC_TimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_B;
	
	  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
	  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_TimingInitStructure;
	  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_TimingInitStructure;	  
	
	  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
	  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}

/**
  * @brief  EXTI_Config Program.
  * @param  None
  * @retval : None
  */
void Timer_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);

	TIM_DeInit(TIM2);

	TIM_TimeBaseStructure.TIM_Period = 3000;		 					//自动重装载寄存器周期的值(计数值)
																	//累计 TIM_Period个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Prescaler = (36000 - 1);				//时钟预分频数   例如：时钟频率=72MHZ/(时钟预分频+1)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 			//采样分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 		//向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);							//清除溢出中断标志							//禁止ARR预装载缓冲器
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

	TIM_Cmd(TIM2, ENABLE);											//开启时钟
}

/*******************************************************************************
* Function Name  : GPIO_Config
* Description    : GPIO_Config  program
* author         ：wangxiaotao
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Config(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
	                         RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE); 
							 
	/**
	 *	LED1 -> PB8	 ,	LED2 -> PB9 , LED3 -> PE0 , LED4 -> PE1
	 *  Key1 -> PE2  ,  Key2 -> PE3
	 */	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	  GPIO_Init(GPIOB, &GPIO_InitStructure);					 
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 |GPIO_Pin_3;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	  GPIO_Init(GPIOE, &GPIO_InitStructure);
}


#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
	  /* User can add his own implementation to report the file name and line number,
	     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	
	  /* Infinite loop */
	  while (1)
	  {
	  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
