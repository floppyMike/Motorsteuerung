#pragma once

#include "PWM.h"

/**
 * @brief Check if the motor is running actually running using the gas value
 *
 * @param gas gas value
 * @return All good
 */
auto check_motor(unsigned int gas) -> bool { return true; } // TODO: correlate rotation speed and torque

/**
 * @brief Process motor change
 * @param gas_val value of the gas
 */
void handle_motor(unsigned short gas_val)
{
	// turn_PWM(gas_val != 0);
	set_PWM(gas_val);
}

/**
 * @brief Initialize the motor
 */
void init_motor() { init_timer1_PWM(); }

/**
 * @brief Get the state of the gas
 * @return gas power
 */
auto gas_value() -> unsigned int { return analogRead(pin::GAS); }
