/*
 * servo.c
 *
 *  Created on: Sep 11, 2024
 *      Author: mokhtar
 */


#include "servo.h"

uint32_t l_value;

void servo_Motor_Start_angle_90 (servo_t *servo){
	//TIM2->CCR1 = 200;
	switch (servo->channel_select){
	case ch1:
		servo->htim->Instance->CCR1 = 200;
		break;
	case ch2:
		servo->htim->Instance->CCR2 = 200;
		break;
	case ch3:
		servo->htim->Instance->CCR3 = 200;
		break;
	case ch4:
		servo->htim->Instance->CCR4 = 200;
		break;
	}

	HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
}

void servo_Motor_Start_angle_45 (servo_t *servo){
	switch (servo->channel_select){
		case ch1:
			servo->htim->Instance->CCR1 = 175;
			break;
		case ch2:
			servo->htim->Instance->CCR2 = 175;
			break;
		case ch3:
			servo->htim->Instance->CCR3 = 175;
			break;
		case ch4:
			servo->htim->Instance->CCR4 = 175;
			break;
		}
	HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
}

void servo_Motor_Start_angle_0  (servo_t *servo){
	switch (servo->channel_select){
		case ch1:
			servo->htim->Instance->CCR1 = 150;
			break;
		case ch2:
			servo->htim->Instance->CCR2 = 150;
			break;
		case ch3:
			servo->htim->Instance->CCR3 = 150;
			break;
		case ch4:
			servo->htim->Instance->CCR4 = 150;
			break;
		}
	HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
}

void servo_Motor_Start_angle_N45(servo_t *servo){
	switch (servo->channel_select){
		case ch1:
			servo->htim->Instance->CCR1 = 125;
			break;
		case ch2:
			servo->htim->Instance->CCR2 = 125;
			break;
		case ch3:
			servo->htim->Instance->CCR3 = 125;
			break;
		case ch4:
			servo->htim->Instance->CCR4 = 125;
			break;
		}
	HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
}

void servo_Motor_Start_angle_N90(servo_t *servo){
	switch (servo->channel_select){
		case ch1:
			servo->htim->Instance->CCR1 = 100;
			break;
		case ch2:
			servo->htim->Instance->CCR2 = 100;
			break;
		case ch3:
			servo->htim->Instance->CCR3 = 100;
			break;
		case ch4:
			servo->htim->Instance->CCR4 = 100;
			break;
		}
	HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
}

void servo_Motor_Recycler_from_n90_90(servo_t *servo){

	uint8_t counter = 100;
	switch (servo->channel_select){
			case ch1:
				while (counter <= 200){
						servo->htim->Instance->CCR1 = counter++;
						HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
						HAL_Delay(20);
					}
				break;
			case ch2:
				while (counter <= 200){
						servo->htim->Instance->CCR2 = counter++;
						HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
						HAL_Delay(20);
					}
				break;
			case ch3:
				while (counter <= 200){
						servo->htim->Instance->CCR3 = counter++;
						HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
						HAL_Delay(20);
					}
				break;
			case ch4:
				while (counter <= 200){
						servo->htim->Instance->CCR4 = counter++;
						HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
						HAL_Delay(20);
					}
				break;
			}
}

void servo_Motor_Recycler_from_90_n90(servo_t *servo){
	uint8_t counter = 200;
	switch (servo->channel_select){
		case ch1:
			while (counter >= 100){
					servo->htim->Instance->CCR1 = counter--;
					HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
					HAL_Delay(20);
				}
			break;
		case ch2:
			while (counter >= 100){
					servo->htim->Instance->CCR2 = counter--;
					HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
					HAL_Delay(20);
				}
			break;
		case ch3:
			while (counter >= 100){
					servo->htim->Instance->CCR3 = counter--;
					HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
					HAL_Delay(20);
				}
			break;
		case ch4:
			while (counter >= 100){
					servo->htim->Instance->CCR4 = counter--;
					HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
					HAL_Delay(20);
				}
			break;
		}
}

void servo_motor_stop(servo_t *servo){
	HAL_TIM_PWM_Stop(servo->htim, servo->channel_select);
}

void servo_Motor_ADC_Control(servo_t *servo, uint32_t ADC_Value){
	l_value = ADC_Value + 100;
	switch (servo->channel_select){
			case ch1:
				servo->htim->Instance->CCR1 = l_value;
				break;
			case ch2:
				servo->htim->Instance->CCR2 = l_value;
				break;
			case ch3:
				servo->htim->Instance->CCR3 = l_value;
				break;
			case ch4:
				servo->htim->Instance->CCR4 = l_value;
				break;
			}
		HAL_TIM_PWM_Start(servo->htim, servo->channel_select);
}
