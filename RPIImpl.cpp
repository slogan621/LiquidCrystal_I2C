#if !defined(ARDUINO) 

#include "RPIImpl.h"
#include <inttypes.h>
#include "LiquidCrystal_I2C.h"

#include <time.h>
#include <errno.h>  
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

RPIImpl::RPIImpl(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
{
    _Addr = lcd_Addr;
    _cols = lcd_cols;
    _rows = lcd_rows;
    _backlightval = LCD_NOBACKLIGHT;

    /* default the adapter, almost surely wrong. caller should 
       inspect /sys/class/i2c-dev/ or run "i2cdetect -l" and
       use other constructor, which passes the adapter explicitly */

    _adapter = 1;  
    _fd = -1;
}

RPIImpl::RPIImpl(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t
i2c_adapter)
{
    _Addr = lcd_Addr;
    _cols = lcd_cols;
    _rows = lcd_rows;
    _backlightval = LCD_NOBACKLIGHT;
    _adapter = i2c_adapter;
    _fd = -1;
}

RPIImpl::~RPIImpl()
{
    if (_fd != -1) {
        ::close(_fd);
        _fd = -1;
    }
}

void RPIImpl::delayMilliseconds(uint32_t delay)
{
    // XXX this may need to push down to driver, given in userland, hard
    // to make strong promises about delays.

    struct timespec ts;
    int res;

    ts.tv_sec = delay / 1000;
    ts.tv_nsec = (delay % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);
}

void RPIImpl::delayMicroseconds(uint32_t delay)
{
    // XXX this may need to push down to driver, given in userland, hard
    // to make strong promises about delays.

    struct timespec ts;
    int res;

    ts.tv_sec = delay / 1000000;
    ts.tv_nsec = (delay % 1000000) * 1000000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);
}

void RPIImpl::setBacklightVal(uint8_t val)
{
    _backlightval = val;
}

void RPIImpl::init_priv()
{
    char filename[20];

    snprintf(filename, sizeof(filename), "/dev/i2c-%d", _adapter);
    _fd = open(filename, O_RDWR);
    if (_fd < 0) {
        /* ERROR HANDLING; you can check errno to see what went wrong */
    }
 
    if (ioctl(_fd, I2C_SLAVE, _Addr) < 0) {
        /* ERROR HANDLING; you can check errno to see what went wrong */
    }
#if defined(NOT_YET)
    Serial.print("ArduinoImpl::init_priv\n");
    Wire.begin();
#endif
}

void RPIImpl::expanderWrite(uint8_t data)
{
    if (_fd >= 0) {
        (void) write(_fd, (char *) &data, sizeof(data));
    }
#if defined(NOT_YET)
    Wire.beginTransmission(_Addr);
    printIIC((int)(_data) | _backlightval);
    Wire.endTransmission();
#endif
}

#endif // !ARDUINO
