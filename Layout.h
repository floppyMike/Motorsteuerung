#pragma once

#include "Defines.h"

namespace pin
{
#if defined MICRO
	static constexpr int LUEFTER_TIEFSETZER = 3, LUEFTER_MOTOR = 5, LUEFTER_VORSTAERKER = 6, LUEFTER_BMS = 9,
						 LUEFTER_HOCHSETZER = 11, LUEFTER_MOTOR_TREIB = 13;

	static constexpr int PWM = 10;

	static constexpr int MUX_S0 = 0, MUX_S1 = 1, MUX_S2 = 2, MUX_S3 = 4, MUX_EN = 7;

	static constexpr int MUX_SIG1 = A0, MUX_SIG2 = A1;

	static constexpr int ZUND	 = 8;
	static constexpr int NOT_AUS = 12;

	static constexpr int GAS = A3;

#elif defined MEGA
	static constexpr int LUEFTER_TIEFSETZER = 2, LUEFTER_MOTOR = 3, LUEFTER_VORSTAERKER = 4, LUEFTER_BMS = 5,
						 LUEFTER_HOCHSETZER = 6, LUEFTER_MOTOR_TREIB = 7;

	static constexpr int PWM = 11;

	static constexpr int MUX_S0 = 14, MUX_S1 = 15, MUX_S2 = 16, MUX_S3 = 17, MUX_EN = 18;

	static constexpr int ZUND	 = 0;
	static constexpr int NOT_AUS = 1;

	static constexpr int MUX_SIG1 = A0, MUX_SIG2 = A1;

	static constexpr int GAS = A2;
#endif
} // namespace pin

void init_pins() noexcept
{
	pinMode(pin::LUEFTER_TIEFSETZER, OUTPUT);
	pinMode(pin::LUEFTER_MOTOR, OUTPUT);
	pinMode(pin::LUEFTER_VORSTAERKER, OUTPUT);
	pinMode(pin::LUEFTER_BMS, OUTPUT);
	pinMode(pin::LUEFTER_MOTOR_TREIB, OUTPUT);

	pinMode(pin::PWM, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(8, OUTPUT);

	pinMode(pin::MUX_S0, OUTPUT);
	pinMode(pin::MUX_S1, OUTPUT);
	pinMode(pin::MUX_S2, OUTPUT);
	pinMode(pin::MUX_S3, OUTPUT);
	pinMode(pin::MUX_EN, OUTPUT);

	pinMode(pin::ZUND, OUTPUT);
	pinMode(pin::NOT_AUS, OUTPUT);
}