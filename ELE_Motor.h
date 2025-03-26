//
// Created by Administrator on 2025/3/25.
//

/* 修改记录2025/3/27 00:03 OhzyMain
 * 1.宏定义了每个Motor控制引脚(PWM输出引脚)对应的TIM的句柄指针和通道. 如ELE_MotorX对应的分别是ELE_MotorX_TIM, ELE_MotorX_CHANNEL;
 * 2.将main.h和tim.h放到此处引用*/

#ifndef ELECONTEST_STM32_ELE_MOTOR_H
#define ELECONTEST_STM32_ELE_MOTOR_H
#include "ELE_glbDef.h"
#include "main.h"
#include "tim.h"

// MotorLF1 表示 Motor Left Forward 1,舵机左前方上关节
// MotorRB2 表示 Motor Right Backward 1,舵机右后方下关节
#define ELE_MotorLF1_TIM htim1
#define ELE_MotorLF1_CHANNEL TIM_CHANNEL_1
#define ELE_MotorLF2_TIM htim1
#define ELE_MotorLF2_CHANNEL TIM_CHANNEL_2
#define ELE_MotorLB1_TIM htim1
#define ELE_MotorLB1_CHANNEL TIM_CHANNEL_3
#define ELE_MotorLB2_TIM htim1
#define ELE_MotorLB2_CHANNEL TIM_CHANNEL_4
#define ELE_MotorRF1_TIM &htim3
#define ELE_MotorRF1_CHANNEL TIM_CHANNEL_2
#define ELE_MotorRF2_TIM htim3
#define ELE_MotorRF2_CHANNEL TIM_CHANNEL_1
#define ELE_MotorRB1_TIM htim3
#define ELE_MotorRB1_CHANNEL TIM_CHANNEL_4
#define ELE_MotorRB2_TIM htim3
#define ELE_MotorRB2_CHANNEL TIM_CHANNEL_3


void ELE_Motor_Steering_Machine_Init(void);
u16 ELE_Motor_Calculate_Pulse_Width(u16 angle);
void ELE_Motor_Steering_Machine_Moving(TIM_HandleTypeDef *handle, u32 channel, u16 angle);


#endif //ELECONTEST_STM32_ELE_MOTOR_H
