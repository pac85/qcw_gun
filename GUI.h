#include "utils.h"
class ControlsGUI
{
public:
	ControlsGUI(LiquidCrystal * _lcd) : LSbps(0, 4, _lcd), LSton(6, 10, _lcd), LSamplitude(12, 16, _lcd)
	{
		this->lcd = _lcd;
	}
	void initial_draw()
	{
		lcd->clear();
		lcd->setCursor(0, 0);
		lcd->print("Bps   Ton   Ampl");
	}
	void draw()
	{
		LSbps.setString(String(bps));
		LSton.setString(String(ton));
		LSamplitude.setString(String(amplitude));
	}
	void set_params(float bps , float ton, float amplitude)
	{
		this->bps = bps, this->ton = ton, this->amplitude = amplitude;
	}
private:
	float bps , ton, amplitude;
	LiquidCrystal * lcd;
	LCDString LSbps, LSton, LSamplitude;
};

class ReadingsGUI
{
public:
	ReadingsGUI(LiquidCrystal * _lcd) : LSbatt(0, 4, _lcd), LSbus(6, 10, _lcd), LSpri(12, 16, _lcd)
	{
		this->lcd = _lcd;
	}
	
	void initial_draw()
	{
		lcd->clear();
		lcd->setCursor(0, 0);
		lcd->print("Batt  Bus   Prim");
	}
	void draw()
	{
		LSbatt.setString(String(batt));
		LSbus.setString(String(bus));
		LSpri.setString(String(pri));
	}
	void set_params(float batt, float bus, float pri)
	{
		this->batt = batt, this->bus = bus, this->pri = pri;
	}
private:
	float batt, bus, pri;
	LiquidCrystal * lcd;
	LCDString LSbatt, LSbus, LSpri;
};
