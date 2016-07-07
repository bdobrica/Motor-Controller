#include "Arduino.h"
#include "Motor.h"

Motor::Motor (uint8_t step, uint8_t dir, uint8_t enable, uint8_t min, uint8_t max, boolean invert) {
	pinMode (_step = step, OUTPUT);
	pinMode (_dir = dir, OUTPUT);
	pinMode (_enable = enable, OUTPUT);

	pinMode (_min = min, INPUT_PULLUP);
	pinMode (_max = max, INPUT_PULLUP);

	digitalWrite (_step, LOW);
	digitalWrite (_enable, MOTOR_DISABLE);

	_enabled = false;

	_forward = !invert;
	_homed = false;
	_where = false;
	}
  
void Motor::enable () {
	digitalWrite (_enable, MOTOR_ENABLE);
	_enabled = true;
	}

void Motor::disable () {
	digitalWrite (_enable, MOTOR_DISABLE);
	_enabled = false;
	}

void Motor::step (boolean dir) {
	if (!_enabled)
		digitalWrite (_enable, MOTOR_ENABLE);

	dir = dir ? _forward : !_forward;

	digitalWrite (_dir, dir ? HIGH : LOW);
	digitalWrite (_step, HIGH);
	delayMicroseconds (MOTOR_STEP_DELAY);
	digitalWrite (_step, LOW);
	delayMicroseconds (MOTOR_STEP_DELAY);

	if (!_enabled)
		digitalWrite (_enable, MOTOR_DISABLE);
	}

uint8_t Motor::endstop () {
	if (digitalRead (_min) == HIGH) {
		delayMicroseconds (MOTOR_ENDSTOP_DELAY);
		if (digitalRead (_min) == HIGH)
			return MOTOR_ENDSTOP_HIT_MIN;
		}

	if (digitalRead (_max) == HIGH) {
		delayMicroseconds (MOTOR_ENDSTOP_DELAY);
		if (digitalRead (_max) == HIGH)
			return MOTOR_ENDSTOP_HIT_MAX;
		}

	return MOTOR_ENDSTOP_HIT_NONE;
	}

void Motor::home (boolean where) {
	uint8_t hit = endstop ();
	uint8_t c;
	
	if (where == MOTOR_GOTO_HOME_MIN) {
		while (hit != MOTOR_ENDSTOP_HIT_MIN) {
			step (_forward);
			hit = endstop ();
			}

		for (c = 0; c < MOTOR_HOME_BACK_STEPS; c++)
			step (!_forward);
		
		_where = MOTOR_GOTO_HOME_MIN;
		}
	
	if (where == MOTOR_GOTO_HOME_MAX) {
		while (hit != MOTOR_ENDSTOP_HIT_MAX) {
			step (_forward);
			hit = endstop ();
			}

		for (c = 0; c < MOTOR_HOME_BACK_STEPS; c++)
			step (!_forward);
		
		_where = MOTOR_GOTO_HOME_MAX;
		}
	}

void Motor::move (double length) {
	boolean dir;
	long c, steps = long (length / MOTOR_STEP_LENGTH);
	dir = steps < 0 ? !_forward : _forward;
	steps = abs (steps);
	for (long c = 0; c < steps; c++)
		step (dir);
	}
