#include "DebugStream.h"
#include "Layout.h"
#include "PWM.h"
#include "Multiplexer.h"
#include "FanControl.h"
#include "Battery.h"
#include "Motor.h"

static enum State { RUNNING, COOLING } g_prog_state;

void setup()
{
	init_pins();
	init_motor_PWM();
	init_fan_control();

	Serial.begin(9600);
}

void loop()
{
	switch (g_prog_state)
	{
	case RUNNING: running(); break;
	case COOLING: cooling(); break;
	}

	delay(1000);
}

void running()
{
	const auto c   = charge();
	const auto pot = gas_value();

	unsigned int temps[ALL_FANS];
	temperatures(temps);

	if (check_battery(c) && check_temperature(temps))
		kill();

	handle_motor(pot);
	handle_fan_control(temps);
}

void cooling() {}

void kill() {}