/*
 * SYSTick.c
 *
 *  Created on: Mar 28, 2025
 *      Author: 17438
 */

#include "SysTick.h"

static uint32_t fac_us=0;

void SysTick_Init(uint8_t SYSCLK){
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	fac_us=SYSCLK;
}

void delay_us(uint32_t udelay) {
	__IO uint32_t Delay = udelay * 168 / 8;//(SystemCoreClock / 8U / 1000000U)
	//见stm32f1xx_hal_rcc.c -- static void RCC_Delay(uint32_t mdelay)
	do{
		__NOP();
	}while(Delay --);
}
