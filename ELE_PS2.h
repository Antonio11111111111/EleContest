/**
  ******************************************************************************
  * @file    ax_ps2.h
  * @author  Musk Han @ XTARK
  * @version V1.1
  * @date    2018-01-01
  * @brief   X-CTR100 PS2 joystick driver file
  *
  ******************************************************************************
  * @xtark  Implemented on the X-CTR100 development platform
  *         For more information, visit <url id="cvhul7oc86s5oci5ifgg" type="url" status="parsed" title="XTARK - Focused on AI Education and Research Robots" wc="1004">http://www.xtark.cn</url> 
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ELE_PS2_H
#define __ELE_PS2_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "ELE_glbDef.h"
#include "main.h"
#include "SysTick.h"

// Joystick value structure definition
typedef struct{
	uint8_t mode;							/* Joystick mode */
	uint8_t btn1;							/* Bit0 Bit1 Bit2 Bit3 Bit4 Bit5 Bit6 Bit7*/

	uint8_t btn2;							/* Bit0 Bit1 Bit2 Bit3 Bit4 Bit5 Bit6 Bit7*/

	uint8_t RJoy_LR;						/* Right joystick left-right	0x00 = left	0xff = right */
	uint8_t RJoy_UD;						/* Right joystick up-down		0x00 = up	0xff = down */
	uint8_t LJoy_LR;						/* Left joystick left-right		0x00 = left	0xff = right */
	uint8_t LJoy_UD;						/* Left joystick up-down		0x00 = up 	0xff = down */
}ELE_PS2_TypeDef;

/* X-CTR100 PS2 joystick driver functions */
void ELE_PS2_Init(void);  // PS2 initialization
void ELE_PS2_Scan_Key(ELE_PS2_TypeDef *ELE_PS2_Struct); // PS2 scan keys and update joystick values

#endif

/******************* (C)2018 XTARK **************************************/
