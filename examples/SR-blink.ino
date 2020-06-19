#include "jshift.h"

#define SH_CP 9
#define DS 8
#define ST_CP 7

jshift sr(SH_CP , DS , ST_CP , 4);

void setup()
{

}

void loop()
{
    sr.writeBit(0,HIGH);
    delay(1000);
    sr.writeBit(0,LOW);
    delay(1000);
   
}