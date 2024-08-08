#include "slot_sensor.h"

// Counter for slot sensor
static GPIO_PinState last_state = GPIO_PIN_RESET; // Last state of the sensor
int8_t counter = 0;

void SlotSensor_Init(void) {
	counter = 0;
    // Initialize the last state
    last_state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);
}

int SlotSensor_Update(void) {
    GPIO_PinState current_state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4); // Read pin state

    // Check for a change in state
    if (current_state == GPIO_PIN_SET && last_state == GPIO_PIN_RESET) {
        counter++; // Increment counter on state change
         // Update last state
    }
    last_state = current_state;
    return counter ;
}
