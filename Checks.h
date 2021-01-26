#pragma once

#include "Layout.h"
#include "Multiplexer.h"

/**
 * @brief Check if enough power is available
 * @return if battery has enough power
 */
auto check_battery() -> bool { return mux_val(pin::BMS_LADESTAND) <= MIN_CHARGE; }

/**
 * @brief Check if temperature sensors output a impossible temperature
 * @return fan type of temperature ~> ALL_FANS means all ok
 */
auto check_temperature() -> FanType
{
	for (int temp = 0; temp < ALL_FANS; ++temp)
		if (mux_val(temp) <= MIN_TEMP)
			return (FanType)temp;

	return ALL_FANS;
}

/**
 * @brief Check if the motor is running actually running using the gas value
 *
 * @param gas gas value
 * @return All good
 */
auto check_motor(unsigned int gas) -> bool { return true; } // TODO: correlate rotation speed and torque
