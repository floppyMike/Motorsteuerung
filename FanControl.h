#pragma once

#define MUX Type4067Mux

MUX mux[] = { MUX(MUX_SIG1, INPUT, ANALOG, MUX_S0, MUX_S1, MUX_S2, MUX_S3, MUX_EN), 
							MUX(MUX_SIG2, INPUT, ANALOG, MUX_S0, MUX_S1, MUX_S2, MUX_S3, MUX_EN) };

// Max temperatures
static constexpr int TIEFSETZ_TEMP[] = { 20, 70 };
static constexpr int MOTOR_TEMP[] = { 20, 70 };
static constexpr int VORSTARK_TEMP[] = { 20, 70 };
static constexpr int BMS_TEMP[] = { 20, 70 };
static constexpr int HOCHSETZ_TEMP[] = { 20, 70 };
static constexpr int MOTOR_TREIB_TEMP[] = { 20, 70 };

// Wenn Lüfter unter der unteren Grenze ist ~> schalte Lüfter an.
// Schrittweise erhöhe die Temperatur (Schritt = (Hoch Grenze - Niedrig Grenze) / 100), Lüfter werden von 0% bis 100% getrieben
// Um ein und aus schalten zu vermeiden wird ein Temperatur Toleranz eingesetzt (Entweder hard coded oder custom Toleranz für jedes Element)
//  ~> Die Toleranz ist der Puffer die der Lüfter an sein muss oder aus sein muss bei der anfänglichen Grenze
// 

// Range 1 (input_start till input_end) to Range 2 (output_start till output_end)
// output = output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start)

constexpr int map(int val, int temp_min, int temp_max, int volt_min, int volt_max)
{
    return volt_min + (volt_max - volt_min) / (temp_max - temp_min) * (val - temp_min);
    //return volt_min + (volt_max - volt_min) / (temp_min - temp_max) * (val - temp_max);
}

int part_val(int pin)
{
    constexpr int MAX_PINS_MULTI = 16;
    MUX* const m = pin < MAX_PINS_MULTI ? mux : mux + 1;
    return m->read(pin % MAX_PINS_MULTI);
}

int fan_val(int pin, int val)
{
    analogWrite(pin, val);
}