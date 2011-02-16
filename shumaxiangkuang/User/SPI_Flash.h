#ifndef _SPI_FLASH_H_
#define _SPI_FLASH_H_  1
//#include "stm32f10x_lib.h"

/* Select SPI FLASH: ChipSelect pin low  */
#define Select_Flash()     GPIO_ResetBits(GPIOA, GPIO_Pin_4)
/* Deselect SPI FLASH: ChipSelect pin high */
#define NotSelect_Flash()    GPIO_SetBits(GPIOA, GPIO_Pin_4)



void SPI_Flash_Init(void);	         //SPI≥ı ºªØ



#endif


