/*
 * servo.h
 *
 *  Created on: Sep 11, 2024
 *      Author: mokhtar
 */

#ifndef SERVO_MOTOR_SERVO_H_
#define SERVO_MOTOR_SERVO_H_

/*section : includes */
#include "stander_file.h"
#include "time.h"
/*section : macro declarations  */


/*section : macro declaration functions  */

/*section : data type declarations  */

//@defgroup TIM_Channel TIM Channel
typedef enum {
	ch1 = TIM_CHANNEL_1,
	ch2 = TIM_CHANNEL_2,
	ch3 = TIM_CHANNEL_3,
	ch4 = TIM_CHANNEL_4
}TIM_CHANNEL_S;

typedef struct {
	TIM_HandleTypeDef *htim;     //timer use
	TIM_CHANNEL_S channel_select ; //channel select
}servo_t;
/*section : functions declarations  */
void servo_Motor_Start_angle_90 (servo_t *servo);
void servo_Motor_Start_angle_45 (servo_t *servo);
void servo_Motor_Start_angle_0  (servo_t *servo);
void servo_Motor_Start_angle_N45(servo_t *servo);
void servo_Motor_Start_angle_N90(servo_t *servo);
void servo_Motor_Recycler_from_n90_90(servo_t *servo);
void servo_Motor_Recycler_from_90_n90(servo_t *servo);
void servo_Motor_ADC_Control(servo_t *servo, uint32_t ADC_Value);
void servo_motor_stop(servo_t *servo);
#endif /* SERVO_MOTOR_SERVO_H_ */


// this drive use tim1 with prescaler 160 and reload value 2000 and channel one ch1
//So update it
