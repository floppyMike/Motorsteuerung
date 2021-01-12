#pragma once

#include "Layout.h"

#if defined MEGA // ------------------------------------------------

void init_motor_PWM()
{
	//*m_TCCRA = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21)
	//| _BV(WGM20);	  // COM0A0 = Toggle OCR0A; COM0B1 = Use OCR0B; WGM## = Set PWM mode
	//*m_TCCRB = _BV(CS22); // Vorteiler = 8

	TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10); // (Fast-PWM) 16MHz / Vorteiler / (Bits + 1) ~> Frequenz;
													 // (Phase-Correct PWM) 16MHz / Vorteiler / Bits / 2 ~> Frequenz
	TCCR1B = _BV(CS00);								 // CS01 ~> 8 Vorteiler; CS00 ~> 1 Vorteiler
	OCR1A  = 0;										 // (val + 1) / 256 = % (Unused)
	OCR1B  = 100;									 // (val + 1) / 256 = %
}

void set_PWM(unsigned short v) { OCR1B = v; }

void turn_PWM(bool on)
{
	// Disable PWM at 0
	TCCR1B = !on ? _BV(WGM12) : _BV(WGM12) | _BV(CS11);
}

#elif defined MICRO // ------------------------------------------------

// void init_motor_PWM()
// {
// 	//*m_TCCRA = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21)
// 	//| _BV(WGM20);	  // COM0A0 = Toggle OCR0A; COM0B1 = Use OCR0B; WGM## = Set PWM mode
// 	//*m_TCCRB = _BV(CS22); // Vorteiler = 8

// 	TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21)
// 		| _BV(WGM20);	// (Fast-PWM) 16MHz / Vorteiler / (Bits + 1) ~> Frequenz;
// 						// (Phase-Correct PWM) 16MHz / Vorteiler / Bits / 2 ~> Frequenz
// 	TCCR2B = _BV(CS20); // CS01 ~> 8 Vorteiler; CS00 ~> 1 Vorteiler
// 	OCR2A  = 0;			// (val + 1) / 256 = % (Unused)
// 	OCR2B  = 100;		// (val + 1) / 256 = %
// }

// void set_PWM(unsigned short v) { OCR2B = v; }

#endif // ------------------------------------------------

void handle_motor_PWM_control(unsigned short gas_val)
{
	// Disable PWM at 0
	turn_PWM(gas_val != 0);

	// Set PWM value
	set_PWM(gas_val);
}
