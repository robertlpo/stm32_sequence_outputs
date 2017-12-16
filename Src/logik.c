/*
 * logik.c
 *
 *  Created on: 8 gru 2017
 *      Author: r.lapucha
 */


#include "logik.h"
#include "inputs.h"


volatile int count1ms;

int current_info = INP_STOP;
int current_info_time_counter = 0;


/* Timer2 configuration: APB1 = 64MHz / (Prescaler 640) = 100kHz / (Period 100) = 1KHz (1ms) */


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2)
	{
		/* increment, rest in main */
		count1ms++;

	}
}



void init_outputs_configuration(void)
{
	sections[0][0].signal_type = takt;
	sections[0][0].gpio_port = S0O0_GPIO_Port;
	sections[0][0].gpio_pin = S0O0_Pin;
	sections[0][0].time_on = 1200;
	sections[0][0].time_off = 800;
	sections[0][0].time_counter = 0;

	sections[0][1].signal_type = takt;
	sections[0][1].gpio_port = S0O1_GPIO_Port;
	sections[0][1].gpio_pin = S0O1_Pin;
	sections[0][1].time_on = 150;
	sections[0][1].time_off = 350;
	sections[0][1].time_counter = 0;

	sections[0][2].signal_type = pulse;
	sections[0][2].gpio_port = S0O2_GPIO_Port;
	sections[0][2].gpio_pin = S0O2_Pin;
	sections[0][2].time_on = 5000;
	sections[0][2].time_off = 5000;
	sections[0][2].time_counter = 0;
	sections[0][2].repeats = REP_1;

	sections[0][3].signal_type = takt;
	sections[0][3].gpio_port = S0O3_GPIO_Port;
	sections[0][3].gpio_pin = S0O3_Pin;
	sections[0][3].time_on = 166;
	sections[0][3].time_off = 166;
	sections[0][3].time_counter = 0;

	sections[1][0].signal_type = takt;
	sections[1][0].gpio_port = S1O0_GPIO_Port;
	sections[1][0].gpio_pin = S1O0_Pin;
	sections[1][0].time_on = 1200;
	sections[1][0].time_off = 800;
	sections[1][0].time_counter = 0;

	sections[1][1].signal_type = takt;
	sections[1][1].gpio_port = S1O1_GPIO_Port;
	sections[1][1].gpio_pin = S1O1_Pin;
	sections[1][1].time_on = 150;
	sections[1][1].time_off = 350;
	sections[1][1].time_counter = 0;

	sections[1][2].signal_type = pulse;
	sections[1][2].gpio_port = S1O2_GPIO_Port;
	sections[1][2].gpio_pin = S1O2_Pin;
	sections[1][2].time_on = 5000;
	sections[1][2].time_off = 5000;
	sections[1][2].time_counter = 0;
	sections[1][2].repeats = REP_1;

	sections[1][3].signal_type = takt;
	sections[1][3].gpio_port = S1O3_GPIO_Port;
	sections[1][3].gpio_pin = S1O3_Pin;
	sections[1][3].time_on = 166;
	sections[1][3].time_off = 166;
	sections[1][3].time_counter = 0;

	sections[2][0].signal_type = takt;
	sections[2][0].gpio_port = S2O0_GPIO_Port;
	sections[2][0].gpio_pin = S2O0_Pin;
	sections[2][0].time_on = 1200;
	sections[2][0].time_off = 800;
	sections[2][0].time_counter = 0;

	sections[2][1].signal_type = takt;
	sections[2][1].gpio_port = S2O1_GPIO_Port;
	sections[2][1].gpio_pin = S2O1_Pin;
	sections[2][1].time_on = 150;
	sections[2][1].time_off = 350;
	sections[2][1].time_counter = 0;

	sections[2][2].signal_type = pulse;
	sections[2][2].gpio_port = S2O2_GPIO_Port;
	sections[2][2].gpio_pin = S2O2_Pin;
	sections[2][2].time_on = 5000;
	sections[2][2].time_off = 5000;
	sections[2][2].time_counter = 0;
	sections[2][2].repeats = REP_1;

	sections[2][3].signal_type = takt;
	sections[2][3].gpio_port = S2O3_GPIO_Port;
	sections[2][3].gpio_pin = S2O3_Pin;
	sections[2][3].time_on = 166;
	sections[2][3].time_off = 166;
	sections[2][3].time_counter = 0;
}



void init_inputs_configuration(void)
{
	inputs[INP_SEL0].input_type = ls;
	inputs[INP_SEL0].gpio_port = SEL0_GPIO_Port;
	inputs[INP_SEL0].gpio_pin = SEL0_Pin;
	inputs[INP_SEL0].debounc_time = 1000;
	inputs[INP_SEL0].debounc_counter = 0;

	inputs[INP_SEL1].input_type = ls;
	inputs[INP_SEL1].gpio_port = SEL1_GPIO_Port;
	inputs[INP_SEL1].gpio_pin = SEL1_Pin;
	inputs[INP_SEL1].debounc_time = 1000;
	inputs[INP_SEL1].debounc_counter = 0;

	inputs[INP_SEL2].input_type = ls;
	inputs[INP_SEL2].gpio_port = SEL2_GPIO_Port;
	inputs[INP_SEL2].gpio_pin = SEL2_Pin;
	inputs[INP_SEL2].debounc_time = 1000;
	inputs[INP_SEL2].debounc_counter = 0;

	inputs[INP_STOP].input_type = ls;
	inputs[INP_STOP].gpio_port = STOP_GPIO_Port;
	inputs[INP_STOP].gpio_pin = STOP_Pin;
	inputs[INP_STOP].debounc_time = 1000;
	inputs[INP_STOP].debounc_counter = 0;
}



void control_signals(void)
{
	for (int sect = 0; sect < SECTIONS_AMOUNT; sect++)
	{
		for (int sign = 0; sign < SIGNALS_PER_SECTION; sign++)
		{
			if (sections[sect][sign].status == enabled)
			{
				if (sections[sect][sign].signal_type == takt ||
				   (sections[sect][sign].signal_type == pulse && sections[sect][sign].repeat_counter < sections[sect][sign].repeats))
				{
					if (sections[sect][sign].time_counter >= 0 &&
						sections[sect][sign].time_counter <= sections[sect][sign].time_on)
					{
						HAL_GPIO_WritePin(sections[sect][sign].gpio_port, sections[sect][sign].gpio_pin, GPIO_PIN_SET);

						sections[sect][sign].time_counter++;
					}
					else

					if (sections[sect][sign].time_counter > sections[sect][sign].time_on &&
						sections[sect][sign].time_counter <= sections[sect][sign].time_on + sections[sect][sign].time_off)
					{
						HAL_GPIO_WritePin(sections[sect][sign].gpio_port, sections[sect][sign].gpio_pin, GPIO_PIN_RESET);

						sections[sect][sign].time_counter++;
					}
					else

					{
						sections[sect][sign].time_counter = 0;

						if (sections[sect][sign].signal_type == pulse)
						{
							sections[sect][sign].repeat_counter++;
						}
					}
				}
			}
		}
	}
}



void control_inputs(void)
{
	if (check_input(INP_STOP))
	{
		disable_signals();
		current_info = INP_STOP;
	}
	else

	if (check_input(INP_SEL0))
	{
		disable_signals();
		enable_signals(0);
		current_info = 0;
	}
	else

	if (check_input(INP_SEL1))
	{
		disable_signals();
		enable_signals(1);
		current_info = 1;
	}
	else

	if (check_input(INP_SEL2))
	{
		disable_signals();
		enable_signals(2);
		current_info = 2;
	}
}



void disable_signals(void)
{
	for (int sect = 0; sect < SECTIONS_AMOUNT; sect++)
	{
		for (int sign = 0; sign < SIGNALS_PER_SECTION; sign++)
		{
			sections[sect][sign].status = disabled;
			sections[sect][sign].time_counter = 0;
			sections[sect][sign].repeat_counter = 0;
			HAL_GPIO_WritePin(sections[sect][sign].gpio_port, sections[sect][sign].gpio_pin, 0);
		}
	}
}



void enable_signals(int section)
{
	for (int sign = 0; sign < SIGNALS_PER_SECTION; sign++)
	{
		sections[section][sign].status = enabled;
		sections[section][sign].time_counter = 0;
		sections[section][sign].repeat_counter = 0;
	}
}



void logik_main_loop(void)
{
	if (count1ms >= 1)										/* 1ms period */
	{
		count1ms = 0;

		control_signals();

		control_inputs();

		show_info(current_info);
	}
}



void init_info_configuration(void)
{
	infos[INP_SEL0].time_on = 300;
	infos[INP_SEL0].time_off = 300;

	infos[INP_SEL1].time_on = 600;
	infos[INP_SEL1].time_off = 600;

	infos[INP_SEL2].time_on = 900;
	infos[INP_SEL2].time_off = 900;

	infos[INP_STOP].time_on = 100;
	infos[INP_STOP].time_off = 100;
}



void show_info(int info)
{
	if (current_info_time_counter >= 0 &&
		current_info_time_counter <= infos[info].time_on)
	{
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		current_info_time_counter++;
	}
	else

	if (current_info_time_counter > infos[info].time_on &&
		current_info_time_counter <= infos[info].time_on + infos[info].time_off)
	{
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		current_info_time_counter++;
	}
	else

	{
		current_info_time_counter = 0;
	}

}



