#include "DebugStream.h"
#include "Layout.h"
#include "PWM.h"
#include "Multiplexer.h"
#include "FanControl.h"
#include "Checks.h"
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
	if (check_battery() && check_temperature())
		kill();

	const auto pot = gas_value();

	SerialStream() << "Potval: " << pot;

	handle_motor(pot);
	handle_fan_control();
}

void cooling()
{
}

void kill()
{
}