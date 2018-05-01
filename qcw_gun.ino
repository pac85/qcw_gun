#define PWMFREQ_IMPLEMENTATION
#include"pwm_freq.h"
#define UTILS_IMPLEMENTATION
#include "utils.h"
#include"pins.h"
#include"synth.h"
#include"GUI.h"


#include <LiquidCrystal.h>

#define NO_FAULT

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
ControlsGUI cGUI(&lcd);
ReadingsGUI rGUI(&lcd);

const int n_screens = 2;
int current_screen = 0;
bool switched = true;


void setup() {

    // defines for setting and clearing register bits
  #ifndef cbi
  #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
  #endif
  #ifndef sbi
  #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
  #endif
  
  // set prescale to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;

  init_pins();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("  QCW Gun V1.0 ");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print(" Maltese Andrea ");
  delay (3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Software by:  ");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("[   Pac85HV    ]");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Param. Control ");
  delay(2000);
  //buzz
  tone(buzzer_pin, 1000, 1000);
  delay (1000);
}

void loop() 
{
  float batt_voltage = read_batt_voltage(),
        bus_voltage = read_bus_voltage(),
        pri_current;

  /************************does checks*****************************/
  bool fault = false;
  #ifndef NO_FAULT
  #warning fault activated 
  fault = batt_voltage > 22.0f || bus_voltage < 320.0f;
  #endif
  /************************manages fault***************************/
  if(fault)
  {
    delay(1000);
    lcd.clear();
    lcd.print("  FAULT ACTIVE  ");
    lcd.setCursor(0, 1);
    lcd.print("    WARNING!    ");
    digitalWrite(fault_pin, HIGH);
    while(true)
    {
    tone(buzzer_pin,1000,500); 
    delay(1000);
      }
    }
  
  float bps = read_bps(),
        ton = read_ton(),
        amplitude = read_amplitude();

  /************************draws GUI*******************************/
  //switches screen when button is pressed
  if(digitalRead(menu_pin))
  {
    switched = true;
    current_screen++;
    current_screen %= n_screens;
  }
  while(digitalRead(menu_pin)){}
  switch(current_screen)
  {
    case 0:
      if(switched)
        cGUI.initial_draw();
      cGUI.set_params(bps, ton, amplitude);
      cGUI.draw();
      break;
    case 1:
      if(switched)
        rGUI.initial_draw();
      rGUI.draw();
      break;
  }
  switched = false;
  /************************draws GUI*******************************/

  //from here on the code is only executed if the trigger is pressed
  if(!digitalRead(trigger_pin)) 
  {
    delay(100); //limits the framerate to 10 to make the numbers on screen readable
    return;
  }
        
  const float ramp_down = 1.0f,
              supply_voltage = 300.0f,
              base_voltage = 47.0f;

  pri_current = play_ramp(m_to_u(ton-ramp_down),
                          m_to_u(ramp_down),
                          base_voltage/supply_voltage,
                          amplitude,
                          200.0f);  
                          
	delay(1000/bps);
  }

