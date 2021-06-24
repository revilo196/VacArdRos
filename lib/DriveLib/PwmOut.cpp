#include "PwmOut.h"

PwmOut::PwmOut(uint32_t pinNum) {
    this->pinNum = pinNum;
    this->pin = digitalPinToPinName(pinNum);
    value = 0;
    pinMode(pinNum, OUTPUT);
    analogWrite(pinNum, value);
}

PwmOut::PwmOut(PinName pin) {
    this->pinNum = pinNametoDigitalPin(pin);
    this->pin = pin;
    value = 0;
    pinMode(pinNum, OUTPUT);
    analogWrite(pinNum, value);
}

void PwmOut::operator=(float value) {
    if(value >= 0.0f && value <= 1.001f) {
        analogWrite(pinNum, (uint32_t)(value*255) );
    }
}

void PwmOut::setFreq(uint32_t f) {
    analogWriteFrequency(f);
}
void PwmOut::setRes(uint32_t res) {
    analogWriteResolution(res);
}