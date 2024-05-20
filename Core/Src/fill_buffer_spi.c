#include "main.h"
#include <string.h>

#define MAX_BUFFER_SIZE 100 // Corrected definition of MAX_BUFFER_SIZE

void filla_the_buffer(void)
{
    static char buffer[MAX_BUFFER_SIZE];
    static uint8_t RXindex = 0;

    // Read pin state
    uint8_t pinstate = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);

    if (!pinstate)
    {
        // Receive data from SPI
        uint8_t receivedData;
        HAL_SPI_Receive(&hspi1, &receivedData, 1, HAL_MAX_DELAY);

        // Store received data in buffer
        buffer[RXindex++] = (char)receivedData;

        // Check for end of message or buffer overflow
        if ((char)receivedData == '$' || RXindex >= MAX_BUFFER_SIZE)
        {
            // Null-terminate buffer
            buffer[RXindex] = '\0';

            // Process buffer if it contains "ping"
            if (strstr(buffer, "ping") != NULL)
            {
                // Toggle GPIO pin 3
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
            }

            // Reset buffer index
            RXindex = 0;
            memset(buffer, 0, sizeof(buffer));
        }
    }
}

