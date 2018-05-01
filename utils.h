#ifndef UTILS
#define UTILS
#include "pwm_freq.h"
#include "pins.h"


#ifdef UTILS_IMPLEMENTATION

inline float f_map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

inline void f_analogWrite(float f, int pin)
{
  analogWrite(pin, min(f*255, 255));
}

inline float f_analogRead(int pin)
{
	return analogRead(pin) / 1024.0f;
}

int get_TCCR0B_divisor()
{
	switch(TCCR0B & 0b00000111)
	{
		case 0x1: return 1;
		case 0x2: return 8;
		case 0x3: return 64;
		case 0x4: return 256;
		case 0x5: return 1024;
	}
}

//unmessed version of delayMicroseconds
inline void u_delayMicroseconds(unsigned long int us)
{
  delayMicroseconds(us);
}

//unmessed version of delay
inline void u_delay(unsigned long int us)
{
  delay(us/**64/get_TCCR0B_divisor()*/);
}

//unmessed version of micros
inline unsigned long u_micros()
{
  return micros()/*/64 * get_TCCR0B_divisor()*/;
}

//unmessed version of millis
inline unsigned long u_millis()
{
  return millis()/*/64 * get_TCCR0B_divisor()*/;
}

//returns the current time in seconds
inline float ftime()
{
	return float(u_millis())/1000.0f;
}

/****************************math********************************/
inline float fract(float a)
{
  int i_part = a;   //extract integer part
  return a-i_part;  //decimnal part is simply the float part minus the integer part
}

float rand(float n){return fract(sin(n) * 43758.5453123);}

inline float m_to_u(float a){return a/1000.0f;}//from milli to unit

/*************************circuit specific***********************/
inline float read_batt_voltage()
{
	const float k = 30.0;	//to be adjusted so that the reading is correct
	return f_analogRead(batt_pin)*k;
}

inline float	read_bus_voltage()
{
	const float k = 400.0;	//to be adjusted so that the reading is correct
	return f_analogRead(batt_pin)*k;
}

inline float read_pri_current()
{
	const float k = 200.0;	//to be adjusted so that the reading is correct
	return f_analogRead(batt_pin)*k;
}

inline float read_bps()
{	
  const float min_bps = 1.0f, max_bps = 30.0f;
  
	return f_analogRead(bps_pin)*(max_bps-min_bps)+min_bps;
}

inline float read_ton()
{
	const float min_ton = 5.0f, max_ton = 20.0f;
  
  return f_analogRead(ton_pin)*(max_ton-min_ton)+min_ton;
}

inline float read_amplitude()
{
	//const float min_ampl = 0.0f, max_ampl = 1.0f;

  return f_analogRead(amplitude_pin);
}

#include <LiquidCrystal.h>
//an helper class to properly display strings in an lcd screen
class LCDString
{
public:
	LCDString(int x, int y, LiquidCrystal * lcd)
	{
		this->x = x, this->y = y, this->lcd = lcd;
	}
	void 	setString(const String &s)
	{
		/*for(int i = 0;i < max(last_length, s.length());i++ )
		{
			lcd->setCursor(x, y);
			if(i < s.length())
			{
				lcd->write(s.charAt(i));
			}
			else
			{
				lcd->write(' ');
			}
		}
		last_length = s.length();*/
        lcd->setCursor(x, y);
        for(int i = 0;i < last_length;i++)
            lcd->write(' ');

        lcd->setCursor(x, y);
        lcd->print(s);
        last_length = s.length();
	}
	
private:
	int last_length = 0;
	int x, y;
	LiquidCrystal * lcd;
};

#endif

#endif

 
