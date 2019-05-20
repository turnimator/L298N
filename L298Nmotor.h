#ifndef L298Nmotor_h
#define L298Nmotor_h
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
	int __motor_r_pwm_pin;
	int __motor_r_in1_pin;
	int __motor_r_in2_pin;

	int __motor_l_pwm_pin;
	int __motor_l_in3_pin;
	int __motor_l_in4_pin;

	uint8_t _throttle = 0;
	int8_t _steering_wheel = 90; // 90 degrees = straight ahead
	GearShift _gear = PARK; // Start in PARK. We don't want any accidents

	void setPwm();
public:
	L298Nmotor(int pwmR=6, int in1L=38, int in2R=39, int pwmL=7, int in3L=40, int in4L=41);
	void turnlLeft(int8_t amt);
	void turnRight(int8_t amt);
	void returnToCenter(int increment); // Emulate caster angle forces, returning the steering wheel to center (increment=0 sets it dead center)
	void setThrottle(uint8_t newSpeed);
	void setGear(GearShift lever) ;
};
#endif

