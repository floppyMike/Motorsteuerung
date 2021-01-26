#pragma once

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
