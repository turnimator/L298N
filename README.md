# L298N
## L298Nmotor(int pwmR=7, int in1L=4, int in2R=5, int pwmL=6, int in3L=12, int in4L=13)
If nothing is specified, the Contructor assumes a MEGA2560 board with the following pins used
### int pwmR=7
This is the pin that's connected to the 'Enable' input for the **right** motor on the L298N board.

### int in1L=4
This is the pin that's connected to the **IN1** input on the L298N board. It assumes that this input controls the **right** motor.

### int in2R=5
This is the pin that's connected to the **IN2** input on the L298N board. It assumes that this input controls the **right** motor.

### int pwmL=6
This is the pin that's connected to the 'Enable' input for the **left** motor on the L298N board.

### int in3L=12
This is the pin that's connected to the **IN3** input on the L298N board. It assumes that this input controls the **left** motor.

### int in4L=13
This is the pin that's connected to the **IN4** input on the L298N board. It assumes that this input controls the **left** motor.

## void turnlLeft(int8_t amt)
Turn the 'steering wheel' left by amt. This will reduce the speed of the left motor.

## void turnRight(int8_t amt)
Turn the 'steering wheel' right by amt. This will reduce the speed of the right motor.

## void returnToCenter(int increment)
Emulate caster angle forces, returning the steering wheel to center (increment=0 sets it dead center)

## void setThrottle(uint8_t newSpeed)
Set the amount of throttle. If the steering whell is centered at 90 deg, both left and right motors will get the same PWM value.

## void setGear(GearBox lever) 
This will manipulate the IN1, _IN2, IN3 and IN4 signals.

