/*
 * inputs.h
 *
 *  Created on: 9 gru 2017
 *      Author: r.lapucha
 */

#ifndef INPUTS_H_
#define INPUTS_H_

#include "stm32f1xx_hal.h"


#define INP_AMOUNT					4


typedef enum InputType
{
	hs,
	ls
} InputType;


typedef struct InputDefinition
{
	InputType input_type;
	GPIO_TypeDef* gpio_port;
	uint16_t gpio_pin;
	unsigned int debounc_time;
	unsigned int debounc_counter;
	unsigned int inaktiv_counter;

} InputDefinition;


InputDefinition inputs[INP_AMOUNT];


void init_inputs_configuration(void);

int check_input(int id);


#endif /* INPUTS_H_ */
