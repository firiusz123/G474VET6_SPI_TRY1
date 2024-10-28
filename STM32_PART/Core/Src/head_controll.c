#include <string.h>
#include "head_controll.h"


#define RX_BUFFER_SIZE 32 // Define an appropriate size for your buffer



char* head_control1(void) {
    static char RxBuffer[RX_BUFFER_SIZE];
    memset(RxBuffer, '\0', sizeof(RxBuffer)); // Clear the buffer

    char received_char;
    int8_t index = 0;

    uint8_t timeout = 1000;
    uint32_t start_time = HAL_GetTick();

    // Continue to receive characters until the character '$' is found
    while (1) {
        // Receive one character at a time
        if (HAL_UART_Receive(&huart4, (uint8_t*)&received_char, 1, HAL_MAX_DELAY) == HAL_OK) {
            // Skip adding to buffer if the received character is '\0'
            if (received_char == '\0') {
                continue;
            }
            HAL_Delay(1);
            RxBuffer[index++] = received_char;
            start_time = HAL_GetTick();

            // Break the loop if the end of the buffer is reached or if '$' is received
            if (index >= RX_BUFFER_SIZE || received_char == '$' || HAL_GetTick() - start_time > timeout)

            {
            	return "Error";


            }

        }
    }

    // Null-terminate the string
    RxBuffer[index] = '\0';

    return RxBuffer;
}
