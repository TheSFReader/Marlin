/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * servo stepper : allow the use of a servo in place of a stepper.
 *
 */



#include "../inc/MarlinConfig.h"



#if ENABLED(HAVE_SERVOSTEPPER)

#include "servostepper.h"

#include "../module/servo.h"



extern Servo servo[NUM_SERVOS];



ServoStepper::ServoStepper(uint8_t servoNr, bool invert_dir, int16_t min_endstop_pos, int16_t max_endstop_pos) {
  servoIndex = servoNr;
  currentPosition = 1500;
  currentDir = 0;
  previousStepWrite = 0;
  enabled = 0;

  this->invert_dir = invert_dir;
  // If the dir is inverted, we also need to invert the min/max tests.
  // The most efficient way to do that is to switch te values and negate the result if inverted
  // And the most efficient way to negate the result if inverted is to xor the result with invert_dir
  // (removes a conditional)
  if(! invert_dir) {
    this->min_endstop_pos = min_endstop_pos;
    this->max_endstop_pos = max_endstop_pos;
  } else {
    this->min_endstop_pos = max_endstop_pos;
    this->max_endstop_pos = min_endstop_pos;
  }

  stepIncrement = invert_dir ? -1 : 1;
}

ServoStepper::ServoStepper(uint8_t servoNr) {
  servoIndex = servoNr;
  currentPosition = 1500;
  currentDir = 0;
  previousStepWrite = 0;
  enabled = 0;
  invert_dir = true;
  min_endstop_pos = 1100;
  max_endstop_pos = 1900;

  stepIncrement = invert_dir ? -1 : 1;
}

void ServoStepper::init() {

}

void ServoStepper::enable(uint8_t newenabled) {
  if(newenabled) {
    if(! enabled) {
      servo[servoIndex].reattach();
    }
  } else {
    if(enabled) {
      servo[servoIndex].detach();
    }
  }
  enabled = newenabled;

}

 uint8_t ServoStepper::isEnabled() {
  return servo[servoIndex].attached();
 }

void ServoStepper::setDir(uint8_t direction) {
  currentDir = direction;
  // Set to either -1 or 1 (easier to add).
  stepIncrement=(invert_dir ^ currentDir) * 2 - 1;
}

uint8_t ServoStepper::getDir() {
  return currentDir;
}

void ServoStepper::doStep(uint8_t stepByte) {
   // Only step on rising edge
   if(stepByte && previousStepWrite != stepByte) {
    currentPosition += stepIncrement;

    if(! servo[servoIndex].attached()) {
     servo[servoIndex].reattach();
    }
    servo[servoIndex].writeMicroseconds(currentPosition);
  }
  previousStepWrite = stepByte;
}




#endif // HAVE_SERVOSTEPPER
