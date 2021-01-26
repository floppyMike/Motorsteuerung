#pragma once

#include "Layout.h"
#include "Multiplexer.h"

/**
 * @brief Check if enough power is available
 * @return if battery has enough power
 */
auto check_battery(unsigned int charge) -> bool { return charge <= MIN_CHARGE; }

/**
 * @brief Get the battery charge
 * @return battery charge
 */
auto charge() -> unsigned int { return mux_val(pin::BMS_LADESTAND); }