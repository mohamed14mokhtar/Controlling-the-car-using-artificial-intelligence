/*
 * servo_cfg.c
 *
 *  Created on: Sep 11, 2024
 *      Author: mokhtar
 */

#include "servo_cfg.h"


servo_t servo = {
	.channel_select = ch1,
	.htim = &htim2
};

