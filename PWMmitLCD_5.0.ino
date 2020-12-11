// Requirements
//	- Fan control frequency > 20kHz
//  - Fans have 3 states
//      > Off when nothing is running
//      > Half on when temperature reaches certain temperatur ~> At least 80% on
//      > Full on when temperature is over half range ~> 100% on

// Importants
//	- Fan control is 0 till 255
//	- Temperature input is 0 till 1023

static constexpr int ZUND = 8;
static constexpr int NOT_AUS = 12;

static constexpr int GAS = A5;

bool disable = false;

#include "FanControl.h"
#include "PWM.h"

void setup() 
{
    // Initialize components
    init_motor_PWM();

	Serial.begin(9600);
}

void loop() 
{
	// Read Poti from pedal
	const unsigned int pot = analogRead(A5);

    // Handlers
    handle_fan_control();
    handle_motor_PWM_control(pot);
	
	delay(100);
}
