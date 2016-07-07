#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

#define MOTOR_STEP_DELAY	100
#define MOTOR_ENDSTOP_DELAY	50

#define MOTOR_STEP_LENGTH	0.0125

#define MOTOR_ENDSTOP_HIT_MIN	1
#define MOTOR_ENDSTOP_HIT_MAX	2
#define MOTOR_ENDSTOP_HIT_NONE	0

#define MOTOR_GOTO_HOME_MIN		false
#define MOTOR_GOTO_HOME_MAX		true
#define MOTOR_HOME_BACK_STEPS	100

#define MOTOR_ENDSTOP_ACTIVE	HIGH
#define MOTOR_ENABLE			LOW
#define MOTOR_DISABLE			HIGH

class Motor {
	public:
		Motor (uint8_t step, uint8_t dir, uint8_t enable, uint8_t min, uint8_t max, boolean invert = false);
		void enable ();
		void disable ();
		uint8_t endstop ();
		void step (boolean dir);
		void home (boolean where = MOTOR_GOTO_HOME_MIN);
		void measure (double length);
		void move (double length);

	private:
		boolean _enabled;
		boolean _forward;

		boolean _homed;
		boolean _where;

		double _length;

		uint8_t _step;
		uint8_t _dir;
		uint8_t _enable;
		uint8_t _min;
		uint8_t _max;
	};
#endif
