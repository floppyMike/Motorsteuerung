#pragma once

#include "Mux.h"

using namespace admux;

static constexpr int MUX_S0 = 0;
static constexpr int MUX_S1 = 1;
static constexpr int MUX_S2 = 2;
static constexpr int MUX_S3 = 4;
static constexpr int MUX_EN = 7;

static constexpr int MUX_SIG1 = A0;
static constexpr int MUX_SIG2 = A1;

Mux mux[] = { Mux(Pin(MUX_SIG1, INPUT, PinType::Analog), Pinset(MUX_S0, MUX_S1, MUX_S2, MUX_S3), MUX_EN), 
			  Mux(Pin(MUX_SIG2, INPUT, PinType::Analog), Pinset(MUX_S0, MUX_S1, MUX_S2, MUX_S3), MUX_EN) };
