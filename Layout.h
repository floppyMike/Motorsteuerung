#pragma once

#include "Defines.h"
#include "Multiplexer.h"

// -----------------------------------------------------------------------------
// Pins
// -----------------------------------------------------------------------------

namespace pin
{
#if defined MICRO // ------------------------------------------------

	static constexpr int LUEFTER_TIEFSETZER = 3, LUEFTER_MOTOR = 5, LUEFTER_VORSTAERKER = 6, LUEFTER_BMS = 9,
						 LUEFTER_HOCHSETZER = 11, LUEFTER_MOTOR_TREIB = 13;

	static constexpr int PWM = 10;

	static constexpr int MUX_S0 = 0, MUX_S1 = 1, MUX_S2 = 2, MUX_S3 = 4, MUX_EN = 7;

	static constexpr int MUX_SIG1 = A0, MUX_SIG2 = A1;

	static constexpr int ZUND	 = 8;
	static constexpr int NOT_AUS = 12;

	static constexpr int GAS = A3;

#elif defined MEGA // ------------------------------------------------

	static constexpr int LUEFTER[ALL_FANS] = { 2, 3, 4, 5, 6, 7 };

	// Multiplexer row of pins "i" represents pin of fan so no need to define them manually

	static constexpr int PWM = 10;

	static constexpr int MUX_S0 = 14, MUX_S1 = 15, MUX_S2 = 16, MUX_S3 = 17, MUX_EN = 18;

	static constexpr int ZUND	 = 0;
	static constexpr int NOT_AUS = 1;

	static constexpr int MUX_SIG1 = A0, MUX_SIG2 = A1;

	static constexpr int GAS = A2;

#endif // ------------------------------------------------
} // namespace pin

/**
 * @brief Initilaze the IO of the pins
 */
void init_pins() noexcept
{
	for (auto l = begin(pin::LUEFTER), e = end(pin::LUEFTER); l != e; ++l) pinMode(*l, OUTPUT);

	pinMode(pin::PWM, OUTPUT);

	pinMode(pin::MUX_S0, OUTPUT);
	pinMode(pin::MUX_S1, OUTPUT);
	pinMode(pin::MUX_S2, OUTPUT);
	pinMode(pin::MUX_S3, OUTPUT);
	pinMode(pin::MUX_EN, OUTPUT);

	pinMode(pin::ZUND, OUTPUT);
	pinMode(pin::NOT_AUS, OUTPUT);
}

// -----------------------------------------------------------------------------
// Multiplexers
// -----------------------------------------------------------------------------

static Multiplexer mux1(pin::MUX_SIG1, pin::MUX_S0, pin::MUX_S1, pin::MUX_S2, pin::MUX_S3, pin::MUX_EN);
static Multiplexer mux2(pin::MUX_SIG2, pin::MUX_S0, pin::MUX_S1, pin::MUX_S2, pin::MUX_S3, pin::MUX_EN);