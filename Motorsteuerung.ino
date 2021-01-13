#include "DebugStream.h"
#include "Layout.h"
#include "PWM.h"
#include "Multiplexer.h"

static Multiplexer mux(pin::MUX_SIG2, pin::MUX_S0, pin::MUX_S1, pin::MUX_S2, pin::MUX_S3, pin::MUX_EN);

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
	const unsigned int val = mux.address({ 15 }).read();
	SerialStream() << "Potval: " << pot << " Muxval: " << val;

	handle_motor_PWM_control(pot);
	delay(1000);
}