class SerialStream
{
public:
	SerialStream() {}

	template<typename T>
	auto operator<<(const T &v) -> SerialStream &
	{
		Serial.print(v);
		return *this;
	}

	~SerialStream() { Serial.print('\n'); }
};