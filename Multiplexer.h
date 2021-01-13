#pragma once

struct Bit4
{
	unsigned char v : 4;
};

class Multiplexer
{
public:
	Multiplexer(int z, int s0, int s1, int s2, int s3, int en)
		: m_z(z)
		, m_s{ s0, s1, s2, s3 }
		, m_en(en)
	{
		turn(true);
	}

	/**
	 * @brief Change the target pin
	 * @param a Address of the pin (integer is possible)
	 */
	auto address(Bit4 a) const -> const Multiplexer &
	{
		for (char i = 0; i < sizeof(m_s) / sizeof(m_s[0]); ++i) digitalWrite(m_s[i], a.v & (1 << i) ? HIGH : LOW);
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