#pragma once

#include "Multiplexer.h"

// Range 1 (input_start till input_end) to Range 2 (output_start till output_end)
// output = output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start)
constexpr int map(int val, int temp_min, int temp_max, int volt_min, int volt_max)
{
	return volt_min + (volt_max - volt_min) / (temp_max - temp_min) * (val - temp_min);
}

// Contains information about each fan
struct Fan
{
	int pin,		// Pin connection
		temp_half;	// Point at which fan should go full speed (between 0 and 1023)
};

constexpr int temp_to_value(int temp)
{
	// return map(temp, )
	return 0;
}

// Tiefsetzer, Motor, Vorverstärker, BMS, Hochsetzer, Motor Treiber; index is multiplexer input port
static constexpr Fan LUEFTER[] = { 
	{ 3, temp_to_value(60) }, 
	{ 5, temp_to_value(60) }, 
	{ 6, temp_to_value(60) },
	{ 9, temp_to_value(60) },
	{ 11, temp_to_value(60) },
	{ 13, temp_to_value(60) }
};

// Discribes the fan type of the LUEFTER array
enum FanType
{
	TIEFSETZER, MOTOR, VORSTAEKER, BMS, HOCHSETZER, TREIBER
};

// Wenn System an ist ~> schalte Lüfter an.
// Lüfter werden in 3 Stuffen angeschaltet, Lüfter werden 0%, 50% und 100% getrieben
// Um ein und aus schalten zu vermeiden wird ein Temperatur Toleranz eingesetzt (Entweder hard coded oder custom Toleranz für jedes Element)
//  ~> Die Toleranz ist der Puffer die der Lüfter an sein muss oder aus sein muss bei der anfänglichen Grenze
// 

int part_val(int pin)
{
	constexpr int MAX_PINS_MULTI = 16;
	Mux* const m = pin < MAX_PINS_MULTI ? mux : mux + 1;
	return m->read(pin % MAX_PINS_MULTI);
}

int fan_val(int pin, int val)
{
	analogWrite(pin, val);
}