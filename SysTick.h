/*
 * SysTick.h
 *
 *  Created on: Mar 28, 2025
 *      Author: 17438
 */

#ifndef INC_SYSTICK_H_
#define INC_SYSTICK_H_
#include "main.h"

void SysTick_Init(uint8_t SYSCLK);
void delay_us(uint32_t nus);

#endif /* INC_SYSTICK_H_ */
