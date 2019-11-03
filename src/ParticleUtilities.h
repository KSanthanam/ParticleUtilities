#ifndef __PARTICLEUTILITIES_H
#define __PARTICLEUTILITIES_H

#include "Particle.h"
#include "Grove_4Digit_Display.h"
#include "Grove-Ultrasonic-Ranger.h"
#include "Grove_ChainableLED.h"

#define DISPLAY_SIZE 4
#define NUM_LEDS 5

class DisplayUnit
{
    public:
        DisplayUnit(boolean point_on_off, TM1637 *displayUnit);
        ~DisplayUnit();

        void display(long value);
        void init();
    private:
        boolean _point_on_off;
        byte* _ListDisp;
        TM1637 *_displayUnit;
        boolean _start_display;
};

class Leds 
{
    public:
        Leds(ChainableLED *leds, long range_low, long range_high);
        void display(long value);
        void displayRange(long value);
        void init();
    private:
        ChainableLED *_leds;
        long _range_low;
        long _range_high;
        float _hue;    
        float getHue(long value);    
};

class GroveSensors
{
public:
    GroveSensors(DisplayUnit *displayUnit, Ultrasonic *ultrasonic,Leds  *leds);
    ~GroveSensors();

    void display(long value);
    void initialiseDisplay();
    long getDistance();
    void displayLED(long value);
private:
    DisplayUnit *_displayUnit;
    Ultrasonic *_ultrasonic;
    Leds *_leds;
};

#endif /* __PARTICLEUTILITIES_H */
