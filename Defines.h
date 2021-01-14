#pragma once

#define MEGA // Used for virtual test cases
//#define UNO //TODO
//#define MICRO // Real

/**
 * @brief Describes the fan types
 */
enum FanType
{
	TIEFSETZER,
	MOTOR,
	VORSTAEKER,
	BMS,
	HOCHSETZER,
	TREIBER,
	ALL_FANS
};

/**
 * @brief Describes the fan states
 */
enum FanState : unsigned char
{
	HALF,
	FULL,
	ALL_STATES
};

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

#if defined MEGA // ------------------------------------------------

/**
 * @brief Describes the border where the fans start going fuĺl power
 */
static constexpr int LUEFTER_HALF_POINT[ALL_FANS] = { 147, 147, 147, 147, 147, 147 };

/**
 * @brief Describes the point where things start getting critical (does nothing now). ~> Poweroff? Limit engine?
 */
static constexpr int LUEFTER_LIMIT[ALL_FANS] = { 200, 200, 200, 200, 200, 200 };

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

// -----------------------------------------------------------------------------
// Utility
// -----------------------------------------------------------------------------

/**
 * @brief Helper function for array begin
 * @param arr c array
 * @return array begin
 */
template<typename T>
constexpr auto begin(T *arr) noexcept -> T *
{
	return arr;
}

/**
 * @brief Helper function for array end
 * @param arr c array
 * @return array end
 */
template<typename T, unsigned int n>
constexpr auto end(T (&arr)[n]) noexcept -> T *
{
	return arr + n;
}

/**
 * @brief Map a area to another area
 *
 * @param val input value
 * @param input_min input value minimum range
 * @param input_max input value maximum range
 * @param output_min mapped value minimum range
 * @param output_max mapped value maximum range
 * @return mapped value
 */
constexpr int map(int val, int input_min, int input_max, int output_min, int output_max)
{
	return output_min + (output_max - output_min) / (input_max - input_min) * (val - input_min);
}