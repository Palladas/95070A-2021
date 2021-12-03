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
	piston.set_value(false);
	calibrateSensors();
  autonSelector();
}

void disabled() {
	control.clear();
	delay(200);
}

void competition_initialize() {}

void autonomous() {
  switch(selected){
     case 0:

     case 1:

     case 2:
		 NUMOGO();
     case 3:
		 AWP1();
     case 4:
		 AWP2();
     case 5:
		 TWONUMOGO();
     case 6:
		 test();
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
	std::string t =std::to_string( (FrontLeft.get_temperature()+FrontRight.get_temperature() + BackLeft.get_temperature()+ BackRight.get_temperature()+Clamp.get_temperature()+FBarR.get_temperature()+ FBarL.get_temperature())/7);
	control.print(1, 1, t.c_str());
		delay(200);
}

bool climb = 0;

std::string climbstring = "No Climb";

void climbmode() {
	if (climb){
		std::string climbstring = "Climb";
	}
	else{
		std::string climbstring = "No Climb";
	}
	control.print(2, 1, climbstring.c_str());
		delay(200);
}

void opcontrol() {
	Clamp.set_brake_mode(MOTOR_BRAKE_HOLD);
	FBarL.set_brake_mode(MOTOR_BRAKE_HOLD);
	FBarR.set_brake_mode(MOTOR_BRAKE_HOLD);
	FrontLeft.set_brake_mode(MOTOR_BRAKE_COAST);
	FrontRight.set_brake_mode(MOTOR_BRAKE_COAST);
	BackRight.set_brake_mode(MOTOR_BRAKE_COAST);
	BackLeft.set_brake_mode(MOTOR_BRAKE_COAST);
	master.clear();
  int goalHeight = 0;
	double prevr = 0;
	double prevl = 0;
	double multiplier = 2;
  while (true){
		Task my_task(my_task_fn);
		Task climbmode(my_task_fn);
		double power = control.get_analog(ANALOG_LEFT_Y);
		double turn = control.get_analog(ANALOG_LEFT_X);
		driverControl(multiplier*power+turn, multiplier*power - turn);
		if (control.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
			piston.set_value(true);
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_LEFT)){
			piston.set_value(false);
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_X)){
			Clamp.move(100);
		}
		else if (control.get_digital(E_CONTROLLER_DIGITAL_B)){
			Clamp.move(-100);
		}
		else{
			Clamp.move_velocity(0);
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
			fourbarmove(0);
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
			AWP1();
		}
		if(control.get_digital(E_CONTROLLER_DIGITAL_Y)){
			if (multiplier == 2){
				multiplier = 0.75;
				FrontLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
				FrontRight.set_brake_mode(MOTOR_BRAKE_HOLD);
				BackRight.set_brake_mode(MOTOR_BRAKE_HOLD);
				BackLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
				climb = 1;
			}else{
				multiplier = 2;
				FrontLeft.set_brake_mode(MOTOR_BRAKE_COAST);
				FrontRight.set_brake_mode(MOTOR_BRAKE_COAST);
				BackRight.set_brake_mode(MOTOR_BRAKE_COAST);
				BackLeft.set_brake_mode(MOTOR_BRAKE_COAST);
				climb = 0;
			}

		}
    pros::delay(20);
  }
}
