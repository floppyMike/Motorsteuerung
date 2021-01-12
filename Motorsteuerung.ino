#include "DebugStream.h"
#include "Layout.h"
#include "PWM.h"

void setup()
{
    init_pins();
	init_motor_PWM();
	Serial.begin(9600);
}

void loop()
{
	// Read Poti from pedal
	const unsigned int pot = analogRead(pin::GAS);
	SerialStream() << "Potval: " << pot;

	handle_motor_PWM_control(pot);
    delay(1000);
}