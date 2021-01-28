#pragma once

#include "Layout.h"
#include "Multiplexer.h"
#include "Defines.h"

/**
 * @brief Check if temperature sensors output a impossible temperature
 * @return fan type of unreadable temperature ~> ALL_FANS means all ok
 */
auto check_temperature(unsigned int (&buf)[ALL_FANS]) -> FanType
{
	if (const auto f = find_if(begin(buf), end(buf), [](unsigned int t) { return t <= MIN_TEMP; }); f != end(buf))
		return (FanType)(begin(buf) - f);

	return ALL_FANS;
}

/**
 * @brief Search for a component thats overheating
 * @return overheating component
 */
auto check_overheat(unsigned int (&buf)[ALL_FANS]) -> FanType
{
	if (const auto f =
			find_if(begin(buf), end(buf), [c = FAN_STATES[FULL]](unsigned int t) mutable { return t > *c++; });
		f != end(buf))
		return (FanType)(begin(buf) - f);

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
 * @brief Temperature change switch pauses
 */
static struct FanControl
{
	unsigned long time	 = 0;
	unsigned char was_in = OFF;
} g_fan_states[ALL_FANS];

/**
 * @brief Set the fan object
 *
 * @param pin pin of fan
 * @param val analog fan value
 */
void set_fan(FanType t, FanState s)
{
	g_fan_states[t].was_in = s;
	analogWrite(pin::LUEFTER[t], FAN_POWER[s]);
}

/**
 * @brief set all fans to a power
 * @param s Fan state
 */
void set_fans(FanState s)
{
	for (auto i = 0u; i < ALL_FANS; ++i) set_fan((FanType)i, s);
}

/**
 * @brief Initialize the fans
 */
void init_fans() { set_fans(OFF); }

/**
 * @brief Handle fan speed using temperature sensors
 */
void handle_fan_control(unsigned int (&buf)[ALL_FANS])
{
	for (auto f = 0u; f < ALL_FANS; ++f)
	{
		auto state = &g_fan_states[f];

		if (const auto t = millis(); state->time <= t)
			for (auto s = 0u; s < ALL_STATES; ++s)
			{
				const auto temp		= buf[f] <= FAN_STATES[s][f];
				const auto fanstate = state->was_in <= s;

				if (temp != fanstate)
				{
					SerialStream() << "i: " << f << " was: " << state->was_in << " temp: " << temp
								   << " fan: " << fanstate;

					state->time = t + SWITCH_LAG;
					state->was_in += fanstate ? 1 : -1;
					set_fan((FanType)f, (FanState)state->was_in);

					SerialStream() << "Now: " << state->was_in;

					break;
				}
			}
	}
}