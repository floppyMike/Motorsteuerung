#pragma once

#include "DebugStream.h"
#include "Utility.h"

#define MEGA
//#define UNO //TODO
//#define MICRO

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
	ALL_FANS,
    NO_FANS
};

/**
 * @brief Describes the fan states
 */
enum FanState : unsigned char
{
    OFF,
	HALF,
	FULL,
	ALL_STATES
};

// -----------------------------------------------------------------------------
// Pins
// -----------------------------------------------------------------------------

namespace pin
{
#if defined MICRO // ------------------------------------------------

	static constexpr int LUEFTER[ALL_FANS] = { 3, 5, 6, 9, 11, 13 };

	// Multiplexer row of pins "i" represents pin of fan so no need to define them manually

	static constexpr int PWM = 10;

	static constexpr int MUX_S0 = 0, MUX_S1 = 1, MUX_S2 = 2, MUX_S3 = 4, MUX_EN = 7;

	static constexpr int MUX_SIG1 = A0, MUX_SIG2 = A1;

	static constexpr int ZUND	 = 8;
	static constexpr int NOT_AUS = 12;

	static constexpr int GAS = A3;

#elif defined MEGA // ------------------------------------------------

	static constexpr int LUEFTER[ALL_FANS] = { 2, 3, 4, 5, 6, 7 };

	// Multiplexer row of pins "i" represents pin of temperature sensor so no need to define them manually.
	// The rest MUST be beyond ALL_FANS...
	static constexpr int BMS_LADESTAND	= ALL_FANS + 0;
	static constexpr int BMS_GES_STROM	= ALL_FANS + 1;
	static constexpr int BMS_GES_SPAN	= ALL_FANS + 2;
	static constexpr int MOTOR_DREHZAHL = ALL_FANS + 3;
	static constexpr int MOTOR_SPAN		= ALL_FANS + 4;
	static constexpr int MOTOR_DREHMOM	= ALL_FANS + 5;
	static constexpr int MOTOR_STROM	= ALL_FANS + 6;

	static constexpr int PWM = 10;

	static constexpr int MUX_S0 = 14, MUX_S1 = 15, MUX_S2 = 16, MUX_S3 = 17, MUX_EN = 18;

	static constexpr int ZUND	 = 0;
	static constexpr int NOT_AUS = 1;

	static constexpr int MUX_SIG1 = A1, MUX_SIG2 = A0;

	static constexpr int GAS = A2;

#endif // ------------------------------------------------
} // namespace pin

/**
 * @brief Initilaze the IO of the pins
 */
void init_pins() noexcept
{
	StatusStream _s("Setting up pins");

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

