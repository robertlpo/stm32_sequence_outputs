/*
 * inputs.c
 *
 *  Created on: 9 gru 2017
 *      Author: r.lapucha
 */


#include "inputs.h"


int check_input(int id)
{
	int result = 0;

	if (inputs[id].input_type == ls)
	{
		if (HAL_GPIO_ReadPin(inputs[id].gpio_port, inputs[id].gpio_pin) == GPIO_PIN_RESET)
		{
			if (inputs[id].debounc_counter < inputs[id].debounc_time)
			{
				inputs[id].debounc_counter++;
				result = 0;
			}
			else

			if (inputs[id].debounc_counter == inputs[id].debounc_time)
			{
				inputs[id].debounc_counter++;
				result = 1;
			}
			else

			{
				result = 0;
			}

			inputs[id].inaktiv_counter = 0;
		}
		else

		{
			if (inputs[id].debounc_counter > 0)
			{
				if (inputs[id].inaktiv_counter++ >= inputs[id].debounc_time)
				{
					inputs[id].debounc_counter = 0;
					inputs[id].inaktiv_counter = 0;
				}
			}
		}
	}

	return result;
}
