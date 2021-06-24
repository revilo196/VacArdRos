#include "WheelEncoder.h"

#define M_PI 3.14159265358979323846


    WheelEncoder::WheelEncoder(uint32_t pin)
    {
        this->pin = pin;
        counter = 0;
    }

    WheelEncoder::~WheelEncoder(){
        detachInterrupt(pin);
    }

    void WheelEncoder::setup(){
        pinMode(pin, INPUT);
        attachInterrupt(pin,std::bind(&WheelEncoder::interrup_function, this), CHANGE);
    }

    void WheelEncoder::interrup_function() {
        counter++;
    }