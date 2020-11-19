// Requirements
//	- Fan control frequency > 20kHz

// Importants
//	- Fan control is 0 till 255
//	- Temperature input is 0 till 1023

#include "Type4067Mux.h"

struct Fan
{
	int out;
	int mult_in;
};

// Tiefsetzer, Motor, Vorverstärker, BMS, Hochsetzer, Motor Treiber; index is multiplexer input port
static constexpr int LUEFTER[] = { 3, 5, 6, 9, 11, 13 };

static constexpr int MUX_S0 = 0;
static constexpr int MUX_S1 = 1;
static constexpr int MUX_S2 = 2;
static constexpr int TIEFSETZ_LUFT = 3;
static constexpr int MUX_S3 = 4;
static constexpr int MOTOR_LUFT = 5;
static constexpr int VORSTARK_LUFT = 6;
static constexpr int MUX_EN = 7;
static constexpr int ZUND = 8;
static constexpr int BMS_LUFT = 9;
static constexpr int PWM = 10;
static constexpr int HOCHSETZ_LUFT = 11;
static constexpr int NOT_AUS = 12;
static constexpr int MOTOR_TREIB_LUFT = 13;

static constexpr int MUX_SIG1 = A0;
static constexpr int MUX_SIG2 = A1;
static constexpr int GAS = A5;

bool disable = false;

#include "FanControl.h"



void setup() 
{
	pinMode(PWM, OUTPUT); // Timer 2 controls 11 and 3
	pinMode(3, OUTPUT);

	// Setup PWM Timer
	TCCR1A = _BV(COM1A0) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);   // COM0A0 = Toggle OCR0A; COM0B1 = Use OCR0B; WGM## = Set PWM mode
	TCCR1B = _BV(WGM12) | _BV(CS11);                                // Vorteiler = 8
	OCR1A = 100;                                                    // (16MHz / f / Vorteiler = OCR0A; f -> 20kHz)
	OCR1B = 0;                                                      // 100 is 100% and 1 is 1%

	Serial.begin(9600);

	analogWrite(3, 255);
}

void loop() 
{
	// Read Poti from pedal
	const unsigned int pot = analogRead(GAS);

	// Monitor poti values
	Serial.print("OCR1B: "), Serial.print(pot), Serial.print('\n');

	// Disable PWM at 0 or disable
	if (pot == 0 || disable)
		TCCR1B = _BV(WGM12);
	else
		TCCR1B = _BV(WGM12) | _BV(CS11);

	// Set PWM value
	OCR1B = pot;

	// Poll all sensors for temperatur
	for (auto i = 0, end = sizeof(LUEFTER) / sizeof(LUEFTER[0]); i < end; ++i)
	{
		const auto temp_range = part_val(LUEFTER[i]); // Between 0 and 1023
		const auto voltage_range = map(temp, 0, 1023, 0, 255);
		fan_val(i, voltage_range); // Between 0 and 255
	}
	
	delay(100);
}
