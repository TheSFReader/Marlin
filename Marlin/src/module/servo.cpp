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
 * module/servo.cpp
 */

#include "../inc/MarlinConfig.h"

#if HAS_SERVOS

#include "servo.h"

HAL_SERVO_LIB servo[NUM_SERVOS];

void servo_init() {
  #if NUM_SERVOS >= 1 && HAS_SERVO_0
    #if (defined SERVO0_MIN_MS) && (defined SERVO0_MAX_MS)
      servo[0].attach(SERVO0_PIN, SERVO0_MIN_MS, SERVO0_MAX_MS);
    #else
      servo[0].attach(SERVO0_PIN);
    #endif
    servo[0].detach(); // Just set up the pin. We don't have a position yet. Don't move to a random position.
  #endif
  #if NUM_SERVOS >= 2 && HAS_SERVO_1
  #if (defined SERVO1_MIN_MS) && (defined SERVO1_MAX_MS)
    servo[1].attach(SERVO1_PIN, SERVO1_MIN_MS, SERVO1_MAX_MS);
  #else
    servo[1].attach(SERVO1_PIN);
  #endif
    servo[1].detach();
  #endif
  #if NUM_SERVOS >= 3 && HAS_SERVO_2
  #if (defined SERVO2_MIN_MS) && (defined SERVO2_MAX_MS)
    servo[2].attach(SERVO2_PIN, SERVO2_MIN_MS, SERVO2_MAX_MS);
  #else
    servo[2].attach(SERVO2_PIN);
  #endif
    servo[2].detach();
  #endif
  #if NUM_SERVOS >= 4 && HAS_SERVO_3
  #if (defined SERVO3_MIN_MS) && (defined SERVO3_MAX_MS)
    servo[3].attach(SERVO3_PIN, SERVO3_MIN_MS, SERVO3_MAX_MS);
  #else
    servo[3].attach(SERVO3_PIN);
  #endif
    servo[3].detach();
  #endif
}

#endif // HAS_SERVOS
