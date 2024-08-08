/*
 * call_center.c
 *
 *  Created on: Jul 25, 2024
 *      Author: firiusz
 */
#include "call_center.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "slot_sensor.h"
#include "motor_control.h"

#define RX_BUFFER_SIZE 32
#define TX_BUFFER_SIZE 32
#define MAX_BUFFER_SIZE 32
#define END_OF_MESSAGE '$'

char RxBuffer[RX_BUFFER_SIZE]={0};
char TxBuffer[TX_BUFFER_SIZE] = "pAng$";

int8_t posABS = 0;


char* command_checker(uint8_t* buffer)
{
    int8_t ending_condition = 1;
    int8_t index = 0;

    while (ending_condition)
    {
        if (buffer[index] == '#')
        {
            ending_condition = 0;
        }
        else
        {
            index++;
        }

    }

    // Allocate memory for the command string with an extra byte for the null terminator
    char* command = (char*)malloc(index + 1);
    if (command == NULL)
    {
        return NULL;  // Allocation failed
    }

    // Copy the command part from buffer to the newly allocated string
    strncpy(command, (char*)buffer, index);
    command[index] = '\0';  // Null-terminate the string

    return command;
}

char* Uart_getter(void)
{
	int8_t ending_condition = 1 ;
	uint8_t recieved_letter ;
	int8_t index ;
	char* charbuffer = (char*)malloc(32);
	while(ending_condition)
	{
		HAL_UART_Receive(&huart4, &recieved_letter, 1,1000);
		charbuffer[index]=(char)recieved_letter;
		if((char)recieved_letter =='$'){ending_condition = 0 ;}
		else{index++;}
		if(index > 32-1){ending_condition = 0;}


	}

	return charbuffer;





}
void SPI_Communication(void)
{
    int8_t index = 0;
    uint8_t receivedData;
    uint8_t pinstate = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);


    if (!pinstate) {memset(RxBuffer, 0, sizeof(RxBuffer));}

    while (!pinstate) {
        // Receive data from SPI
        HAL_SPI_Receive(&hspi1, &receivedData, 1, HAL_MAX_DELAY);

        // Check for buffer overflow
        if (index < MAX_BUFFER_SIZE)
        {
            // Store received data in buffer
            RxBuffer[index++] = (char)receivedData;

            // Check if end of message
            if ((char)receivedData == END_OF_MESSAGE)
            {
            	char* command = command_checker(RxBuffer);
            	if(command == NULL){command = "MEM#ERR";}

            	else if(strcmp(command, "HEAD") == 0)
            	{
            		HAL_UART_Transmit(&huart5, (uint8_t *)RxBuffer, index, HAL_MAX_DELAY);
            		memset(TxBuffer, '\0', sizeof(TxBuffer));
            		command = Uart_getter();

            		strncpy(TxBuffer, command, sizeof(TxBuffer) - 1);
            		free(command);

            	}
            	else if(strcmp(command, "MAGNET") == 0)
            	{

            		HAL_UART_Transmit(&huart5, (uint8_t *)RxBuffer, strlen(RxBuffer), HAL_MAX_DELAY);
            		memset(TxBuffer, '\0', sizeof(TxBuffer));
            		char *str = "MAG#OK$";
            		strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            	}


            	else if(strcmp(command,"ROT")==0)
            	{
            		    int number;
            		    sscanf(RxBuffer, "ROT#%d$", &number);
            		    Motor_Steer(number);
            		memset(TxBuffer, '\0', sizeof(TxBuffer));
            		char *str = "ROT#OK$";
            		strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            	}



            	else if(strcmp(command,"AROT")==0)
            	{
            		 int number;
            		 sscanf(RxBuffer, "AROT#%d$", &number);


            		 ABSRotateHead(number);

            		 memset(TxBuffer, '\0', sizeof(TxBuffer));
            		 char *str = "ROT#OK$";
            		 strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);



            	}

            	else if(strcmp(command,"TILEBASE")==0){HeadBase();}

            	free(command);
            	command = NULL;
                HAL_SPI_Transmit(&hspi1, (uint8_t *)TxBuffer, strlen(TxBuffer), HAL_MAX_DELAY);
                index = 0; // Reset buffer index

            }
        }

        // Update pin state
        pinstate = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);
    }
}
