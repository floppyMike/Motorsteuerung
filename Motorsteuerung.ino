// #define NDEBUG // Uncomment this if release version

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

#ifndef NDEBUG
	print_temps(temps);
#endif

	// Do checks
	if (bool bat = !check_battery(c), temp = check_temperature(temps) != ALL_FANS; bat || temp)
	{
		if (bat)
			SerialStream() << "Battery needs charging.";

		if (temp)
			SerialStream() << "Temperature sensor(s) not working correctly.";

		kill();
		return;
	}

	// Do jobs
	switch (g_prog_state)
	{
	case RUNNING: running(temps, pot); break;
	case COOLING: cooling(temps); break;
	}

#ifndef NDEBUG
	delay(1000);
#endif
}

// -----------------------------------------------------------------------------
// Common state handlers
// -----------------------------------------------------------------------------

void print_temps(unsigned int (&temps)[ALL_FANS])
{
	SerialStream() << "Temperatures:";
	for (auto i = 0u; i < ALL_FANS; ++i) Log() << '\t' << COMP_DESC[i] << ": " << temps[i] << '\n';
}

// -----------------------------------------------------------------------------
// Running state handlers
// -----------------------------------------------------------------------------

void start_running()
{
	StatusStream _s("Enabling motor");

	init_motor();
	g_prog_state = RUNNING;
}

void running(unsigned int (&temps)[ALL_FANS], unsigned int pot)
{
	// Additional checks
	if (auto comp = check_overheat(temps); comp != ALL_FANS)
	{
		SerialStream() << COMP_DESC[comp] << " is overheating";

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
	StatusStream _s("Starting cooling procedure");

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
	StatusStream _s("Shutting down");

	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	cli();
	sleep_enable();
	sei();
	sleep_cpu();
	sleep_disable();
	sei();
}
