/* ============================================================================
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
 * ============================================================================*/


#ifndef jshift_h
#define jshift_h

#include "Arduino.h"

class jshift
{
    public :

        // Inisiasi Pin dan jumlah IC yg terpasang
        jshift(uint8_t _clockPin , uint8_t _dataPin , uint8_t _latchPin , uint8_t _count = 1 );

        // Fungsi-fungsi public
        void writeBit(uint8_t _expNo, uint8_t _pin , uint8_t _stat);
        void writeBit(uint8_t _pin , uint8_t _stat);
        void writeByte(uint8_t _expNo , uint8_t _data);
        void writeByte(uint8_t _data);

        // Fungsi batch
        void batchBegin();
        void batchWrite();

    private :
        // Fungsi-fungsi uint8_ternal
        void shiftByte(uint8_t _data);
        void shiftAllOut(uint8_t _count);

        // Variabel-variabel uint8_ternal
        uint8_t clockPin ; // Pin Clock/SH_CP pada IC 74HC595 
        uint8_t dataPin ; // Pin Data/DS pada IC 74HC595 
        uint8_t latchPin ; // Pin Latch/ST_CP pada IC 74HC595 
        uint8_t count ; // Jumlah IC yg terpasang Daisy Chain

        uint8_t batchMode ; // Batch mode untuk write beberapa perintah

        // Internal main register data
        uint8_t registerData[64];

};

#endif