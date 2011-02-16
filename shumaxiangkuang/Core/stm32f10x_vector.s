;******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
;* File Name          : stm32f10x_vector.s
;* Author             : MCD Application Team
;* Version            : V2.0
;* Date               : 05/23/2008
;* Description        : STM32F10x vector table for RVMDK toolchain. 
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Configure external SRAM mounted on STM3210E-EVAL board
;*                        to be used as data memory (optional, to be enabled by user)
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM3 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;* <<< Use Configuration Wizard in Context Menu >>>   
;*******************************************************************************
; THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
; WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
; AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
; INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
; CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
; INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
; FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED 
; IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
;*******************************************************************************

; If you need to use external SRAM mounted on STM3210E-EVAL board as data memory,
; change the following define value to '1' (or choose ENABLE in Configuration Wizard window)
;//   <o>  External SRAM Configuration  <0=> DISABLE <1=> ENABLE 
DATA_IN_ExtSRAM  EQU     0


; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
;// <h> Stack Configuration
;//   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;// </h>
Stack_Size       EQU     0x00000400

                 AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem        SPACE   Stack_Size

__initial_sp
; If you need to use external SRAM mounted on STM3210E-EVAL board as data memory
; and internal SRAM for Stack, uncomment the following line and comment the line above
;__initial_sp    EQU 0x20000000 + Stack_Size ; "Use MicroLIB" must be checked in
                                             ; the Project->Options->Target window

; Amount of memory (in bytes) allocated for Heap
; Tailor this value to your application needs
;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;// </h>

Heap_Size        EQU     0x00000400

                 AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem         SPACE   Heap_Size
__heap_limit
		

                 THUMB
                 PRESERVE8

                 ; Import exceptions handlers
                 IMPORT  NMIException
                 IMPORT  HardFaultException
                 IMPORT  MemManageException
                 IMPORT  BusFaultException
                 IMPORT  UsageFaultException
                 IMPORT  SVCHandler
                 IMPORT  DebugMonitor
                 IMPORT  PendSVC
                 IMPORT  SysTickHandler
                 IMPORT  WWDG_IRQHandler
                 IMPORT  PVD_IRQHandler
                 IMPORT  TAMPER_IRQHandler
                 IMPORT  RTC_IRQHandler
                 IMPORT  FLASH_IRQHandler
                 IMPORT  RCC_IRQHandler
                 IMPORT  EXTI0_IRQHandler
                 IMPORT  EXTI1_IRQHandler
                 IMPORT  EXTI2_IRQHandler
                 IMPORT  EXTI3_IRQHandler
                 IMPORT  EXTI4_IRQHandler
                 IMPORT  DMA1_Channel1_IRQHandler
                 IMPORT  DMA1_Channel2_IRQHandler
                 IMPORT  DMA1_Channel3_IRQHandler
                 IMPORT  DMA1_Channel4_IRQHandler
                 IMPORT  DMA1_Channel5_IRQHandler
                 IMPORT  DMA1_Channel6_IRQHandler
                 IMPORT  DMA1_Channel7_IRQHandler
                 IMPORT  ADC1_2_IRQHandler
                 IMPORT  USB_HP_CAN_TX_IRQHandler
                 IMPORT  USB_LP_CAN_RX0_IRQHandler
                 IMPORT  CAN_RX1_IRQHandler
                 IMPORT  CAN_SCE_IRQHandler
                 IMPORT  EXTI9_5_IRQHandler
                 IMPORT  TIM1_BRK_IRQHandler
                 IMPORT  TIM1_UP_IRQHandler
                 IMPORT  TIM1_TRG_COM_IRQHandler
                 IMPORT  TIM1_CC_IRQHandler
                 IMPORT  TIM2_IRQHandler
                 IMPORT  TIM3_IRQHandler
                 IMPORT  TIM4_IRQHandler
                 IMPORT  I2C1_EV_IRQHandler
                 IMPORT  I2C1_ER_IRQHandler
                 IMPORT  I2C2_EV_IRQHandler
                 IMPORT  I2C2_ER_IRQHandler
                 IMPORT  SPI1_IRQHandler
                 IMPORT  SPI2_IRQHandler
                 IMPORT  USART1_IRQHandler
                 IMPORT  USART2_IRQHandler
                 IMPORT  USART3_IRQHandler
                 IMPORT  EXTI15_10_IRQHandler
                 IMPORT  RTCAlarm_IRQHandler
                 IMPORT  USBWakeUp_IRQHandler
                 IMPORT  TIM8_BRK_IRQHandler
                 IMPORT  TIM8_UP_IRQHandler
                 IMPORT  TIM8_TRG_COM_IRQHandler
                 IMPORT  TIM8_CC_IRQHandler
                 IMPORT  ADC3_IRQHandler
                 IMPORT  FSMC_IRQHandler
                 IMPORT  SDIO_IRQHandler
                 IMPORT  TIM5_IRQHandler
                 IMPORT  SPI3_IRQHandler
                 IMPORT  UART4_IRQHandler
                 IMPORT  UART5_IRQHandler
                 IMPORT  TIM6_IRQHandler
                 IMPORT  TIM7_IRQHandler
                 IMPORT  DMA2_Channel1_IRQHandler
                 IMPORT  DMA2_Channel2_IRQHandler
                 IMPORT  DMA2_Channel3_IRQHandler
                 IMPORT  DMA2_Channel4_5_IRQHandler
                 
;*******************************************************************************
; Fill-up the Vector Table entries with the exceptions ISR address
;*******************************************************************************
                 AREA    RESET, DATA, READONLY
                 EXPORT  __Vectors
                      
__Vectors        DCD  __initial_sp              ; Top of Stack
                 DCD  Reset_Handler
                 DCD  NMIException
                 DCD  HardFaultException
                 DCD  MemManageException
                 DCD  BusFaultException
                 DCD  UsageFaultException
                 DCD  0                 ; Reserved
                 DCD  0                 ; Reserved
                 DCD  0                 ; Reserved
                 DCD  0                 ; Reserved
                 DCD  SVCHandler
                 DCD  DebugMonitor
                 DCD  0                 ; Reserved
                 DCD  PendSVC
                 DCD  SysTickHandler
                 DCD  WWDG_IRQHandler
                 DCD  PVD_IRQHandler
                 DCD  TAMPER_IRQHandler
                 DCD  RTC_IRQHandler
                 DCD  FLASH_IRQHandler
                 DCD  RCC_IRQHandler
                 DCD  EXTI0_IRQHandler
                 DCD  EXTI1_IRQHandler
                 DCD  EXTI2_IRQHandler
                 DCD  EXTI3_IRQHandler
                 DCD  EXTI4_IRQHandler
                 DCD  DMA1_Channel1_IRQHandler
                 DCD  DMA1_Channel2_IRQHandler
                 DCD  DMA1_Channel3_IRQHandler
                 DCD  DMA1_Channel4_IRQHandler
                 DCD  DMA1_Channel5_IRQHandler
                 DCD  DMA1_Channel6_IRQHandler
                 DCD  DMA1_Channel7_IRQHandler
                 DCD  ADC1_2_IRQHandler
                 DCD  USB_HP_CAN_TX_IRQHandler
                 DCD  USB_LP_CAN_RX0_IRQHandler
                 DCD  CAN_RX1_IRQHandler
                 DCD  CAN_SCE_IRQHandler
                 DCD  EXTI9_5_IRQHandler
                 DCD  TIM1_BRK_IRQHandler
                 DCD  TIM1_UP_IRQHandler
                 DCD  TIM1_TRG_COM_IRQHandler
                 DCD  TIM1_CC_IRQHandler
                 DCD  TIM2_IRQHandler
                 DCD  TIM3_IRQHandler
                 DCD  TIM4_IRQHandler
                 DCD  I2C1_EV_IRQHandler
                 DCD  I2C1_ER_IRQHandler
                 DCD  I2C2_EV_IRQHandler
                 DCD  I2C2_ER_IRQHandler
                 DCD  SPI1_IRQHandler
                 DCD  SPI2_IRQHandler
                 DCD  USART1_IRQHandler
                 DCD  USART2_IRQHandler
                 DCD  USART3_IRQHandler
                 DCD  EXTI15_10_IRQHandler
                 DCD  RTCAlarm_IRQHandler
                 DCD  USBWakeUp_IRQHandler 
                 DCD  TIM8_BRK_IRQHandler
                 DCD  TIM8_UP_IRQHandler
                 DCD  TIM8_TRG_COM_IRQHandler
                 DCD  TIM8_CC_IRQHandler
                 DCD  ADC3_IRQHandler
                 DCD  FSMC_IRQHandler
                 DCD  SDIO_IRQHandler
                 DCD  TIM5_IRQHandler
                 DCD  SPI3_IRQHandler
                 DCD  UART4_IRQHandler
                 DCD  UART5_IRQHandler
                 DCD  TIM6_IRQHandler
                 DCD  TIM7_IRQHandler
                 DCD  DMA2_Channel1_IRQHandler
                 DCD  DMA2_Channel2_IRQHandler
                 DCD  DMA2_Channel3_IRQHandler
                 DCD  DMA2_Channel4_5_IRQHandler
                 
                 AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler    PROC
                 EXPORT  Reset_Handler
				 
				         IF      DATA_IN_ExtSRAM == 1
; FSMC Bank1 NOR/SRAM3 is used for the STM3210E-EVAL, if another Bank is 
; required, then adjust the Register Addresses


; Enable FSMC clock
				         LDR R0,= 0x00000114 
				         LDR R1,= 0x40021014
				         STR R0,[R1]	                 
                  
; Enable GPIOD, GPIOE, GPIOF and GPIOG clocks
				         LDR R0,= 0x000001E0
				         LDR R1,= 0x40021018
				         STR R0,[R1]	   

; SRAM Data lines, NOE and NWE configuration 
; SRAM Address lines configuration 
; NOE and NWE configuration   
; NE3 configuration 
; NBL0, NBL1 configuration 

				         LDR R0,= 0x44BB44BB 
				         LDR R1,= 0x40011400
				         STR R0,[R1]		
				 
				         LDR R0,= 0xBBBBBBBB 
				         LDR R1,= 0x40011404
				         STR R0,[R1]		
				 
				         LDR R0,= 0xB44444BB 
				         LDR R1,= 0x40011800
				         STR R0,[R1]		
				 
				         LDR R0,= 0xBBBBBBBB 
				         LDR R1,= 0x40011804
				         STR R0,[R1]		
				 
				         LDR R0,= 0x44BBBBBB 
				         LDR R1,= 0x40011C00
				         STR R0,[R1]	    

				         LDR R0,= 0xBBBB4444 
				         LDR R1,= 0x40011C04
				         STR R0,[R1]	    

				         LDR R0,= 0x44BBBBBB
				         LDR R1,= 0x40012000
				         STR R0,[R1]		

				         LDR R0,= 0x44444B44
				         LDR R1,= 0x40012004
				         STR R0,[R1]      
				         
; FSMC Configuration   
; Enable FSMC Bank1_SRAM Bank 

				        LDR R0,= 0x00001011
				        LDR R1,= 0xA0000010
				        STR R0,[R1]	

				        LDR R0,= 0x00000200 
				        LDR R1,= 0xA0000014
				        STR R0,[R1]	

				  		 
				        ENDIF
				        
				        
				 IMPORT  __main
                 LDR     R0, =__main
                 BX      R0
                 ENDP

                 ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB           
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE*****
