/* ==========================================================================
 * jShift - General Library untuk IC 74HC595
 * 
 * Tujuan : 
 * - Meringkaskan Fungsi-fungsi shift data apabila menggunakan IC 74HC595
 * - Menambah Output digital pada Arduino
 * - Diperuntukan untuk output kecil seperti LED
 * 
 * Hanya menggunakan 3 pin Arduino
 * Dapat dipasang hingga 64 buah IC 74HC595
 * Koneksi IC Daisy Chain
 * 
 * (c) 2020 - judincahsigerung@gmail.com
 * ==============================================================================*/

#include "Arduino.h"
#include "jshift.h"


// Inisiasi Shift Register
jshift::jshift(uint8_t _clockPin , uint8_t _dataPin , uint8_t _latchPin , uint8_t _count )
{
    clockPin = _clockPin ;
    dataPin = _dataPin ;
    latchPin = _latchPin ;

    count = _count - 1 ;

    // Semua pin dijadikan Output
    pinMode(_clockPin , OUTPUT);
    pinMode(_dataPin , OUTPUT);
    pinMode(_latchPin , OUTPUT);
}

// Shift 8 bit without latch
void jshift::shiftByte(uint8_t _data)
{
    for (int i = 0 ; i < 8 ; i++)  
    {
        digitalWrite(clockPin, LOW);
        if (_data & (0x80 >> i ) ) digitalWrite(dataPin , HIGH);
        else digitalWrite(dataPin, LOW);
        digitalWrite(clockPin, HIGH);
    }

}

// Shift All data and latch
void jshift::shiftAllOut(uint8_t _count)
{
    digitalWrite(latchPin , HIGH);
    
    for (int i = _count ; i >= 0 ; i-- )
    {
        shiftByte(registerData[i]);
    }
    
    digitalWrite(latchPin , LOW);
}

// write 1 bit ke IC tujuan
void jshift::writeBit(uint8_t _expNo , uint8_t _pin , uint8_t _stat)
{
    unsigned char temp;
    temp = ((temp | 1) << _pin);
    if (_stat) registerData[_expNo] |= temp ;
    else registerData[_expNo] &= ~temp ;

    if(!batchMode)  shiftAllOut(count);
}

// Write 1 bit ke IC no. 1
void jshift::writeBit(uint8_t _pin , uint8_t _stat)
{
    unsigned char temp;
    temp = ((temp | 1) << _pin);
    if (_stat) registerData[0] |= temp ;
    else registerData[0] &= ~temp ;

    if(!batchMode) shiftAllOut(count);
}

void jshift::writeByte(uint8_t _expNo , uint8_t _data)
{
    registerData[_expNo] = _data ;
    if(!batchMode) shiftAllOut(count);
}

void jshift::writeByte(uint8_t _data)
{
    registerData[0] = _data ;
    if(!batchMode) shiftAllOut(count);
}

void jshift::batchBegin()
{
    batchMode = 1 ;
}

void jshift::batchWrite()
{
    if (batchMode) shiftAllOut(count);
    batchMode = 0 ;
}