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
  stepper_indirection.h - stepper motor driver indirection macros
  to allow some stepper functions to be done via SPI/I2c instead of direct pin manipulation
  Part of Marlin

  Copyright (c) 2015 Dominik Wenger

  Marlin is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Marlin is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Marlin.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * servo stepper : allow the use of a servo in place of a stepper.
 *
 */

#ifndef SERVOSTEPPER_H
#define SERVOSTEPPER_H

class ServoStepper {
  public:
    ServoStepper(uint8_t servoIndex);
    ServoStepper(uint8_t servoIndex, bool invert_dir, int16_t min_endstop_pos, int16_t max_endstop_pos);
    void init();
    void enable(uint8_t enabled);
    uint8_t isEnabled();
    void setDir(uint8_t direction);
    uint8_t getDir();
    void doStep(uint8_t step);
    uint8_t getStep();
    FORCE_INLINE bool read_MIN_Endstop()
    {
        bool result = (currentPosition < min_endstop_pos) ^ invert_dir;
        /*
      SERIAL_ECHOPAIR("Check Min", currentPosition);
      if(invert_dir)
      SERIAL_ECHO("(inverted");
      SERIAL_ECHOPAIR("<", min_endstop_pos);
      SERIAL_ECHOLNPAIR(" -->", result);
      */
      return result;
    }
    FORCE_INLINE bool read_MAX_Endstop()
    {
      SERIAL_ECHOPAIR("Check Max", currentPosition);
      SERIAL_ECHOLNPAIR(">", min_endstop_pos);
      return currentPosition > max_endstop_pos;
    }

  private:
    uint8_t enabled;
    uint8_t servoIndex;               // index into the channel data for this servo
    int16_t currentPosition;
    int16_t lastPositionSent;
    uint8_t currentDir;
    bool invert_dir;
    uint8_t previousStepWrite;
    int16_t min_endstop_pos;
    int16_t max_endstop_pos;
    char stepIncrement;


};

extern void servostepper_init();

#endif // SERVOSTEPPER_H
