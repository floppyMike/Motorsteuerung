#pragma once

#include "Multiplexer.h"

// Range 1 (input_start till input_end) to Range 2 (output_start till output_end)
// output = output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start)
constexpr int map(int val, int temp_min, int temp_max, int volt_min, int volt_max)
{
	return volt_min + (volt_max - volt_min) / (temp_max - temp_min) * (val - temp_min);
}

constexpr int temp_to_value(int temp)
{
	// return map(temp, )
	return 0;
}

// Contains information about each fan
struct Fan
{
	Fan(int f, int tp, int th)
		: fan_pin(f)
		, temp_pin(tp)
		, temp_half(th)
	{}

	int fan_pin;					// Fan pin connection
	int temp_pin;					// Pin to temperatur sensor (on Multiplexer)
	int temp_half;					// Point at which fan should go full speed (between 0 and 1023)

	unsigned long timeout = 0;		// Timepoint in milliseconds till fan can be switched again
	bool          prev_half = 0;	// Previous step it was on
};

// Discribes the fan type of the LUEFTER array
enum FanType
{
	TIEFSETZER, MOTOR, VORSTAEKER, BMS, HOCHSETZER, TREIBER, NOTHING
};

// Tiefsetzer, Motor, Vorverstärker, BMS, Hochsetzer, Motor Treiber; index is multiplexer input port
static inline Fan LUEFTER[] = { 
	{ 3, 0, 420 }, 
	{ 5, 1, temp_to_value(60) }, 
	{ 6, 2, temp_to_value(60) },
	{ 9, 3, temp_to_value(60) },
	{ 11, 4, temp_to_value(60) },
	{ 13, 5, temp_to_value(60) }
};

// Wenn System an ist ~> schalte Lüfter an.
// Lüfter werden in 3 Stuffen angeschaltet, Lüfter werden 0%, 80% und 100% getrieben
// Um ein und aus schalten zu vermeiden wird ein Temperatur Toleranz eingesetzt (Entweder hard coded oder custom Toleranz für jedes Element)
//  ~> Die Toleranz ist der Puffer die der Lüfter an sein muss oder aus sein muss bei der anfänglichen Grenze
// 

int part_val(int pin)
{
	constexpr int MAX_PINS_MULTI = 15 + 1;
	Mux* const m = pin < MAX_PINS_MULTI ? mux : mux + 1;
	return m->read(pin % MAX_PINS_MULTI);
}

int fan_val(int pin, int val)
{
	analogWrite(pin, val);
}

void init_fan_control()
{
	for (auto i = LUEFTER, end = LUEFTER + sizeof(LUEFTER) / sizeof(LUEFTER[0]); i < end; ++i)
		pinMode(i->fan_pin, OUTPUT);
}

void handle_fan_control()
{
	//for (FanType i = 0; i < FanType::NOTHING; ++i)
	for (auto i = LUEFTER, end = LUEFTER + sizeof(LUEFTER) / sizeof(LUEFTER[0]); i < end; ++i)
		if (i->timeout <= millis())
		{
			constexpr int HALF_RUN = map(9, 0, 12, 0, 255), FULL_RUN = 255;

			const auto temp_range = part_val(i->temp_pin); // Between 0 and 1023

			debug_message("Temperatur: ", temp_range);

			const bool prev_half = i->prev_half;
			const bool flag = temp_range < i->temp_half;

			if (prev_half == flag)
				continue;

			debug_message("Fan ", i - LUEFTER, (flag ? " lowered power." : " highered power."));

			i->prev_half = !i->prev_half;
			fan_val(i->fan_pin, flag ? HALF_RUN : FULL_RUN);

			i->timeout = millis() + 5000;
		}
}