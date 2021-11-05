#include "../include/main.h"
#include  "../include/autonomous.h"


void leftBtn(){

}
void centerBtn(){

}
void rightBtn(){

}
void initialize() {
	pros::lcd::initialize();

	pros::lcd::register_btn0_cb(leftBtn);
	pros::lcd::register_btn1_cb(centerBtn);
	pros::lcd::register_btn2_cb(rightBtn);
	Clamp.set_brake_mode(MOTOR_BRAKE_HOLD);
	FBarL.set_brake_mode(MOTOR_BRAKE_HOLD);
	FBarR.set_brake_mode(MOTOR_BRAKE_HOLD);
  autonSelector();

	//autonSelector();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  switch(selected){
     case 0:
		 	disabledAuton();
     case 1:
		 	pop();
     case 2:
		 REDX();
     case 3:

     case 4:

     case 5:

     case 6:

     case 7:

		 case 8:
		 	skills();
   }
}

const int NUM_HEIGHTS = 3;
const int height1 = 0;
const int height2 = 700;
const int height3 = 1500;


const int heights[NUM_HEIGHTS] = {height1, height2,height3};
const int heights2[NUM_HEIGHTS] = {0, 700,1800};

int x = 0;

void my_task_fn(void* param) {
	std::string t =std::to_string( (FrontLeft.get_temperature()+FrontRight.get_temperature()+BackLeft.get_temperature()+BackRight.get_temperature())/4);
	control.print(1, 1, t.c_str());
		delay(200);
		// ...
}


void opcontrol() {
	master.clear();
	control.clear();
	Clamp.set_brake_mode(MOTOR_BRAKE_HOLD);
	FBarL.set_brake_mode(MOTOR_BRAKE_HOLD);
	FBarR.set_brake_mode(MOTOR_BRAKE_HOLD);
  int goalHeight = 0;
	double prevr = 0;
	double prevl = 0;
  while (true){
		Task my_task(my_task_fn);
		x+=1;
		double power = control.get_analog(ANALOG_LEFT_Y);
		double turn = control.get_analog(ANALOG_LEFT_X);
		driverControl(2*power+turn, 2*power - turn);
		if (control.get_digital(E_CONTROLLER_DIGITAL_X)){
			Clamp.move(100);
		}
		else if (control.get_digital(E_CONTROLLER_DIGITAL_B)){
			Clamp.move(-100);
		}
		else if(control.get_digital(E_CONTROLLER_DIGITAL_Y)){
			Clamp.move_absolute(0,-100);
		}
		else{
			Clamp.set_brake_mode(MOTOR_BRAKE_HOLD);
			Clamp.move_velocity(0);
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_UP)){
			autonomous();
		}
    if (RUp.changedToPressed() && goalHeight < NUM_HEIGHTS - 1) {
      goalHeight++;
      liftControl->setTarget(heights[goalHeight]);
    } else if (RDown.changedToPressed() && goalHeight > 0) {
      goalHeight--;
      liftControl->setTarget(heights[goalHeight]);
    }
		if (control.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      fourbarmove(200);

    } else if (control.get_digital(E_CONTROLLER_DIGITAL_L2)) {
      fourbarmove(-86);
    } else {
			FBarL.set_brake_mode(MOTOR_BRAKE_HOLD);
			FBarR.set_brake_mode(MOTOR_BRAKE_HOLD);
			fourbarmove(0);
		}
    pros::delay(20);
  }
}
