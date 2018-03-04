#ifndef _HAL_SERVO_TEENSY_H_
#define _HAL_SERVO_TEENSY_H_

#include <Servo.h>

// Inherit and expand on the official library
class libServo : public Servo {
  public:
    int8_t attach(const int pin);
    int8_t attach(const int pin, const int min, const int max);
    void move(const int value);
    int8_t reattach(); // re-attaches to its given pin without re-setting the min-max values (supposes noone needs the pin for anyting else
  private:
     uint16_t min_ticks;
     uint16_t max_ticks;
     uint8_t servoIndex;               // index into the channel data for this servo
};

#endif // _HAL_SERVO_TEENSY_H_
