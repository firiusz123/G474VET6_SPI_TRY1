/*
 * call_center.h
 *
 *  Created on: Jul 25, 2024
 *      Author: mateu
 */

#ifndef INC_CALL_CENTER_H_
#define INC_CALL_CENTER_H_

#include "main.h"
extern SPI_HandleTypeDef hspi1; // Extern declaration
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;

void SPI_Communication(void);


#endif /* INC_CALL_CENTER_H_ */
