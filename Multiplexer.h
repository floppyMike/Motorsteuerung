#pragma once

#include "Layout.h"

struct Bit4
{
	unsigned char v : 4;
};

class Multiplexer
{
public:
	static constexpr unsigned int ADDRESS_PINS = 4;
	static constexpr unsigned int INPUTS	   = (1 << ADDRESS_PINS) - 1;

	Multiplexer(int z, int s0, int s1, int s2, int s3, int en)
		: m_z(z)
		, m_s{ s0, s1, s2, s3 }
		, m_en(en)
	{
		turn(true);
	}

	/**
	 * @brief Change the target pin that will be used for getting input from
	 * @param a Address of the pin (integer is possible)
	 */
	auto address(Bit4 a) const -> const Multiplexer &
	{
		for (unsigned int i = 0, e = sizeof(m_s) / sizeof(m_s[0]); i < e; ++i)
			digitalWrite(m_s[i], a.v & (1 << i) ? HIGH : LOW);

		return *this;
	}

	/**
	 * @brief Get analog input from the addressed pin
	 * @return analog input
	 */
	auto read() const noexcept -> int { return analogRead(m_z); }

	/**
	 * @brief Turn multiplexer on or off
	 * @param on state
	 */
	void turn(bool on) noexcept
	{
		m_enabled = on;
		digitalWrite(m_en, !m_enabled ? HIGH : LOW);
	}

	/**
	 * @brief Get state of multiplexer
	 * @return if is on
	 */
	auto is_on() const noexcept -> bool { return m_enabled; }

private:
	int m_z;
	int m_s[4];

	int	 m_en;
	bool m_enabled;
};

// -----------------------------------------------------------------------------
// Multiplexers
// -----------------------------------------------------------------------------

static Multiplexer mux1(pin::MUX_SIG1, pin::MUX_S0, pin::MUX_S1, pin::MUX_S2, pin::MUX_S3, pin::MUX_EN);
static Multiplexer mux2(pin::MUX_SIG2, pin::MUX_S0, pin::MUX_S1, pin::MUX_S2, pin::MUX_S3, pin::MUX_EN);

/**
 * @brief Reads a pin from the multiplexers
 *
 * @param mux_pin pin to read from BOTH multiplexers
 * @return read value
 */
auto mux_val(unsigned int mux_pin) -> int
{
	return (mux_pin <= Multiplexer::INPUTS ? &mux1 : &mux2)
		->address({ (unsigned char)(mux_pin % (Multiplexer::INPUTS + 1)) })
		.read();
}
