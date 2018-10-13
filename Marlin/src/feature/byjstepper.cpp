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
 * byjstepper.cpp - Enable the use of a byj stepper.
 */

#include "../inc/MarlinConfig.h"

#if ENABLED(USE_BYJSTEPPER)

#include "byjstepper.h"

const uint8_t halfSteps[8]={1, 3, 2, 6, 4, 12, 8, 9 };

ByjStepper::ByjStepper(void (*stepfunction)(const uint8_t new_step)) {
  
  internalstep = stepfunction;
  
  currentDir = 0;
  currentStepBit = 0;
  enabled = 0;
  
}


ByjStepper::init(const uint8_t pin0,const uint8_t pin1,const uint8_t pin2,const uint8_t pin3) {
   pinMode(pin0, OUTPUT);
   pinMode(pin1, OUTPUT);
   pinMode(pin2, OUTPUT);
   pinMode(pin3, OUTPUT);
}

void ByjStepper::enable(const uint8_t new_enabled) {
  enabled = new_enabled;
  
    uint8_t command = (!new_enabled) ? halfSteps[currentHalfStep] : 0;
    (*internalstep)(command);
}

uint8_t ByjStepper::isEnabled() { return enabled; }

void ByjStepper::setDir(const uint8_t new_direction) { currentDir = new_direction; }

uint8_t ByjStepper::getDir() { return currentDir; }

void ByjStepper::doStep(const uint8_t new_step) {
  if (currentStepBit != new_step) {
    step();
  }
  currentStepBit = new_step;
}

void ByjStepper::step() {
  if(currentDir)
    currentHalfStep ++;
  else 
    currentHalfStep--;
  currentHalfStep = currentHalfStep % 8;
  
  (*internalstep)(halfSteps[currentHalfStep]);
  
  /*SERIAL_ECHO_START();
    SERIAL_ECHO(command & 1);
    SERIAL_ECHO((command >> 1) & 1);
    SERIAL_ECHO((command >> 2) & 1);
    SERIAL_ECHO((command >> 3) & 1); */
}



#endif // BYJSTEPPER_H
