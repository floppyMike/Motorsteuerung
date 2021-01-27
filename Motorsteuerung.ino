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
	init_motor();
	init_fans();

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
    // Get inputs
	const auto c   = charge();
	const auto pot = gas_value();

	unsigned int temps[ALL_FANS];
	temperatures(temps);

    // Do checks
	if (!check_battery(c))
		kill();

    if (!check_temperature(temps))
    {
        SerialStream() << "Too Hot! Cooling down...";
        g_prog_state = COOLING;
    }

    // Do reporting
    for (auto i = 0u; i < ALL_FANS; ++i)
        SerialStream() << COMP_DESC[i] << ": " << temps[i];

    // Do jobs
	handle_motor(pot);
	handle_fan_control(temps);
}

void cooling()
{

}

void kill() {}