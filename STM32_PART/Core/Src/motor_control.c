#include "motor_control.h"
#include "main.h"
#include "slot_sensor.h"

extern TIM_HandleTypeDef htim1; // Assuming htim1 is your timer handle
extern TIM_HandleTypeDef htim4;

extern int8_t posABS;
extern int8_t TileON;

#define MOTOR_SPEED_TILE_ON 250
#define MOTOR_SPEED_TILE_OFF 180

void Motor_Init(void) {
	  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
    // Initialize motor control here (if any initialization is needed)
}

void Motor_Steer(int8_t target)
{	SlotSensor_Init();
	Motor_Init();
	int8_t count = 0 ;
	int16_t Motorspeed;

	if(TileON)
	{

		Motorspeed = MOTOR_SPEED_TILE_ON - 1 ;
		if(target > 0)
		{

			while(count < target)
			{	  count = SlotSensor_Update();
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Motorspeed);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
			}
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);

		}
		else if(target< 0)
		{
			while(count < -target)
					{	  count = SlotSensor_Update();
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Motorspeed);
					}
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
		}

	}
	else
	{
		Motorspeed = MOTOR_SPEED_TILE_OFF -1 ;
		if(target > 0)
				{
					while(count < target)
					{
						count = SlotSensor_Update();
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Motorspeed);
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
					}

				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
				}
		else if(target< 0)
		{
			while(count < -target)
			{
				count = SlotSensor_Update();
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Motorspeed);
			}
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
		}

	}

}

void RotateHead(int8_t target_position)
{

	Motor_Steer(target_position);


}
int8_t ABSRotateHead(int8_t target_position)
{

	int8_t absolute_target_position = target_position*5 - posABS;

	Motor_Steer(absolute_target_position);
	if(target_position*5 != posABS){posABS = target_position*5;}
	else{HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);}
return 1;


}

void HeadAdjust(int16_t speed)
{
	GPIO_PinState current_state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); 
	GPIO_PinState last_state = current_state
		while(current_state == last_state)
		{
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Motorspeed);
		}

		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
			
		
}
void HeadBase(void)
{

	int16_t BaseSpeed = 150;
	Motor_Init();
	uint8_t pinstate1;
	pinstate1 = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8);

	while(pinstate1)
	{
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, BaseSpeed-1);

		pinstate1 = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8);

	}

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
	HAL_Delay(2000);
	Motor_Steer(3);

}






