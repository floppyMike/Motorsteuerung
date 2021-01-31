#pragma once

#include "Layout.h"

#if defined MEGA // ------------------------------------------------

/**
 * @brief Switch the PWM timer on or off
 * @param on State
 */
void turn_PWM(bool on) // TODO: Test using real Arduino
{
	TCCR1B = on ? TCCR1B | _BV(CS10) : TCCR1B & ~_BV(CS10);
}

/**
 * @brief Initialize motor PWM timer
 */
void init_timer1_PWM() // TODO: Test using Arduino Mega
{
	TCCR1A = _BV(COM1B1) | _BV(WGM11); // (Fast-PWM) 16MHz / Vorteiler / (Bits + 1) ~> Frequenz;
									   // (Phase-Correct PWM) 16MHz / Vorteiler / Bits / 2 ~> Frequenz
	TCCR1B = _BV(CS10) | _BV(WGM12);   // CSn1 ~> 8 Vorteiler; CSn0 ~> 1 Vorteiler
	OCR1A  = 0;						   // (val + 1) / 511 = % (Unused)
	OCR1B  = 100;					   // (val + 1) / 511 = %

    turn_PWM(true);
}

/**
 * @brief Change the motor PWM duty cycle
 * @param v
 */
void set_PWM(unsigned short v) { OCR1B = v; }

#endif // ------------------------------------------------
