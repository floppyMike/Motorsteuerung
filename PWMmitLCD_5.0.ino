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
    pinMode(3, OUTPUT);

    // Initialize components
    init_motor_PWM();

    analogWrite(3, 255);

	Serial.begin(9600);
}

void loop() 
{
	// Read Poti from pedal
	const unsigned int pot = analogRead(A0);

	// Monitor poti values
	Serial.print("OCR1B: "), Serial.print(pot), Serial.print('\n');

    // Handlers
    handle_motor_PWM_control(pot);

/*
	// Poll all sensors for temperatur
	for (auto i = 0u, end = sizeof(LUEFTER) / sizeof(LUEFTER[0]); i < end; ++i)
	{
		const auto temp_range = part_val(LUEFTER[i]); // Between 0 and 1023
		const auto voltage_range = map(temp_range, 0, 1023, 0, 255);
		fan_val(i, voltage_range); // Between 0 and 255
	}
*/
	
	delay(100);
}
