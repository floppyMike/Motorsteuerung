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

	Serial.begin(9600);
}

void loop() 
{
	// Read Poti from pedal
	const unsigned int pot = analogRead(A5);

	// Monitor poti values
	Serial.print("OCR1B: "), Serial.print(pot), Serial.print('\n');

    Serial.print("Val0: "), Serial.print(mux[0].read(0)), Serial.print('\n');
    Serial.print("Val1: "), Serial.print(mux[1].read(0)), Serial.print('\n');
    Serial.print("Func: "), Serial.print(part_val(17)), Serial.print('\n');

    // Handlers
    handle_fan_control();
	
	delay(100);
}
