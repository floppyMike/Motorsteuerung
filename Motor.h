#pragma once

#include "PWM.h"

/**
 * @brief Process motor change
 * @param gas_val value of the gas
 */
void handle_motor(unsigned short gas_val)
{
	//turn_PWM(gas_val != 0);
	set_PWM(gas_val);
}

/**
 * @brief Get the state of the gas
 * @return gas power
 */
auto gas_value() -> unsigned int
{
    return analogRead(pin::GAS);
}
