/* This file is aimed at repackaging the ax Library. But as the TIM I/Os is not defined ,
 * the file is in the state: TODO */
/* Pose initialization function should be written and this work is better to be given to Wang Maoyao. */


/* 修改记录2025/3/27 0:15 OhzyMain
 * 1.简写了ELE_Motor_Steering_Machine_Init(void);
 * 2.略微改动ELE_Motor_Calculate_Pulse_Width(u16 angle)数据换算中的类型转换;
 * 3.修改了ELE_Motor_Steering_Machine_Moving(...)的参数, 增加了Motor控制引脚(PWM输出引脚)对应的TIM的句柄指针和通道, 已在ELE_Motor.h文件中宏定义;
 * 4.将main.h和tim.h放到ELE_Motor.h中引用*/

#include "ELE_Motor.h"


// Steering Machine initialize
void ELE_Motor_Steering_Machine_Init(void){
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_ALL);
}

// Calculate the pulse width with the target angle **TO BE Modified**
// 换算公式取决于定时器的的配置
u16 ELE_Motor_Calculate_Pulse_Width(u16 angle){
	//Ensure the angle is between 0 and 180
	if (angle > 180){angle = 180;}
	if (angle < 0){angle = 0;}
	u16 pulseWidth = (u16)(1000 + (fp)(angle * 1000) / 180);
	return pulseWidth;
}
// Steering Machine move at a particular angle
void ELE_Motor_Steering_Machine_Moving(TIM_HandleTypeDef *handle, u32 channel, u16 angle){
	u16 temp_d = ELE_Motor_Calculate_Pulse_Width(angle);
	__HAL_TIM_SET_COMPARE(handle, channel, temp_d);
	//HAL_Delay(100);
}
