#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "stm32g4xx_hal.h"

void Motor_Init(void);
void Motor_Steer(int8_t target);
void RotateHead(int8_t target);
int8_t ABSRotateHead(int8_t target_position);
void HeadBase(void);
void HeadAdjust(int16_t speed)

#endif
