/*
(C) Copyright Syd Logan 2020

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.

You may obtain a copy of the License at
http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef _ARDUINOIMPL_H_
#define _ARDUINOIMPL_H_

#include "LCI2CImpl.h"
#include "LiquidCrystal_I2C.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#define printIIC(args)  Wire.write(args)
#else
#include "WProgram.h"
#define printIIC(args)  Wire.send(args)
#endif

#include "Wire.h"

class ArduinoImpl : public LCI2CImpl { 
public:
    ArduinoImpl(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    virtual ~ArduinoImpl() {};
    virtual void init_priv();
    virtual void setBacklightVal(uint8_t val);
    virtual void delayMilliseconds(uint32_t val);
    virtual void delayMicroseconds(uint32_t val);
    virtual void expanderWrite(uint8_t _data);
private:
    uint8_t _Addr;
    uint8_t _cols;
    uint8_t _rows;
    uint8_t _backlightval;
};

#endif
