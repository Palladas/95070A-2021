#include "main.h"
#include  "../include/autonomous.h"


void leftBtn(){

}
void centerBtn(){

}
void rightBtn(){

}
void initialize() {
	pros::lcd::initialize();
	inertial.tare();
	Left_Enc.reset();
	Right_Enc.reset();
	piston.set_value(false);
	delay(2000);
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
		 break;
     case 1:
		 break;
     case 2:
		 wiiings();
		 break;
     case 3:
		 AWP1();
		 break;
     case 4:
		 AWP2();
		 break;
     case 5:
		 TWONUMOGO();
		 break;
     case 6:
		 SNUMOGO();
		 break;
     case 7:
		 STWOMOGO();
		 break;
		 case 8:
		 	solowinpoint();
			break;
   }
	return;
}


const int NUM_HEIGHTS = 3;
const int height1 = 0;
const int height2 = 700;
const int height3 = 1500;


const int heights[NUM_HEIGHTS] = {height1, height2,height3};
const int heights2[NUM_HEIGHTS] = {0, 700,1800};

int x = 0;


bool climb = 0;

std::string climbstring = "No Climb";

void my_task_fn(void* param) {
	std::string t =std::to_string( (FrontLeft.get_temperature()+FrontRight.get_temperature() + BackLeft.get_temperature()+ BackRight.get_temperature()+FBarR.get_temperature())/6);
	control.print(1, 1,t.c_str());
		delay(200);
}

double lastpress;

void opcontrol() {
	FBarR.set_brake_mode(MOTOR_BRAKE_HOLD);
	Clamp.set_brake_mode(MOTOR_BRAKE_HOLD);
	FrontLeft.set_brake_mode(MOTOR_BRAKE_COAST);
	FrontRight.set_brake_mode(MOTOR_BRAKE_COAST);
	BackRight.set_brake_mode(MOTOR_BRAKE_COAST);
	BackLeft.set_brake_mode(MOTOR_BRAKE_COAST);
	MidLeft.set_brake_mode(MOTOR_BRAKE_COAST);
	MidRight.set_brake_mode(MOTOR_BRAKE_COAST);
	master.clear();
  int goalHeight = 0;
	double prevr = 0;
	double prevl = 0;
	double multiplier = 6;
  while (true){
		printOnScreen();
		Clamp.set_brake_mode(MOTOR_BRAKE_HOLD);
	  Task my_task(my_task_fn);
		//Task climbmode_(climbmode);
		double power = control.get_analog(ANALOG_LEFT_Y);
		double turn = control.get_analog(ANALOG_LEFT_X);
		driverControl(multiplier*(power+3*turn/6), multiplier*(power - 3*turn/6));
		if (control.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
		//	autonomous();
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_X)){
			piston.set_value(true);
		}
		else if (control.get_digital(E_CONTROLLER_DIGITAL_B)){
			piston.set_value(false);
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_UP)){
			piston2.set_value(true);
		}
		else if (control.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
			piston2.set_value(false);
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      fourbarmove(100);

    } else if (control.get_digital(E_CONTROLLER_DIGITAL_L2)) {
      fourbarmove(-100);
    } else {
			fourbarmove(0);
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      Clamp.move_velocity(200);

    } else if (control.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			Clamp.move_velocity(-200);

    } else {
			Clamp.move_velocity(0);

		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
			//AWP1();
		}
		if(control.get_digital(E_CONTROLLER_DIGITAL_Y) && millis()-lastpress>=1000){
			if (multiplier == 2){
				multiplier = 0.75;
				FrontLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
				FrontRight.set_brake_mode(MOTOR_BRAKE_HOLD);
				BackRight.set_brake_mode(MOTOR_BRAKE_HOLD);
				BackLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
        MidRight.set_brake_mode(MOTOR_BRAKE_HOLD);
        MidLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
				std::string climbstring = "Climb";
				lastpress = millis();
			}else{
				multiplier = 6;
				FrontLeft.set_brake_mode(MOTOR_BRAKE_COAST);
				FrontRight.set_brake_mode(MOTOR_BRAKE_COAST);
				BackRight.set_brake_mode(MOTOR_BRAKE_COAST);
				BackLeft.set_brake_mode(MOTOR_BRAKE_COAST);
        MidRight.set_brake_mode(MOTOR_BRAKE_COAST);
        MidLeft.set_brake_mode(MOTOR_BRAKE_COAST);
				std::string climbstring = "No Climb";
				lastpress = millis();
			}

		}
    pros::delay(20);
  }
}
