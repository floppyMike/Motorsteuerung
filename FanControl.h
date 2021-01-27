#pragma once

#include "Layout.h"
#include "Multiplexer.h"
#include "Defines.h"

// Wenn System an ist ~> schalte Lüfter an.
// Lüfter werden in 3 Stuffen angeschaltet, Lüfter werden 0%, 75% und 100% getrieben
// Um ein und aus schalten zu vermeiden wird ein Temperatur Toleranz eingesetzt
//  ~> Die Toleranz ist der Puffer die der Lüfter an sein muss oder aus sein muss bei der anfänglichen Grenze

/**
 * @brief Check if temperature sensors output a impossible temperature
 * @return fan type of temperature ~> ALL_FANS means all ok
 */
auto check_temperature(unsigned int (&buf)[ALL_FANS]) -> FanType
{
	for (auto i = begin(buf), e = end(buf); i != e; ++i)
		if (*i <= MIN_TEMP)
			return (FanType)(begin(buf) - i);

	return ALL_FANS;
}

/**
 * @brief Read the temperatures
 * @param buf array buffer for temperatures
 */
void temperatures(unsigned int (&buf)[ALL_FANS])
{
	for (auto i = 0u; i < ALL_FANS; ++i) buf[i] = mux_val(i);
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
	for (auto i = begin(pin::LUEFTER), e = end(pin::LUEFTER); i != e; ++i) set_fan(*i, FAN_POWER[OFF]);
}

/**
 * @brief Temperature change switch pauses
 */
struct FanControl
{
	unsigned long time	 = 0;
	unsigned char was_in = OFF;
};

/**
 * @brief Handle fan speed using temperature sensors
 */
void handle_fan_control(unsigned int (&buf)[ALL_FANS])
{
	static FanControl states[ALL_FANS];

	for (auto f = 0u; f < ALL_FANS; ++f)
	{
		auto state = &states[f];

		if (const auto t = millis(); state->time <= t)
		{
			for (auto s = 0u; s < ALL_STATES; ++s)
			{
				const auto temp		= buf[f] <= FAN_STATES[s][f];
				const auto fanstate = state->was_in <= s;

				if (temp != fanstate)
				{
					SerialStream() << "Was: " << state->was_in << " temp: " << temp << " fan: " << fanstate;

					state->time = t + SWITCH_LAG;
					state->was_in += fanstate ? 1 : -1;
					set_fan(pin::LUEFTER[f], FAN_POWER[state->was_in]);

					SerialStream() << "Now: " << state->was_in;

					break;
				}
			}
		}
	}
}