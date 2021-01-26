#pragma once

#include "Layout.h"

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

#if defined MEGA // ------------------------------------------------

/**
 * @brief Describes the border where the fans start going fuĺl power
 */
static constexpr int FAN_HALF_POINT[ALL_FANS] = { 147, 147, 147, 147, 147, 147 };

/**
 * @brief Describes the point where things start getting critical (does nothing now). ~> Poweroff? Limit engine?
 */
static constexpr int FAN_LIMIT[ALL_FANS] = { 200, 200, 200, 200, 200, 200 };

/**
 * @brief Power of HALF and FULL fan states
 */
static constexpr unsigned int FAN_POWER[ALL_STATES] = { 0, 255 };

#elif defined MICRO // ------------------------------------------------

static constexpr int LUEFTER_LIMIT[] = {};

#endif // ------------------------------------------------

/**
 * @brief Lag between switching fan states in milliseconds
 */
static constexpr unsigned long SWITCH_LAG = 5000;
