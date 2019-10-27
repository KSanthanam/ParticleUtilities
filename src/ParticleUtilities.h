#ifndef __PARTICLEUTILITIES_H
#define __PARTICLEUTILITIES_H

#include "Particle.h"
#include "Grove_4Digit_Display.h"

#define DISPLAY_SIZE 4

class ParticleUtilities
{
public:
    ParticleUtilities(boolean serial, boolean point_on_off, TM1637 *displayUnit);
    ~ParticleUtilities();

    void display(long value);
    void init();
private:
    boolean _serial;
    boolean _point_on_off;
    byte* _ListDisp;
    TM1637 *_displayUnit;
    boolean _start_display;

};

#endif /* __PARTICLEUTILITIES_H */
