/*
 * head_controll.h
 *
 *  Created on: Aug 12, 2024
 *      Author: mateu
 */

// head_control.h
#ifndef HEAD_CONTROL_H
#define HEAD_CONTROL_H



#include <stdint.h>
#include  "main.h"
#include "call_center.h"


extern UART_HandleTypeDef huart5; // Assuming huart5 is declared elsewhere
// Function declaration
char* head_control(void);

#endif // HEAD_CONTROL_H

