#include "Arduino.h"


class WheelEncoder {
    uint32_t pin;
    int32_t counter;
    void interrup_function();
public:
    WheelEncoder(uint32_t pin);
    ~WheelEncoder();
    void setup();
    inline int32_t count() {return counter;};
    inline void reset() {counter=0;};
    inline void countDiv(int numerator, int divider) {counter = (numerator*counter)/divider;}

};