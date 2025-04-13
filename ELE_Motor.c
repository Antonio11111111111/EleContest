/* This file is aimed at repackaging the ax Library. But as the TIM I/Os is not defined ,
 * the file is in the state: TODO */
/* Pose initialization function should be written and this work is better to be given to Wang Maoyao. */

/* 修改记录2025/3/27 0:15 OhzyMain
 * 1.简写了ELE_Motor_Steering_Machine_Init(void);
 * 2.略微改动ELE_Motor_Calculate_Pulse_Width(u16 angle)数据换算中的类型转换;
 * 3.修改了ELE_Motor_Steering_Machine_Moving(...)的参数, 增加了Motor控制引脚(PWM输出引脚)对应的TIM的句柄指针和通道, 已在ELE_Motor.h文件中宏定义;
 * 4.将main.h和tim.h放到ELE_Motor.h中引用*/

/* 修改记录2025/4/13 23:48 OhzyMain 半完成
 * 1.新增结构体姿势结构体ELE_Gesture_Typedef,基础动作结构体ELE_Move_Basic_Typedef(见.h文件);
 * 2.封装运动到某一姿势的姿势函数void ELE_Motor_Gesture(ELE_Gesture_Typedef* gesture);
 * 3.封装了基础动作运动函数void ELE_Motor_Basic_Move(ELE_Move_Basic_Typedef* movement),相当于对定态姿势运动Key帧
 * */
#include "ELE_Motor.h"

// Steering Machine initialize
void ELE_Motor_Steering_Machine_Init(void){
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

// Calculate the pulse width with the target angle
u16 ELE_Motor_Calculate_Pulse_Width(u16 angle){
	//Ensure the angle is between 0 and 180
	if (angle > 180){angle = 180;}
	if (angle < 0){angle = 0;}
	u16 pulseWidth = (u16)(50 + (fp)(angle) * 200 / 180);
	return pulseWidth;
}
// Steering Machine move at a particular angle
void ELE_Motor_Steering_Machine_Moving(TIM_HandleTypeDef *handle, u32 channel, u16 angle){
	u16 temp_d = ELE_Motor_Calculate_Pulse_Width(angle);
	__HAL_TIM_SET_COMPARE(handle, channel, temp_d);
}

//八个舵机摆到特定姿势
void ELE_Motor_Gesture(ELE_Gesture_Typedef* gesture){
	ELE_Motor_Steering_Machine_Moving(ELE_MotorLF1_TIM, ELE_MotorLF1_CHANNEL, gesture -> lf1);
	ELE_Motor_Steering_Machine_Moving(ELE_MotorLF2_TIM, ELE_MotorLF2_CHANNEL, gesture -> lf2);
	ELE_Motor_Steering_Machine_Moving(ELE_MotorLB1_TIM, ELE_MotorLB1_CHANNEL, gesture -> lb1);
	ELE_Motor_Steering_Machine_Moving(ELE_MotorLB2_TIM, ELE_MotorLB2_CHANNEL, gesture -> lb2);
	ELE_Motor_Steering_Machine_Moving(ELE_MotorRF1_TIM, ELE_MotorRF1_CHANNEL, gesture -> rf1);
	ELE_Motor_Steering_Machine_Moving(ELE_MotorRF2_TIM, ELE_MotorRF2_CHANNEL, gesture -> rf2);
	ELE_Motor_Steering_Machine_Moving(ELE_MotorRB1_TIM, ELE_MotorRB1_CHANNEL, gesture -> rb1);
	ELE_Motor_Steering_Machine_Moving(ELE_MotorRB2_TIM, ELE_MotorRB2_CHANNEL, gesture -> rb2);
};

//简单动作(动作即姿势-时间序列)
void ELE_Motor_Basic_Move(ELE_Move_Basic_Typedef* movement){
	u8 i;
	u8 time;		//最好用定时器方案取代-需要全局变量
	for(i = 0, time = 0; i < (movement->Gesture_Num); i++){
		while(time <= (movement->Times)[i]){
			HAL_Delay(100);
			time++;
		}
	}
}
