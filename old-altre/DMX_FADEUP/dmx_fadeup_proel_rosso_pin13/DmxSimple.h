



// #if defined DMX_active 

#ifndef DmxSimple_h
#define DmxSimple_h

#include <inttypes.h>

#if RAMEND <= 0x4FF
#define DMX_SIZE 128
#else
#define DMX_SIZE 512
#endif

class DmxSimpleClass
{
  public:
    void maxChannel(int);
    void write(int, uint8_t);
    void usePin(uint8_t);
};
extern DmxSimpleClass DmxSimple;

#endif

 
