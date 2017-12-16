/*
 * logik.h
 *
 *  Created on: 8 gru 2017
 *      Author: r.lapucha
 */

#ifndef LOGIK_H_
#define LOGIK_H_

#include "stm32f1xx_hal.h"


#define SECTIONS_AMOUNT				3
#define SIGNALS_PER_SECTION			4

#define INP_SEL0					0
#define INP_SEL1					1
#define INP_SEL2					2
#define INP_STOP					3
#define INPUTS_AMOUNT				4

#define REP_1						1
#define REP_2						2


typedef enum SignalType
{
	takt,
	pulse

} SignalType;


typedef enum SignalStatus
{
	disabled,
	enabled

} SignalStatus;


typedef struct SignalDefinition
{
	SignalType signal_type;
	GPIO_TypeDef* gpio_port;
	uint16_t gpio_pin;
	unsigned int time_on;
	unsigned int time_off;
	unsigned int time_counter;
	int repeats;
	int repeat_counter;
	SignalStatus status;

} SignalDefinition;


typedef struct InfoDefinition
{
	unsigned int time_on;
	unsigned int time_off;

} InfoDefinition;


SignalDefinition sections[SECTIONS_AMOUNT][SIGNALS_PER_SECTION];

InfoDefinition infos[INPUTS_AMOUNT];


void init_outputs_configuration(void);

void logik_main_loop(void);

void control_signals(void);

void control_inputs(void);

void disable_signals(void);

void enable_signals(int section);

void init_info_configuration(void);

void show_info(int info);

#endif /* LOGIK_H_ */
