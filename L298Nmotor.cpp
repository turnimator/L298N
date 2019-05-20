
uint8_t _throttle = 0;
int8_t _steering_wheel = 90; // 90 degrees = straight ahead
GearShift _gear = PARK; // Start in PARK. We don't want any accidents

void L298Nmotor::setPwm()
{
	uint8_t throttle_left = _throttle;
	uint8_t throttle_right = _throttle;
	int8_t w = _steering_wheel - 90; // Center at 0
	if (w < 0) { // Turning left
		throttle_left = (throttle * abs(w)) / 100;
	}
	if (w > 0) { // Turning right
		throttle_right = (throttle * abs(w)) / 100;
	}
	analogWrite(_motor_r_pwm_pin, throttle_left);
	analogWrite(_motor_l_pwm_pin, throttle_right);
}

L298Nmotor::L298Nmotor(int pwmR=6, int in1L=38, int in2R=39, int pwmL=7, int in3L=40, int in4L=41)
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


void L298Nmotor::turnlLeft(int8_t amt)
{
	steering_wheel += amt;
	if (steering_wheel > 180) {
		steering_wheel = 180;
	}
	setPwm();
}

void L298Nmotor::turnRight(int8_t amt)
{
	steering_wheel -= amt;
	if (steering_wheel < 0) {
		steering_wheel = 0;
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


void L298Nmotor::setThrottle(uint8_t newSpeed) {
	_throttle = newSpeed;
	setPwm();
}

void L298Nmotor::setGear(GearShift lever) {

	__gear = lever;

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

	GearBox  L298Nmotor::getGear()
	{
		return _gear;
	}

}

