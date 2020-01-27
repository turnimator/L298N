#ifndef L298Nmotor_h
#define L298Nmotor_h

extern "C" {
#include "stdint.h"
#include "stdlib.h"
}

enum GearShift {
  PARK,
  REVERSE,
  NEUTRAL,
  DRIVE,
  DRIVE_L,
  DRIVE_R
};

class L298Nmotor{
private:
	int _motor_r_pwm_pin;
	int _motor_r_in1_pin;
	int _motor_r_in2_pin;

	int _motor_l_pwm_pin;
	int _motor_l_in3_pin;
	int _motor_l_in4_pin;

	unsigned int _throttle = 0;
	int _steering_wheel = 90; // 90 degrees = straight ahead
	GearShift _gear = PARK; // Start in PARK. We don't want any accidents

	void setPwm();
public:
	L298Nmotor(int pwmR=7, int in1L=4, int in2R=5, int pwmL=6, int in3L=12, int in4L=13);
	void turnLeft(int amt);
	void turnRight(int amt);
	void returnToCenter(int increment); // Emulate caster angle forces, returning the steering wheel to center (increment=0 sets it dead center)
	void setThrottle(unsigned int newSpeed);
	unsigned int getThrottle();
	int getSteeringWheel();
	void setGear(GearShift lever) ;
	GearShift getGear();
	char *getGearString();
};
#endif

