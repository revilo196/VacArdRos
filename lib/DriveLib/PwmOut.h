#pragma once

#include <Arduino.h>

class PwmOut {
    uint32_t pinNum;
    PinName pin;
    float value;

public:
    PwmOut(uint32_t pinNum);
    PwmOut(PinName pin);
    static void setFreq(uint32_t f);
    static void setRes(uint32_t res);

    void operator=(float value);
};