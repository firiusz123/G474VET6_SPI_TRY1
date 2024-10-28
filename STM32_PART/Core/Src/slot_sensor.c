#include "slot_sensor.h"

// Counter for slot sensor
static GPIO_PinState last_state = GPIO_PIN_RESET; // Last state of the sensor
int8_t counter = 0;

void SlotSensor_Init(int8_t side ) {
	counter = 0;
    // Initialize the last state
	if(side = 0)
	{
		last_state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
	}
	////// !!!!!!!!!!! need to establish whitch pin to use for the 2nd head
	else if (side == 1)
	{
		last_state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
	}

}

int SlotSensor_Update(int8_t side ) {

	if(side == 0 )
	{
		  GPIO_PinState current_state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); // Read pin state

		    // Check for a change in state
		    if (current_state == GPIO_PIN_SET && last_state == GPIO_PIN_RESET) {
		    	HAL_Delay(1);
		    	current_state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8);
		    	if(current_state == GPIO_PIN_SET){
		        counter++;} // Increment counter on state change
		         // Update last state
		    }
		    last_state = current_state;
		    return counter ;
	}
	else if(side =1)
	{
		GPIO_PinState current_state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8); // Read pin state

				    // Check for a change in state
		if (current_state == GPIO_PIN_SET && last_state == GPIO_PIN_RESET)
		{
			HAL_Delay(1);
	    	current_state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8);
	    	if(current_state == GPIO_PIN_SET){
	    		counter++;} // Increment counter on state change
	    	// Update last state
		}
		last_state = current_state;
		return counter ;

	}

}
