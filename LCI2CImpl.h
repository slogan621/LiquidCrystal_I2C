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

#ifndef _LCI2CIMPL_H_
#define _LCI2CIMPL_H_

#include <inttypes.h>
#include <stddef.h> 

class LCI2CImpl {
public:
    virtual ~LCI2CImpl() {};
    virtual void init_priv() = 0;
    virtual void setBacklightVal(uint8_t backlightval) = 0;
    virtual void expanderWrite(uint8_t _data) = 0;
    virtual void delayMilliseconds(uint32_t delay) = 0;
    virtual void delayMicroseconds(uint32_t delay) = 0;
};

#endif
