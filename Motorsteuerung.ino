#include "DebugStream.h"
#include "Layout.h"
#include "PWM.h"
#include "Multiplexer.h"
#include "FanControl.h"
#include "Battery.h"
#include "Motor.h"

static enum State { RUNNING, COOLING } g_prog_state;

// -----------------------------------------------------------------------------
// Main Arduino Loop
// -----------------------------------------------------------------------------

void setup()
{
	Serial.begin(9600);

	init_pins();
	init_fans();

	start_running();
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

// -----------------------------------------------------------------------------
// Running state handlers
// -----------------------------------------------------------------------------

void start_running()
{
	SerialStream() << "Motor enabled.";
	init_motor();
	g_prog_state = RUNNING;
}

void running()
{
	// Get inputs
	const auto c   = charge();
	const auto pot = gas_value();

	unsigned int temps[ALL_FANS];
	temperatures(temps);

	// Do reporting
	for (auto i = 0u; i < ALL_FANS; ++i) SerialStream() << COMP_DESC[i] << ": " << temps[i];

	// Do checks
	if (!check_battery(c) || check_temperature(temps) != ALL_FANS)
    {
		kill();
        return;
    }

	if (check_overheat(temps) != ALL_FANS)
    {
		cool_down();
        return;
    }

	// Do jobs
	handle_motor(pot);
	handle_fan_control(temps);
}

// -----------------------------------------------------------------------------
// Cooling state banners
// -----------------------------------------------------------------------------

void cool_down()
{
	SerialStream() << "Too Hot! Cooling down...";

	set_fans(FULL);
	set_PWM(0);

	g_prog_state = COOLING;
}

void cooling()
{
	unsigned int temps[ALL_FANS];
	temperatures(temps);

	if (check_overheat(temps) == ALL_FANS)
		start_running();
}

// -----------------------------------------------------------------------------
// Kill handler
// -----------------------------------------------------------------------------

void kill() {}