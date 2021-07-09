#pragma once

class Log
{
public:
	template<typename T>
	auto operator<<(const T &v) const -> const Log &
	{
		Serial.print(v);
		return *this;
	}
};

class SerialStream : public Log
{
public:
	SerialStream() { Log() << '[' << millis() << "]\t"; }
	~SerialStream() { *this << '\n'; }
};

class StatusStream
{
public:
	StatusStream(const char *log) { Log() << '[' << millis() << "]\t" << log << "..."; }
	~StatusStream() { Log() << "SUCCESS\n"; }
};
