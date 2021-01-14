#include "DebugStream.h"
#include "Layout.h"
#include "PWM.h"
#include "Multiplexer.h"
#include "FanControl.h"

void setup()
{
	init_pins();
	init_motor_PWM();
	init_fan_control();

	Serial.begin(9600);
}

void loop()
{
	// Read Poti from pedal
	const unsigned int pot	= analogRead(pin::GAS);

	SerialStream() << "Potval: " << pot;

	handle_motor_PWM_control(pot);
	handle_fan_control();

	delay(1000);
}