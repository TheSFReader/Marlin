#ifndef _HAL_SERVO_TEENSY_H_
#define _HAL_SERVO_TEENSY_H_

#include <Servo.h>

// Inherit and expand on the official library
class libServo : public Servo {
  typedef Servo super;
  public:
    int8_t attach(const int pin);
    int8_t attach(const int pin, const int min, const int max);
    void move(const int value);
    int8_t reattach();                // re-attach to the given pin without resetting min/max (assumes nothing else needs the pin)
  private:
    uint16_t min_ticks;
    uint16_t max_ticks;
    uint8_t servoIndex;              // index into the channel data for this servo
    int inputpin;
    int inputmin;
    int inputmax;
};

#endif // _HAL_SERVO_TEENSY_H_
