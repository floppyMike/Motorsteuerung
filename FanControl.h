#pragma once

#include "Layout.h"
#include "Multiplexer.h"
#include "Defines.h"

// Wenn System an ist ~> schalte Lüfter an.
// Lüfter werden in 3 Stuffen angeschaltet, Lüfter werden 0%, 75% und 100% getrieben
// Um ein und aus schalten zu vermeiden wird ein Temperatur Toleranz eingesetzt
//  ~> Die Toleranz ist der Puffer die der Lüfter an sein muss oder aus sein muss bei der anfänglichen Grenze

/**
 * @brief Reads a pin from the multiplexers
 *
 * @param mux_pin pin to read from BOTH multiplexers
 * @return read value
 */
auto temp_val(int mux_pin) -> int
{
	return (mux_pin <= Multiplexer::INPUTS ? &mux1 : &mux2)->address({ mux_pin % (Multiplexer::INPUTS + 1) }).read();
}

/**
 * @brief Set the fan object
 *
 * @param pin pin of fan
 * @param val analog fan value
 */
void set_fan(int pin, int val) { analogWrite(pin, val); }

/**
 * @brief Initialize fans
 */
void init_fan_control()
{
	for (auto i = begin(pin::LUEFTER), e = end(pin::LUEFTER); i != e; ++i) set_fan(*i, FAN_POWER[HALF]);
}

/**
 * @brief Temperature change switch pauses
 */
struct State
{
	unsigned long time	 = 0;
	FanState	  was_in = HALF;
};

/**
 * @brief Handle fan speed using temperature sensors
 */
void handle_fan_control()
{
	static State states[ALL_FANS];

	for (auto i = 0u; i < ALL_FANS; ++i)
	{
		auto state = &states[i];

		if (const auto t = millis(); state->time <= t)
		{
			const auto temperature = temp_val(i);
			SerialStream() << i << " temp val: " << temperature;

			const auto temp		= temperature > LUEFTER_HALF_POINT[i];
			const auto fanstate = state->was_in == FanState::FULL;

			if (fanstate != temp)
			{
				state->time	  = t + SWITCH_LAG;
				state->was_in = static_cast<FanState>(!state->was_in);
				SerialStream() << "New state: " << state->was_in;
				set_fan(pin::LUEFTER[i], FAN_POWER[state->was_in]);
			}
		}
	}
}