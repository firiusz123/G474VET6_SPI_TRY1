#include "motor_control.h"
#include "main.h"
#include "slot_sensor.h"

extern TIM_HandleTypeDef htim1; // Assuming htim1 is your timer handle
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim3;

extern int8_t TileONA;
extern int8_t TileONB;

extern int8_t posABS_HeadA;
extern int8_t posABS_HeadB;

uint8_t pinstate1=1;

#define MOTOR_SPEED_TILE_ON 250
#define MOTOR_SPEED_TILE_OFF 115

void Motor_Init(int8_t side) {
// !!!! CHANGE THE &htim and channels according to the connection schematics
	  if(side == 0)
	  {
		  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
		  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
		  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
	  }
	  else if(side ==1)
	  {
		  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
		  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	  }
    // Initialize motor control here (if any initialization is needed)
}

void Motor_Steer(int8_t side, int8_t target)
{	SlotSensor_Init(side);
	Motor_Init(side);
	int8_t count = 0 ;
	int16_t Motorspeed;


	if(side == 0)
	{

		if(TileONA)
		{

			Motorspeed = MOTOR_SPEED_TILE_ON - 1 ;
			if(target > 0)
			{

				while(count < target)
				{	  count = SlotSensor_Update(side);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Motorspeed);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
				}
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);

			}
			else if(target< 0)
			{
				while(count < -target)
						{	  count = SlotSensor_Update(side);
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
			if(target > 0){
						while(count < target)
						{
							count = SlotSensor_Update(side);
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
					count = SlotSensor_Update(side);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Motorspeed);
				}
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
			}

		}
	}
	else if(side == 1 )
	{
		if(TileONB)
				{

					Motorspeed = MOTOR_SPEED_TILE_ON - 1 ;
					if(target > 0)
					{

						while(count < target)
						{	  count = SlotSensor_Update(side);
							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Motorspeed);
							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
						}
							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);

					}
					else if(target< 0)
					{
						while(count < -target)
								{	  count = SlotSensor_Update(side);
									__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
									__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, Motorspeed);
								}
									__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
									__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
					}

				}
				else
				{

					Motorspeed = MOTOR_SPEED_TILE_OFF -1 ;
					if(target > 0){
								while(count < target)
								{
									count = SlotSensor_Update(side);
									__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Motorspeed);
									__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
								}

							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
							}
					else if(target< 0)
					{
						while(count < -target)
						{
							count = SlotSensor_Update(side);
							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, Motorspeed);
						}
							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
					}

				}
	}
}

void RotateHead(int8_t target_position)
{




}
int8_t ABSRotateHead(int8_t side , int8_t target_position)
{
	if(side == 0 )
	{
		Motor_Init(side);

		GPIO_PinState current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); // Read pin state
		GPIO_PinState last_state1=current_state1;
		if(current_state1==GPIO_PIN_RESET){
			while (current_state1 == last_state1){
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,0);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 100);
				current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
			}

			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);

		}
		HAL_Delay(200);
		int8_t absolute_target_position = target_position*5 - posABS_HeadA;
		SlotSensor_Init(side);
		Motor_Init(side);
		int8_t count = 0 ;
		int16_t Motorspeed;



			if(TileONA)
			{
				Motorspeed = MOTOR_SPEED_TILE_ON - 1 ;
				if(absolute_target_position > 0)
				{
					if (absolute_target_position-count==5){
											if(target_position==1){
											Motorspeed = 220;}
											else if(target_position==2){
												Motorspeed=215;
											}
											else if (target_position==3){
												Motorspeed=215;
											}
										}
										else if (absolute_target_position-count==10){
											if (target_position==2){
											Motorspeed=250;}
											else if(target_position==3){
												Motorspeed=250;
											}
										}
										else if (absolute_target_position-count==15){
											Motorspeed=258;
										}

					while(count < absolute_target_position)
					{	  count = SlotSensor_Update(side);
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Motorspeed);
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
					}

					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
					HAL_Delay(200);
					GPIO_PinState current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); // Read pin state
					GPIO_PinState last_state1=current_state1;
					if(current_state1==GPIO_PIN_RESET){
							while (current_state1 == last_state1){
									__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,0 );
									__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 100);
									current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
									}

						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);

				}
				}
				else if(absolute_target_position< 0)
				{
					if (absolute_target_position-count==-5){
							if(target_position==0){
								Motorspeed = 220;}
							else if(target_position==1){
									Motorspeed=210;
									}
							else if (target_position==2){
									Motorspeed=210;
									}
									}
					else if (absolute_target_position-count==-10){
							if (target_position==0){
								Motorspeed=255;}
							else if(target_position==1){
										Motorspeed=258;
															}
														}
							else if (absolute_target_position-count==-15){
									Motorspeed=255;
							}

					while(count < -absolute_target_position)
							{	  count = SlotSensor_Update(side);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Motorspeed);
							}

					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
					HAL_Delay(200);
					GPIO_PinState current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); // Read pin state
					GPIO_PinState last_state1=current_state1;
					if(current_state1==GPIO_PIN_RESET){
							while (current_state1 == last_state1){
									__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,100 );
									__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
									current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
									}


								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
				}
				}

			}
			else
			{

				Motorspeed = MOTOR_SPEED_TILE_OFF -1 ;
				if(absolute_target_position > 0){
						if (absolute_target_position-count==5){
							if(target_position==1){
							Motorspeed = 120;}
							else if(target_position==2){
								Motorspeed=145;
							}
							else if (target_position==3){
								Motorspeed=145;
							}
						}
						else if (absolute_target_position-count==10){
							if (target_position==2){
							Motorspeed=115;}
							else if(target_position==3){
								Motorspeed=170;
							}
						}
						else if (absolute_target_position-count==15){
							Motorspeed=180;
						}
							while(count < absolute_target_position)
							{
								count = SlotSensor_Update(side);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Motorspeed);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
							}

						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
						HAL_Delay(200);

						GPIO_PinState current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); // Read pin state
						GPIO_PinState last_state1=current_state1;
						if(current_state1==GPIO_PIN_RESET){
							while (current_state1 == last_state1){
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,0 );
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 100);
								current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);

						}
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);

						}
						}
				else if(absolute_target_position< 0)
				{
					if (absolute_target_position-count==-5){
											if(target_position==0){
											Motorspeed = 131;}
											else if(target_position==1){
												Motorspeed=131;
											}
											else if (target_position==2){
												Motorspeed=129;
											}
										}
										else if (absolute_target_position-count==-10){
											if (target_position==0){
											Motorspeed=195;}
											else if(target_position==1){
												Motorspeed=180;
											}
										}
										else if (absolute_target_position-count==-15){
											Motorspeed=210;
										}

					while(count < -absolute_target_position)
					{
						count = SlotSensor_Update(side);
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, Motorspeed);
					}

						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
						HAL_Delay(200);
						GPIO_PinState current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); // Read pin state
						GPIO_PinState last_state1=current_state1;
						if(current_state1==GPIO_PIN_RESET){
								while (current_state1 == last_state1){
										__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,100 );
										__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
										current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
										}
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
					}


				}

			}

				//Motor_Steer(absolute_target_position);
				if(target_position*5 != posABS_HeadA){posABS_HeadA = target_position*5;}
				else{HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);}
			return 1;
	}


	else if(side == 1)
	{

		Motor_Init(side);

				GPIO_PinState current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); // Read pin state
				GPIO_PinState last_state1=current_state1;
				if(current_state1==GPIO_PIN_RESET){
					while (current_state1 == last_state1){
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,0);
						__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 100);
						current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
					}

					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);

				}
				HAL_Delay(200);
				int8_t absolute_target_position = target_position*5 - posABS_HeadB;
				SlotSensor_Init(side);
				Motor_Init(side);
				int8_t count = 0 ;
				int16_t Motorspeed;



					if(TileONA)
					{
						Motorspeed = MOTOR_SPEED_TILE_ON - 1 ;
						if(absolute_target_position > 0)
						{
							if (absolute_target_position-count==5){
													if(target_position==1){
													Motorspeed = 220;}
													else if(target_position==2){
														Motorspeed=215;
													}
													else if (target_position==3){
														Motorspeed=215;
													}
												}
												else if (absolute_target_position-count==10){
													if (target_position==2){
													Motorspeed=250;}
													else if(target_position==3){
														Motorspeed=250;
													}
												}
												else if (absolute_target_position-count==15){
													Motorspeed=258;
												}

							while(count < absolute_target_position)
							{	  count = SlotSensor_Update(side);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Motorspeed);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
							}

							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
							HAL_Delay(200);
							GPIO_PinState current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); // Read pin state
							GPIO_PinState last_state1=current_state1;
							if(current_state1==GPIO_PIN_RESET){
									while (current_state1 == last_state1){
											__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,0 );
											__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 100);
											current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
											}

								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);

						}
						}
						else if(absolute_target_position< 0)
						{
							if (absolute_target_position-count==-5){
									if(target_position==0){
										Motorspeed = 220;}
									else if(target_position==1){
											Motorspeed=210;
											}
									else if (target_position==2){
											Motorspeed=210;
											}
											}
							else if (absolute_target_position-count==-10){
									if (target_position==0){
										Motorspeed=255;}
									else if(target_position==1){
												Motorspeed=258;
																	}
																}
									else if (absolute_target_position-count==-15){
											Motorspeed=255;
									}

							while(count < -absolute_target_position)
									{	  count = SlotSensor_Update(side);
										__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
										__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, Motorspeed);
									}

							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
							__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
							HAL_Delay(200);
							GPIO_PinState current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); // Read pin state
							GPIO_PinState last_state1=current_state1;
							if(current_state1==GPIO_PIN_RESET){
									while (current_state1 == last_state1){
											__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,100 );
											__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
											current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
											}


										__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
										__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
						}
						}

					}
					else
					{

						Motorspeed = MOTOR_SPEED_TILE_OFF -1 ;
						if(absolute_target_position > 0){
								if (absolute_target_position-count==5){
									if(target_position==1){
									Motorspeed = 120;}
									else if(target_position==2){
										Motorspeed=145;
									}
									else if (target_position==3){
										Motorspeed=145;
									}
								}
								else if (absolute_target_position-count==10){
									if (target_position==2){
									Motorspeed=115;}
									else if(target_position==3){
										Motorspeed=170;
									}
								}
								else if (absolute_target_position-count==15){
									Motorspeed=180;
								}
									while(count < absolute_target_position)
									{
										count = SlotSensor_Update(side);
										__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Motorspeed);
										__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
									}

								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
								HAL_Delay(200);

								GPIO_PinState current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); // Read pin state
								GPIO_PinState last_state1=current_state1;
								if(current_state1==GPIO_PIN_RESET){
									while (current_state1 == last_state1){
										__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,0 );
										__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 100);
										current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);

								}
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);

								}
								}
						else if(absolute_target_position< 0)
						{
							if (absolute_target_position-count==-5){
													if(target_position==0){
													Motorspeed = 131;}
													else if(target_position==1){
														Motorspeed=131;
													}
													else if (target_position==2){
														Motorspeed=129;
													}
												}
												else if (absolute_target_position-count==-10){
													if (target_position==0){
													Motorspeed=195;}
													else if(target_position==1){
														Motorspeed=180;
													}
												}
												else if (absolute_target_position-count==-15){
													Motorspeed=210;
												}

							while(count < -absolute_target_position)
							{
								count = SlotSensor_Update(side);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, Motorspeed);
							}

								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
								__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
								HAL_Delay(200);
								GPIO_PinState current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7); // Read pin state
								GPIO_PinState last_state1=current_state1;
								if(current_state1==GPIO_PIN_RESET){
										while (current_state1 == last_state1){
												__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,100 );
												__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
												current_state1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
												}
										__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
										__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
							}


						}

					}

						//Motor_Steer(absolute_target_position);
						if(target_position*5 != posABS_HeadB){posABS_HeadB = target_position*5;}
						else{HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);}
					return 1;

	}


}
void HeadBase(int8_t side)
{

	if(side == 0)
	{

		int16_t BaseSpeed = 250;
		Motor_Init(side);
		//uint8_t pinstate1;
		pinstate1 = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8);

		while(pinstate1)
		{
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, BaseSpeed-1);

			pinstate1 = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8);
			 if (pinstate1==0){
				 HAL_Delay(200);
				 pinstate1 = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8);
			 }

		}

		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
		HAL_Delay(2000);
		Motor_Steer(side,3);
		posABS_HeadA=0;
	}
	else if(side == 1)
	{
		int16_t BaseSpeed = 250;
				Motor_Init(side);
				//uint8_t pinstate1;
				pinstate1 = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8);

				while(pinstate1)
				{
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, BaseSpeed-1);

					pinstate1 = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8);
					 if (pinstate1==0){
						 HAL_Delay(200);
						 pinstate1 = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8);
					 }

				}

				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
				HAL_Delay(2000);
				Motor_Steer(side,3);
				posABS_HeadB=0;
	}

}






