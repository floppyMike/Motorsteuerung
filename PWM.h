#pragma once

static constexpr int PWM = 10;

// Defines common PWM control registers
template<typename OUT>
struct CustomPWM
{
	char* TCCRA, *TCCRB;
	OUT* OCRA, *OCRB;
};

using MicroPWM = CustomPWM<short>; // Arduino Micro PWM set
using UnoPWM = CustomPWM<char>; // Arduino Uno PWM set

static inline MicroPWM MOTOR_PWM = { &TCCR1A, &TCCR1B, &OCR1A, &OCR1B }; // Pins 10, 9

/*
auto analogget(int pin)
{
    switch (pin)
    {
        case 
    };
}
*/

void init_motor_PWM()
{
	pinMode(PWM, OUTPUT);

	// Setup PWM Timer
	*MOTOR_PWM.TCCRA = _BV(COM1A0) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);   // COM0A0 = Toggle OCR0A; COM0B1 = Use OCR0B; WGM## = Set PWM mode
	*MOTOR_PWM.TCCRB = _BV(WGM12) | _BV(CS11);                                // Vorteiler = 8
	*MOTOR_PWM.OCRA = 100;                                                    // (16MHz / f / Vorteiler = OCR0A; f -> 20kHz)
	*MOTOR_PWM.OCRB = 0;                                                      // 100 is 100% and 1 is 1%
}

void handle_motor_PWM_control(unsigned int gas_val)
{
	// Disable PWM at 0 or disable
	if (gas_val == 0 || disable)
		*MOTOR_PWM.TCCRB = _BV(WGM12);
	else
		*MOTOR_PWM.TCCRB = _BV(WGM12) | _BV(CS11);

	// Set PWM value
	*MOTOR_PWM.OCRB = gas_val;
}
