#ifndef MAGNET_H
#define MAGNET_H

#include "main.h"

// Function to handle the MAGNET command and send a response
void handleMagnetCommand(const char *command);

// External UART handles
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;

#endif // MAGNET_H
