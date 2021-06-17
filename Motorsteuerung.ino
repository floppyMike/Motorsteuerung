#include "DebugStream.h"
#include "Layout.h"
#include "PWM.h"
#include "Multiplexer.h"
#include "FanControl.h"
#include "Battery.h"
#include "Motor.h"

#include <avr/sleep.h>

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

	// Do jobs
	switch (g_prog_state)
	{
	case RUNNING: running(temps, pot); break;
	case COOLING: cooling(temps); break;
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

void running(unsigned int (&temps)[ALL_FANS], unsigned int pot)
{
	// Additional checks
	if (check_overheat(temps) != ALL_FANS)
	{
		cool_down();
		return;
	}

	// Tasks
	handle_motor(pot);
	handle_fan_control(temps);
}

// -----------------------------------------------------------------------------
// Cooling state handlers
// -----------------------------------------------------------------------------

void cool_down()
{
	SerialStream() << "Too Hot! Cooling down...";

	set_fans(FULL);
	set_PWM(0);

	g_prog_state = COOLING;
}

void cooling(unsigned int (&temps)[ALL_FANS])
{
	if (check_overheat(temps) == ALL_FANS)
		start_running();
}

// -----------------------------------------------------------------------------
// Kill handler
// -----------------------------------------------------------------------------

void kill() // TODO: Test with live arduino.
{
    SerialStream() << "Something went wrong! Going to sleep...";

	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	cli();
	sleep_enable();
	sei();
	sleep_cpu();
    sleep_disable();
    sei();
}
