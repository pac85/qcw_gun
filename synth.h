#include "utils.h" 
#include "pins.h"

struct f_out
{
  f_out(){}

  f_out(float a, float b)
  {
    wave = a;
    amplitude = b;
  }
  float wave, amplitude;
};

/***************************drums*******************************/

inline f_out kick(float ftime)
{
  float amplitude = exp(-15.0*ftime);
  return f_out(sin(6.2831*45.0*ftime)*amplitude, amplitude);
}

inline f_out snare(float ftime)
{
  float amplitude = exp(-45.0*ftime)+exp(-55.0*ftime);
  return f_out((sin(6.2831*230.0*ftime))*exp(-55.0*ftime)*0.8 + rand(ftime*100.0)*exp(-45.0*ftime), amplitude);
}

inline f_out ltom(float ftime)
{
  float amplitude = exp(-35.0*ftime);
  return f_out(sin(6.2831*130.0*ftime)*amplitude, amplitude);
}

inline f_out lmtom(float ftime)
{
  float amplitude = exp(-35.0*ftime);
  return f_out(sin(6.2831*150.0*ftime)*amplitude, amplitude);
}

inline f_out htom(float ftime)
{
  float amplitude = exp(-35.0*ftime);
  return f_out(sin(6.2831*190.0*ftime)*amplitude, amplitude);
}
/***************************drums*******************************/

inline float ramp(float tup, float td, float ampl, float ftime)
{
  return max(ftime < tup ? ftime/tup : 1.0f - ((ftime-tup)/td), 0);
}

enum  drum_types
{
  /*SNARE = 38,
  KICK = 35,
  KICK1 = 36,*/
  KICK = 36,
  SNARE = 38,
  //C_HIHAT = 42,
  //O_HIHAT = 46,
  LTOM = 45,
  LMTOM = 47,
  HTOM = 50
  //C_CYMB = 49,
  //R_CYMB = 51,
  //R_BELL =53

};

void play_drum(float drum_ampl, float tup, float td, float base, float ramp_ampl, drum_types drumt)
{
	setPwmFrequency(pwm_out, 1);
  tup = min(m_to_u(5), tup);

  const float stop_threshold = 0.01f;    	//once the function amplitude reaches this value it will stop being played
  const float drum_delay = m_to_u(5.0f);	//after how many ms the drum sound as to start
  //const float tup= m_to_u(10.0f), td=m_to_u(1.0f), base = 40.0f / 310.0f, ampl = ;
  float f_amplitude = 1.0f;             	//the amplitude of the drum function

  //writes initial value and waits
  f_analogWrite(base, pwm_out);
  u_delay(1);
  digitalWrite(interrupter_pin, HIGH);

  unsigned long start_time;
  switch(drumt)
  {
    case KICK:
      start_time = u_micros();
      while(f_amplitude > stop_threshold)
      {
        //calculates time making shure that it starts from zero
        float ftime = (u_micros()-start_time)/1000000.0f;

        //drum sound
        f_out drum_r;
        if(ftime > drum_delay)
          drum_r = kick(ftime - drum_delay);
        else
          drum_r = f_out(0.0f, 10.0f);

        //ramp
        float ramp_r = ramp(tup, td, ramp_ampl, ftime);

        //combines the two
        float combined = drum_ampl*drum_r.wave + ramp_ampl*ramp_r;
        //adds bias(half the drum sound amplitude unless it is less than the base voltage)
        combined += base + drum_ampl*drum_r.amplitude/2.0f;

        f_analogWrite(combined, pwm_out);

        f_amplitude = drum_r.amplitude;
      }
      break;
    case SNARE:
      start_time = u_micros();
      while(f_amplitude > stop_threshold)
      {
        //calculates time making shure that it starts from zero
        float ftime = (u_micros()-start_time)/1000000.0f;

        //drum sound
        f_out drum_r;
        if(ftime > drum_delay)
          drum_r = snare(ftime - drum_delay);
        else
          drum_r = f_out(0.0f, 10.0f);

        //ramp
        float ramp_r = ramp(tup, td, ramp_ampl, ftime);

        //combines the two
        float combined = drum_ampl*drum_r.wave + ramp_ampl*ramp_r;
        //adds bias(half the drum sound amplitude unless it is less than the base voltage)
        combined += base + drum_ampl*drum_r.amplitude/2.0f;

        f_analogWrite(combined, pwm_out);

        f_amplitude = drum_r.amplitude;
      }
      break;
    case LTOM:
      start_time = u_micros();
      while(f_amplitude > stop_threshold)
      {
        //calculates time making shure that it starts from zero
        float ftime = (u_micros()-start_time)/1000000.0f;

        //drum sound
        f_out drum_r;
        if(ftime > drum_delay)
          drum_r = ltom(ftime - drum_delay);
        else
          drum_r = f_out(0.0f, 10.0f);

        //ramp
        float ramp_r = ramp(tup, td, ramp_ampl, ftime);

        //combines the two
        float combined = drum_ampl*drum_r.wave + ramp_ampl*ramp_r;
        //adds bias(half the drum sound amplitude unless it is less than the base voltage)
        combined += base + drum_ampl*drum_r.amplitude/2.0f;

        f_analogWrite(combined, pwm_out);

        f_amplitude = drum_r.amplitude;
      }
      break;
    case LMTOM:
      start_time = u_micros();
      while(f_amplitude > stop_threshold)
      {
        //calculates time making shure that it starts from zero
        float ftime = (u_micros()-start_time)/1000000.0f;

        //drum sound
        f_out drum_r;
        if(ftime > drum_delay)
          drum_r = lmtom(ftime - drum_delay);
        else
          drum_r = f_out(0.0f, 10.0f);

        //ramp
        float ramp_r = ramp(tup, td, ramp_ampl, ftime);

        //combines the two
        float combined = drum_ampl*drum_r.wave + ramp_ampl*ramp_r;
        //adds bias(half the drum sound amplitude unless it is less than the base voltage)
        combined += base + drum_ampl*drum_r.amplitude/2.0f;

        f_analogWrite(combined, pwm_out);

        f_amplitude = drum_r.amplitude;
      }
      break;
    case HTOM:
      start_time = u_micros();
      while(f_amplitude > stop_threshold)
      {
        //calculates time making shure that it starts from zero
        float ftime = (u_micros()-start_time)/1000000.0f;

        //drum sound
        f_out drum_r;
        if(ftime > drum_delay)
          drum_r = htom(ftime - drum_delay);
        else
          drum_r = f_out(0.0f, 10.0f);

        //ramp
        float ramp_r = ramp(tup, td, ramp_ampl, ftime);

        //combines the two
        float combined = drum_ampl*drum_r.wave + ramp_ampl*ramp_r;
        //adds bias(half the drum sound amplitude unless it is less than the base voltage)
        combined += base + drum_ampl*drum_r.amplitude/2.0f;

        f_analogWrite(combined, pwm_out);

        f_amplitude = drum_r.amplitude;
      }
      break;

     default:
      start_time = u_micros();
      while(f_amplitude > stop_threshold)
      {
        //calculates time making shure that it starts from zero
        float ftime = (u_micros()-start_time)/1000000.0f;

        //drum sound
        f_out drum_r;
        if(ftime > drum_delay)
          drum_r = htom(ftime - drum_delay);
        else
          drum_r = f_out(0.0f, 10.0f);

        //ramp
        float ramp_r = ramp(tup, td, ramp_ampl, ftime);

        //combines the two
        float combined = drum_ampl*drum_r.wave + ramp_ampl*ramp_r;
        //adds bias(half the drum sound amplitude unless it is less than the base voltage)
        combined += base + drum_ampl*drum_r.amplitude/2.0f;

        f_analogWrite(combined, pwm_out);

        f_amplitude = drum_r.amplitude;
      }
      break;


  }
  digitalWrite(interrupter_pin, LOW);
  u_delay(1);
  f_analogWrite(0, pwm_out);
	resetPwmFrequency(pwm_out);
}

float play_ramp(float tup, float td, float base, float ramp_ampl, float max_current)
{
	float peak_current;
	setPwmFrequency(pwm_out, 1);
  tup = max(m_to_u(5), tup);

  const float stop_threshold = 0.01f;    	//once the function amplitude reaches this value it will stop being played
  float f_amplitude = 1.0f;             	//the amplitude of ramp

  //writes initial value and waits
  f_analogWrite(base, pwm_out);
  u_delay(1);
  digitalWrite(interrupter_pin, HIGH);

  //makes sure the ramp is scaled not to clip due to the base offset
  ramp_ampl *= 1.0f-base;

  unsigned long start_time;
  
	start_time = u_micros();
	float ftime = tup/2.0f;
	while(/*f_amplitude > stop_threshold && ftime > (tup/1.5f)*/ftime < (tup+td))
	{
		//calculates time making shure that it starts from zero
		ftime = (u_micros()-start_time)/1000000.0f;

		//ramp
		float ramp_r = ramp(tup, td, ramp_ampl, ftime);

    f_amplitude = ramp_r;

		//combines the two
		float combined = ramp_r*ramp_ampl;
		//adds bias
		combined += base ;

		f_analogWrite(combined, pwm_out);
		
		/*//does current reading
		float primary_current = read_pri_current();
		peak_current = max(peak_current, primary_current);
		if(primary_current > max_current)
			break;*/
	}
	
  digitalWrite(interrupter_pin, LOW);
  u_delay(1);
  f_analogWrite(0, pwm_out);
	resetPwmFrequency(pwm_out);
	
	return peak_current;
}
