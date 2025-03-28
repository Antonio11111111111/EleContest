/**
  ******************************************************************************
  * @file    ax_ps2.c
  * @author  Musk Han @ XTARK
  * @version V1.0
  * @date    2018-01-01
  * @brief   X-CTR100 PS2 interface driver file, supports both master and slave modes
  *
  ******************************************************************************
  * @xtark  Implemented on the X-CTR100 development platform
  *         For more information, visit <url id="cvhuc9e4bbjii2u3bna0" type="url" status="parsed" title="XTARK - Focused on AI Education and Research Robots" wc="1004">http://www.xtark.cn</url> 
  * 
  ******************************************************************************
  */

#include "ELE_PS2.h"

//PS2手柄的输入输出口
#define ELE_PS2_DATA_Read()	HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7)
#define ELE_PS2_CM_H()		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET)
#define ELE_PS2_CM_L()		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET)
#define ELE_PS2_ATT_H()		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET)
#define ELE_PS2_ATT_L()		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET)
#define ELE_PS2_CLK_H()		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET)
#define ELE_PS2_CLK_L()		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET)

const uint8_t ELE_PS2_Command[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};//向PS2的固定通信指令
static uint8_t ELE_PS2_Data[9] = {0};//接收数据

//GPIO已经在GPIO初始化中进行, 此处延时两秒供手柄与接收器配对
void ELE_PS2_Init(void){
	delay_us(2000000);
}

//读写同时进行, 参数是STM32发送给手柄模块的值, 返回值是手柄模块发送给STM32的值
//不在每字节收发拉ATT(CS)低电平,而是在ScanKey时进行片选
static uint8_t ELE_PS2_Read_Write_Data(uint8_t data){
	//ref表示"第几位", res存放接收到的字节
	uint8_t ref,res = 0x00;
	//循环 低位先行 使用CM(高电平有效)
	for(ref = 0x01; ref > 0x00; ref <<= 1){
		//时钟拉低
		ELE_PS2_CLK_L();
		//写CMD引脚
		if(ref&data){
			//CM发送1
			ELE_PS2_CM_H();
		}else{
			//CM发送0
			ELE_PS2_CM_L();
		}
		delay_us(10);

		//时钟拉高
		ELE_PS2_CLK_H();
		delay_us(10);
		if(ELE_PS2_DATA_Read()){
			res |= ref;
		}
	}
	//CM恢复默认高电平
	ELE_PS2_CM_H();
	return res;
}

void ELE_PS2_Scan_Key(ELE_PS2_TypeDef *ELE_PS2_Struct){
	uint8_t i;

	ELE_PS2_ATT_L();
	delay_us(10);
	for(i=0; i<9; i++){
		ELE_PS2_Data[i] = ELE_PS2_Read_Write_Data(ELE_PS2_Command[i]);
		delay_us(10);
	}
	ELE_PS2_ATT_H();

	ELE_PS2_Struct->mode = ELE_PS2_Command[1];
	ELE_PS2_Struct->btn1 = ELE_PS2_Command[3];
	ELE_PS2_Struct->btn2 = ELE_PS2_Command[4];
	ELE_PS2_Struct->RJoy_LR = ELE_PS2_Command[5];
	ELE_PS2_Struct->RJoy_UD = ELE_PS2_Command[6];
	ELE_PS2_Struct->LJoy_LR = ELE_PS2_Command[7];
	ELE_PS2_Struct->LJoy_UD = ELE_PS2_Command[8];
}

/******************* (C) 2018 XTARK **************************************/
