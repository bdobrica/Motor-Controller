#include "Arduino.h"
#include "Turtle.h"

Turtle::Turtle (Motor motor_x, Motor motor_y, Motor motor_z) {
	_mx = motor_x;
	_my = motor_y;
	_mz = motor_z;
	
	_x = 0.00;
	_y = 0.00;
	_z = 0.00;
	
	_u = 0.00;
	_v = 0.00;
	}
