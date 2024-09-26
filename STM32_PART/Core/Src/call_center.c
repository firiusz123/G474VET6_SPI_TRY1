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
//#include "head_controll.h"

#define RX_BUFFER_SIZE 32
#define TX_BUFFER_SIZE 32
#define MAX_BUFFER_SIZE 32
#define END_OF_MESSAGE '$'

char RxBuffer[RX_BUFFER_SIZE]={0};
char TxBuffer[TX_BUFFER_SIZE] = {0};
char RxBuffer1[RX_BUFFER_SIZE]={0};
char TxBuffer1[TX_BUFFER_SIZE] = "pAng$";

int8_t posABS = 0;
int8_t TileON = 0;


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
char* head_control(void) {
    //char RxBuffer1[RX_BUFFER_SIZE];
    //memset(RxBuffer1, '\0', sizeof(RxBuffer1)); // Clear the buffer

    char received_char1;
    int8_t index = 0;
    memset(RxBuffer1, '\0', sizeof(RxBuffer1));
    // Continue to receive characters until the character '$' is found
    while (1) {
        // Receive one character at a time
    	if (HAL_UART_Receive(&huart5, (uint8_t*)&received_char1, 1, 1000) == HAL_OK) {
        //if (HAL_UART_Receive(&huart5, (uint8_t*)&received_char1, 1, HAL_MAX_DELAY) == HAL_OK) {
        //if (HAL_UART_Receive(&huart5, (uint8_t*)received_char1, 1, HAL_MAX_DELAY) == HAL_OK) {
            // Skip adding to buffer if the received character is '\0'
    		if (received_char1=='H'){
    			RxBuffer1[index++] = received_char1;
    			while(1){
    				if (HAL_UART_Receive(&huart5, (uint8_t*)&received_char1, 1, 1000) == HAL_OK) {


    						if (received_char1 == '\0') {
    							continue;
    						}

    						RxBuffer1[index++] = received_char1;
            //HAL_Delay(1);
            // Break the loop if the end of the buffer is reached or if '$' is received
    						if (index >= RX_BUFFER_SIZE || received_char1 == '$') {
    							break;
    						}
    					}
    				}
    			}
    		if (index >= RX_BUFFER_SIZE || received_char1 == '$') {
    		    							break;
    		    						}
    		}
    		}




    // Null-terminate the string
    RxBuffer1[index] = '\0';

    return RxBuffer1;
}

char* swtch_control(void){ //odbiór stanów czujników obrotu kafelka

		memset(RxBuffer1, '\0', sizeof(RxBuffer1)); // Clear the buffer

	    char received_char2;
	    int8_t index = 0;

	    // Continue to receive characters until the character '$' is found
	    while (1) {
	            // Receive one character at a time
	        	if (HAL_UART_Receive(&huart5, (uint8_t*)&received_char2, 1, 1000) == HAL_OK) {

	        		// Skip adding to buffer if the received character is '\0'
	                if (received_char2 == '\0') {
	                    continue;
	                }

	                RxBuffer1[index++] = received_char2;
	                //HAL_Delay(1);
	                // Break the loop if the end of the buffer is reached or if '$' is received
	                if (index >= RX_BUFFER_SIZE || received_char2 == '$') {
	                    break;

	                }
	            }
	    }
	        // Null-terminate the string
	        RxBuffer1[index] = '\0';

	        return RxBuffer1;
}
char* gaps_control(void){ //odbiór stanów czujników szczelinowych w odkręcaczach

		memset(RxBuffer1, '\0', sizeof(RxBuffer1)); // Clear the buffer

	    char received_char2;
	    int8_t index = 0;

	    // Continue to receive characters until the character '$' is found
	    while (1) {
	            // Receive one character at a time
	        	if (HAL_UART_Receive(&huart5, (uint8_t*)&received_char2, 1, 1000) == HAL_OK) {

	        		// Skip adding to buffer if the received character is '\0'
	                if (received_char2 == '\0') {
	                    continue;
	                }

	                RxBuffer1[index++] = received_char2;
	                //HAL_Delay(1);
	                // Break the loop if the end of the buffer is reached or if '$' is received
	                if (index >= RX_BUFFER_SIZE || received_char2 == '$') {
	                    break;

	                }
	            }
	    }
	        // Null-terminate the string
	        RxBuffer1[index] = '\0';

	        return RxBuffer1;
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////
            	else if(strcmp(command, "HEAD") == 0)
            	{

            		HAL_UART_Transmit(&huart5, (uint8_t *)RxBuffer, strlen(RxBuffer), HAL_MAX_DELAY);
            		HAL_Delay(1);
            		char* received_data = head_control();
            		char* str;
            		memset(TxBuffer, '\0', sizeof(TxBuffer));
            		if(strcmp(received_data, "HEAD#0#F0F0F0F0$") == 0 ){str = "HEAD#0#NOK$";}
            		else if(strcmp(received_data, "HEAD#1#F0F0F0F0$") == 0 ) {str = "HEAD#1#NOK$";}
            		else if (received_data[5]=='0'){str = "HEAD#0#OK$";}
            		else if (received_data[5]=='1'){str="HEAD#1#OK$";}

            		printf("%s\n",str);
            		strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            		memset(RxBuffer, '\0', sizeof(RxBuffer));


            	 }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
            	else if(strcmp(command, "MAGNET") == 0)
            	{


            		int8_t MagState;

            		HAL_UART_Transmit(&huart5, (uint8_t *)RxBuffer, strlen(RxBuffer), HAL_MAX_DELAY);
            		memset(TxBuffer, '\0', sizeof(TxBuffer));
					sscanf(RxBuffer, "MAGNET#%d$", &MagState);
					if(MagState != 0){TileON = 1 ;}
					else{TileON = 0 ;}
					//power=char(MagState);
					if(MagState==0){
						char *str = "MAGNET#0#OK$";
						HAL_Delay(200);
						strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
					}
					else if(MagState==4){
						char *str = "MAGNET#4#OK$";
						HAL_Delay(200);
	            		strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);

					}
					//char *str = "MAGNET#4#OK$";
					//HAL_Delay(200);
					//strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            		//HAL_Delay(200);

            		memset(RxBuffer, '\0', sizeof(RxBuffer));
            	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
            	else if(strcmp(command,"ROT")==0)
            	{
            		    int number;
            		    sscanf(RxBuffer, "ROT#%d$", &number);
            		    Motor_Steer(number);
            		memset(TxBuffer, '\0', sizeof(TxBuffer));
            		char *str = "ROT#OK$";
            		strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            		memset(RxBuffer, '\0', sizeof(RxBuffer));
            	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
            	else if(strcmp(command,"AROT")==0)
            	{

            		 int number;
            		 sscanf(RxBuffer, "AROT#%d$", &number);


            		 ABSRotateHead(number);
            		 //char number1=number;
            		 memset(TxBuffer, '\0', sizeof(TxBuffer));
            		 //if ()
            		 if (number== 1){
            		 	 char *str = "AROT#1#OK$";
            		 	 strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            		 }
            		 else if (number==0){
            			 char *str = "AROT#0#OK$";
            			 strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            		 }
            		 else if (number==2){
            		 	 char *str = "AROT#2#OK$";
            		 	 strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            		 }
            		 else if (number==3){
            		 	 char *str = "AROT#3#OK$";
            		 	 strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            		 }
            		// strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            		 memset(RxBuffer, '\0', sizeof(RxBuffer));
            	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
            	else if(strcmp(command,"TILEBASE")==0) //bazowanie obortu kafelka
            	{
            		HeadBase();

            		memset(TxBuffer, '\0', sizeof(TxBuffer));
            		GPIO_PinState current_state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); // Read pin state
            		if (current_state == GPIO_PIN_SET){
            			char* str = "TILEBASE#OK$";
            			strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            		}
            		else if (current_state == GPIO_PIN_RESET){
            			char* str = "TILEBASE#NOK$";
            			strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            		}
            		//strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            		memset(RxBuffer, '\0', sizeof(RxBuffer));
            	}
////////////////////////////////////////////////////////////////////////////////////////////////////////
            	else if(strcmp(command,"SWTCH")==0) //Wysyłka stanu obrotu czujnika 0-wcisniety, 1-pusty
            	{
            		HAL_UART_Transmit(&huart5, (uint8_t *)RxBuffer, strlen(RxBuffer), HAL_MAX_DELAY);
            		//HAL_Delay(1);
            		char* received_data = swtch_control();
            		char* str;
            		memset(TxBuffer, '\0', sizeof(TxBuffer));
            		if((strcmp(received_data, "S#0000$")==0)){str = "SWTCH#0#0#0#0$";}
            		else if ((strcmp(received_data, "S#1000$")==0)){str = "SWTCH#1#0#0#0$";}
            		else if ((strcmp(received_data, "S#0100$")==0)){str = "SWTCH#0#1#0#0$";}
            		else if ((strcmp(received_data, "S#0010$")==0)){str = "SWTCH#0#0#1#0$";}
            		else if ((strcmp(received_data, "S#0001$")==0)){str = "SWTCH#0#0#0#1$";}
            		else{str="SWTCH#ERR$";}

            		strncpy(TxBuffer, str, sizeof(TxBuffer) - 1);
            		memset(RxBuffer, '\0', sizeof(RxBuffer));

            	}
            	////////////////////////////////////////////////////////////////////////////////////////////////////////
            	else if(strcmp(command,"GAPS")==0) //Wysyłka stanu obrotu czujnika 0-wcisniety, 1-pusty
            	{
            		HAL_UART_Transmit(&huart5, (uint8_t *)RxBuffer, strlen(RxBuffer), HAL_MAX_DELAY);
            		//HAL_Delay(1);
            		char* received_data = gaps_control();
            		char output[11];
            		sprintf(output,"G#%c#%c#%c#%c$",received_data[2],received_data[3],received_data[4],received_data[5] );
            		printf("%s\n", output);
            		memset(TxBuffer, '\0', sizeof(TxBuffer));

            		strncpy(TxBuffer, output, sizeof(TxBuffer) - 1);
            		memset(RxBuffer, '\0', sizeof(RxBuffer));

            	}

                HAL_SPI_Transmit(&hspi1, (uint8_t *)TxBuffer, strlen(TxBuffer), HAL_MAX_DELAY);
            	//HAL_SPI_Transmit_IT(&hspi1, (uint8_t *)TxBuffer, strlen(TxBuffer));
                index = 0; // Reset buffer index
                //memset(TxBuffer, '\0', sizeof(TxBuffer));
                free(command);
                command = NULL;
        }

        // Update pin state
        pinstate = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);

    }
    }
}


