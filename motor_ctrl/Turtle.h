#ifndef TURTLE_H
#define TURTLE_H

#include "Arduino.h"
#include "Motor.h"

class Turtle {
	public:
		Turtle (Motor motor_x, Motor motor_y, Motor motor_z);
		// move
		void forward (double length);
		void back (double length);
		void setpos (double x, double y, double z);
		void home ();
		void arc (double x, double y, double z, double angle, double radius);

		// rotate
		void left (double length);
		void right (double length);
		void up (double length);
		void down (double length);
		
		// get position
		double xcor ();
		double ycor ();
		double zcor ();
		
		// get heading (rotation matrix)
		double heading ();
		double towards (double x, double y, double z);

	private:
		Motor _mx;
		Motor _my;
		Motor _mz;
	
		double _x;
		double _y;
		double _z;

		double _u;
		double _v;
	};

#endif
