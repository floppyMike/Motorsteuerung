#pragma once

class SerialStream
{
public:
	SerialStream() {}

	template<typename T>
	auto operator<<(const T &v) const -> const SerialStream &
	{
		Serial.print(v);
		return *this;
	}

	~SerialStream() { Serial.print('\n'); }
};
