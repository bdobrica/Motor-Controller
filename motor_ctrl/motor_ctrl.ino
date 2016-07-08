#include "pins.h"
#include "Motor.h"
#include "Turtle.h"

#define STEP_X_MM        3
#define STEP_Y_MM        3

#define X_LEN_MAX        90
#define Y_LEN_MAX        106

#define X_OFFSET         60
#define Y_OFFSET         70

Motor
  motor_x (X_STEP_PIN, X_DIR_PIN, X_ENABLE_PIN, X_MIN_PIN, X_MAX_PIN),
  motor_y (Y_STEP_PIN, Y_DIR_PIN, Y_ENABLE_PIN, Y_MIN_PIN, Y_MAX_PIN);

void snake () {
  int steps = int (X_LEN_MAX / STEP_X_MM);
  for (int c = 0; c<steps; c++) {
    motor_x.move (-STEP_X_MM);
    motor_y.move (c%2 ? Y_LEN_MAX : -Y_LEN_MAX);
    } 
  }
  
void offset () {
  motor_x.move (-X_OFFSET);
  motor_y.move (-Y_OFFSET);
  }

void setup() {
  // put your setup code here, to run once:
  motor_x.home ();
  motor_y.home ();
  offset ();
  delay (5000);
  snake ();
  delay (5000);
  motor_y.home ();
  motor_x.home ();
}

void loop() {
}
