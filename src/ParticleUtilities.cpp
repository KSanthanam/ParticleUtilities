#include "Particle.h"
#include "ParticleUtilities.h"
#include "Grove-Ultrasonic-Ranger.h"
#include "Grove_4Digit_Display.h"
#include "Grove_ChainableLED.h"

// --------------------------------------------------------------------------------------
DisplayUnit::DisplayUnit(boolean point_on_off, TM1637 *displayUnit)
{
  byte initial[] = {0x0, 0x0, 0x0, 0x0};
  _ListDisp = (byte *)calloc(DISPLAY_SIZE, sizeof(byte));
  memcpy(_ListDisp, initial, DISPLAY_SIZE);
  _displayUnit = displayUnit;
  _point_on_off = point_on_off;
  _start_display = false;
}

DisplayUnit::~DisplayUnit()
{
  free(_ListDisp);
}

void DisplayUnit::init(void)
{
  (*_displayUnit).init();
  (*_displayUnit).point(_point_on_off);
  (*_displayUnit).set(BRIGHT_TYPICAL); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}
void DisplayUnit::display(long value)
{
  long n = value;
  _ListDisp[3] = n % 10;
  n = n / 10;
  _ListDisp[2] = n % 10;
  n = n / 10;
  _ListDisp[1] = n % 10;
  n = n / 10;
  _ListDisp[0] = n % 10;
  for (int pos = 0; pos < DISPLAY_SIZE; pos++)
    (*_displayUnit).display(pos, _ListDisp[pos]);
}
// --------------------------------------------------------------------------------------
Leds::Leds(ChainableLED *leds, long range_low, long range_high)
{
  _leds = leds;
  _hue = 0.025;
}

void Leds::init()
{
  (*_leds).init();
}
void Leds::displayRange(long value)
{
  _hue = getHue(value);
  for (byte i = 0; i < NUM_LEDS; i++)
    (*_leds).setColorHSB(i, _hue, 1.0, 0.5);
};

float Leds::getHue(long value)
{
  if (value < _range_low)
  {
    return 0.25;
  }
  else if (value > _range_high)
  {
    return 0.75;
  }
  else
  {
    return 0.5;
  }
};

void Leds::display(long value)
{
  for (byte i = 0; i < NUM_LEDS; i++)
    (*_leds).setColorHSB(i, _hue, 1.0, 0.5);
  if (value < _range_low)
  {
    if (_hue < 0.025)
    {
      _hue = 0.025;
    }
    else
    {
      _hue -= 0.025;
    }
    return;
  }
  if (value > _range_high)
  {
    if (_hue > 1.0)
    {
      _hue = 0.90;
    }
    else
    {
      _hue += 0.025;
    }
    return;
  }
  _hue = 0.5;
  return;
}

// --------------------------------------------------------------------------------------
GroveSensors::GroveSensors(DisplayUnit *displayUnit, Ultrasonic *ultrasonic, Leds *leds)
{
  _displayUnit = displayUnit;
  _ultrasonic = ultrasonic;
  _leds = leds;
};

GroveSensors::~GroveSensors(){};

void GroveSensors::displayLED(long value)
{
  (*_leds).displayRange(value);
}

void GroveSensors::initialiseDisplay()
{
  (*_displayUnit).init();
};

long GroveSensors::getDistance()
{
  delay(150);
  long RangeInCentimeters;
  RangeInCentimeters = (*_ultrasonic).MeasureInCentimeters(); // two measurements should keep an interval
  return RangeInCentimeters;
}

// void ParticleUtilities::displayLED(long value)
// {
//   (*_leds).displayLED(value);
// }

void GroveSensors::display(long value)
{
  (*_displayUnit).display(value);
};

// --------------------------------------------------------------------------------------
