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
 * byj stepper : allow the use of a 28BYJ-48 stepper using 4 pins.
 */

#ifndef BYJSTEPPER_H
#define BYJSTEPPER_H

class ByjStepper {
  public:
  
    ByjStepper(void (*stepfunction)(const uint8_t new_step));
    
    init(const uint8_t pin0, const uint8_t pin1,const uint8_t pin2,const uint8_t pin3);
    
    void enable(const uint8_t new_enabled);
    uint8_t isEnabled();
    void setDir(const uint8_t new_direction);
    uint8_t getDir();
    void doStep(const uint8_t new_step);
    uint8_t getStep();
    

  private:
    uint8_t enabled;

    void (*internalstep)(const uint8_t command);
    uint8_t currentHalfStep;
    uint8_t currentDir;
    uint8_t halfStepIncrement;
    uint8_t currentStepBit;
    
    void step();
    
};

#endif // BYJSTEPPER_H
