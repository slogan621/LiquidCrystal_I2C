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

#include "ArduinoImpl.h"
#include <inttypes.h>

ArduinoImpl::ArduinoImpl(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
{
    _Addr = lcd_Addr;
    _cols = lcd_cols;
    _rows = lcd_rows;
    _backlightval = LCD_NOBACKLIGHT;
}

void ArduinoImpl::setBacklightVal(uint8_t val)
{
    _backlightval = val;
}

void ArduinoImpl::delayMilliseconds(uint32_t val)
{
    ::delay(val);
}

void ArduinoImpl::delayMicroseconds(uint32_t val)
{
    ::delayMicroseconds(val);
}

void ArduinoImpl::init_priv()
{
    Serial.print("ArduinoImpl::init_priv\n");
    Wire.begin();
}

void ArduinoImpl::expanderWrite(uint8_t _data)
{                                        
    Wire.beginTransmission(_Addr);
    printIIC((int)(_data) | _backlightval);
    Wire.endTransmission();   
}
