#include "Particle.h"
#include "ParticleUtilities.h"
#include "Grove-Ultrasonic-Ranger.h"
#include "Grove_4Digit_Display.h"

// --------------------------------------------------------------------------------------

ParticleUtilities::ParticleUtilities(boolean serial, boolean point_on_off, TM1637 *displayUnit):   _serial(serial)
{
    byte initial[] = {0x0,0x0,0x0,0x0};
    _ListDisp = (byte*) calloc(DISPLAY_SIZE, sizeof(byte));
    memcpy(_ListDisp, initial, DISPLAY_SIZE);
    _displayUnit = displayUnit;
    _point_on_off = point_on_off;
    _start_display = false;
}

ParticleUtilities::~ParticleUtilities()
{
    free(_ListDisp);
}

void ParticleUtilities::init(void)
{
  (*_displayUnit).init();
  (*_displayUnit).point(_point_on_off);
  (*_displayUnit).set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

}

void ParticleUtilities::display(long value)
{
  long n = value;
  _ListDisp[3] = n % 10;
  n = n / 10;
  _ListDisp[2] = n % 10;
  n = n / 10;
  _ListDisp[1] = n % 10;
  n = n / 10;
  _ListDisp[0] = n % 10;
  _start_display = false;
  for (int pos = 3; pos >= 0; pos--)
  {
    if (_ListDisp[pos] > 0 || _start_display)
    {
      _start_display = true;
      (*_displayUnit).display(pos, _ListDisp[pos]);
    }
  }
}

// --------------------------------------------------------------------------------------
