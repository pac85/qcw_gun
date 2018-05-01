#ifndef PINS
#define PINS
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; 																		//LCD pins
const int buzzer_pin = 7, trigger_pin = 8, menu_pin = 13, interrupter_pin = 10, fault_pin = 6;	//buttons
const int pri_current_pin = 0, batt_pin = 1, bus_pin = 2;																				//mesuraments
const int bps_pin = 3, ton_pin = 4, amplitude_pin = 5;																					//regulations

/*************************************DO NOT CHANGE!****************************************/
const int pwm_out = 9;

/*******************************************************************************************/
inline void init_pins()
{
	pinMode(buzzer_pin,				OUTPUT);
	pinMode(interrupter_pin, 	OUTPUT);
	pinMode(fault_pin, 				OUTPUT);
  pinMode(pwm_out,          OUTPUT);
	
	pinMode(trigger_pin, 			INPUT);
	pinMode(menu_pin, 				INPUT);
	
	pinMode(pri_current_pin, 	INPUT);
	pinMode(batt_pin, 				INPUT);
	pinMode(bus_pin, 					INPUT);
	pinMode(bps_pin, 					INPUT);
	pinMode(ton_pin, 					INPUT);
	pinMode(amplitude_pin, 		INPUT);
}

#endif
