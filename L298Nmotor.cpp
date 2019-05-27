//extern "C" {
#include <Arduino.h>
//}
#include "L298Nmotor.h"


uint8_t _throttle = 0;
int8_t _steering_wheel = 90; // 90 degrees = straight ahead
GearShift _gear = PARK; // Start in PARK. We don't want any accidents

void L298Nmotor::setPwm()
{
	uint8_t throttle_left = _throttle;
	uint8_t throttle_right = _throttle;
	int8_t w = _steering_wheel - 90; // Center at 0
	if (w < 0) { // Turning right
		throttle_left = (_throttle * abs(w)) / 180;
	}
	if (w > 0) { // Turning left
		throttle_right = (_throttle * abs(w)) / 180;
	}
	analogWrite(_motor_r_pwm_pin, throttle_left);
	analogWrite(_motor_l_pwm_pin, throttle_right);
}

L298Nmotor::L298Nmotor(int pwmR, int in1L, int in2R, int pwmL, int in3L, int in4L)
{
	_motor_r_pwm_pin  = pwmR;
	_motor_r_in1_pin = in1L;
	_motor_r_in2_pin = in2R;

	_motor_l_pwm_pin    = pwmL;
	_motor_l_in3_pin = in3L;
	_motor_l_in4_pin = in4L;
	pinMode(_motor_r_pwm_pin, OUTPUT);
	pinMode(_motor_r_in1_pin, OUTPUT);
	pinMode(_motor_r_in2_pin, OUTPUT);

	pinMode(_motor_l_pwm_pin, OUTPUT);
	pinMode(_motor_l_in3_pin, OUTPUT);
	pinMode(_motor_l_in4_pin, OUTPUT);

	_throttle = 0;
	_gear = PARK;
}


void L298Nmotor::turnLeft(int amt)
{
	_steering_wheel += amt;
	if (_steering_wheel > 180) {
		_steering_wheel = 180;
	}
	setPwm();
}

void L298Nmotor::turnRight(int amt)
{
	_steering_wheel -= amt;
	if (_steering_wheel < 0) {
		_steering_wheel = 0;
	}
	setPwm();
}

void L298Nmotor::returnToCenter(int increment)
{
	if (_steering_wheel == 90){
		return;
	}
	if (increment == 0){
		_steering_wheel = 90;
		setPwm();
		return;
	}
	if (_steering_wheel < 90){
		turnRight(increment);
	}
	if (_steering_wheel > 90){
		turnLeft(increment);
	}
}

int L298Nmotor::getSteeringWheel()
{
	return _steering_wheel;
}

void L298Nmotor::setThrottle(unsigned int newSpeed) 
{
	_throttle = newSpeed;
	setPwm();
}

unsigned int L298Nmotor::getThrottle()
{
	return _throttle;
}

void L298Nmotor::setGear(GearShift lever) 
{

	_gear = lever;

	switch (lever) {
		case DRIVE: {
				    digitalWrite(_motor_r_in1_pin, HIGH);
				    digitalWrite(_motor_r_in2_pin, LOW);
				    digitalWrite(_motor_l_in3_pin, HIGH);
				    digitalWrite(_motor_l_in4_pin, LOW);
			    }
			    break;
		case DRIVE_L: {
				      digitalWrite(_motor_r_in1_pin, LOW);
				      digitalWrite(_motor_r_in2_pin, HIGH);
				      digitalWrite(_motor_l_in3_pin, HIGH);
				      digitalWrite(_motor_l_in4_pin, LOW);
			      }
			      break;
		case DRIVE_R: {
				      digitalWrite(_motor_r_in1_pin, HIGH);
				      digitalWrite(_motor_r_in2_pin, LOW);
				      digitalWrite(_motor_l_in3_pin, LOW);
				      digitalWrite(_motor_l_in4_pin, HIGH);
			      }
			      break;
		case REVERSE: {
				      digitalWrite(_motor_r_in1_pin, LOW);
				      digitalWrite(_motor_r_in2_pin, HIGH);
				      digitalWrite(_motor_l_in3_pin, LOW);
				      digitalWrite(_motor_l_in4_pin, HIGH);
			      }
			      break;
		case NEUTRAL:
			      digitalWrite(_motor_r_in1_pin, LOW);
			      digitalWrite(_motor_r_in2_pin, LOW);
			      digitalWrite(_motor_l_in3_pin, LOW);
			      digitalWrite(_motor_l_in4_pin, LOW);
			      break;
		case PARK:
			      digitalWrite(_motor_r_in1_pin, LOW);
			      digitalWrite(_motor_r_in2_pin, LOW);
			      digitalWrite(_motor_l_in3_pin, LOW);
			      digitalWrite(_motor_l_in4_pin, LOW);
			      break;
		default: {// NEUTRAL
				 digitalWrite(_motor_r_in1_pin, LOW);
				 digitalWrite(_motor_r_in2_pin, LOW);
				 digitalWrite(_motor_l_in3_pin, LOW);
				 digitalWrite(_motor_l_in4_pin, LOW);
			 }
			 break;
	}
}

GearShift  L298Nmotor::getGear()
{
	return _gear;
}

char* L298Nmotor::getGearString()
{

	switch(_gear){
		case PARK: return "P"; break;
		case REVERSE: return "R"; break;
		case NEUTRAL: return "N"; break;
		case DRIVE: return "D"; break;
		case DRIVE_L: return "DL"; break;
		case DRIVE_R: return "DR"; break;
	}
	return "E";
}

