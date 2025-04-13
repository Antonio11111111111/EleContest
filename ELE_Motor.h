//
// Created by Administrator on 2025/3/25.
//

/* 修改记录2025/3/27 00:03 OhzyMain
 * 1.宏定义了每个Motor控制引脚(PWM输出引脚)对应的TIM的句柄指针和通道. 如ELE_MotorX对应的分别是ELE_MotorX_TIM, ELE_MotorX_CHANNEL;
 * 2.将main.h和tim.h放到此处引用*/

/* 修改记录2025/4/13 23:56 OhzyMain 半完成
 * 1.新增结构体姿势结构体ELE_Gesture_Typedef,基础动作结构体ELE_Move_Basic_Typedef;
 * */

#ifndef ELECONTEST_STM32_ELE_MOTOR_H
#define ELECONTEST_STM32_ELE_MOTOR_H
#include "ELE_glbDef.h"
#include "main.h"
#include "tim.h"

//姿势结构体 某一时刻8个舵机的角度
typedef struct{
	u8 lf1, lf2, lb1, lb2, rf1, rf2, rb1, rb2;
}ELE_Gesture_Typedef;

//基础动作结构体 支持0.1*256=25.6s Gesture_Num 最高20个姿势 Gesture_Num为总共需要的姿势数量
typedef struct{
	u8 Gesture_Num;
	ELE_Gesture_Typedef Gestures[20];
	u8 Times[20];
}ELE_Move_Basic_Typedef;

//动作组结构体 - 未完成
/*typedef struct{
	u8 num;
}ELE_Move_Group_Typedef;*/

// MotorLF1 表示 Motor Left Forward 1,舵机左前方上关节	MotorRB2 表示 Motor Right Backward 1,舵机右后方下关节
#define ELE_MotorLF1_TIM &htim1
#define ELE_MotorLF1_CHANNEL TIM_CHANNEL_1
#define ELE_MotorLF2_TIM &htim1
#define ELE_MotorLF2_CHANNEL TIM_CHANNEL_2
#define ELE_MotorLB1_TIM &htim1
#define ELE_MotorLB1_CHANNEL TIM_CHANNEL_3
#define ELE_MotorLB2_TIM &htim1
#define ELE_MotorLB2_CHANNEL TIM_CHANNEL_4
#define ELE_MotorRF1_TIM &htim3
#define ELE_MotorRF1_CHANNEL TIM_CHANNEL_2
#define ELE_MotorRF2_TIM &htim3
#define ELE_MotorRF2_CHANNEL TIM_CHANNEL_1
#define ELE_MotorRB1_TIM &htim3
#define ELE_MotorRB1_CHANNEL TIM_CHANNEL_4
#define ELE_MotorRB2_TIM &htim3
#define ELE_MotorRB2_CHANNEL TIM_CHANNEL_3

void ELE_Motor_Steering_Machine_Init(void);
u16 ELE_Motor_Calculate_Pulse_Width(u16 angle);
void ELE_Motor_Steering_Machine_Moving(TIM_HandleTypeDef *handle, u32 channel, u16 angle);
void ELE_Motor_Gesture(ELE_Gesture_Typedef* gesture);
void ELE_Motor_Basic_Move(ELE_Move_Basic_Typedef* movement);

#endif //ELECONTEST_STM32_ELE_MOTOR_H
