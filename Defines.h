#pragma once

#include "Layout.h"

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

/**
 * @brief Names the individual components
 */
static constexpr const char *COMP_DESC[ALL_FANS] = {
	"Tiefsetzer", "Motor", "Vorverstaerker", "BMS", "Hochversetzer", "Motor Treiber"
}; // TODO: Not all components require a fan

#if defined MEGA // ------------------------------------------------

/**
 * @brief Describes the borders where the fans start switching to another power. The last row of values describe the
 * critical limit
 */
static constexpr int FAN_STATES[ALL_STATES][ALL_FANS] = {
	{ 50, 50, 50, 50, 50, 50 }, { 147, 147, 147, 147, 147, 147 }, { 200, 200, 200, 200, 200, 200 }
}; // TODO: Measure appropiate values

/**
 * @brief Power the fan states
 */
static constexpr unsigned int FAN_POWER[ALL_STATES] = { 0, 127, 255 };

#endif // ------------------------------------------------

/**
 * @brief Lag between switching fan states in milliseconds
 */
static constexpr unsigned long SWITCH_LAG = 5000;

/**
 * @brief Charge of battery
 */
static constexpr unsigned int MIN_CHARGE = 0; // TODO: measure and select minium power charge

/**
 * @brief Temperature border till interpreted as "not available"
 */
static constexpr unsigned int MIN_TEMP = 0; // TODO: measure minium temperature allowed till "not available"