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
	piston.set_value(false);
	piston2.set_value(false);
	piston3.set_value(false);
	delay(2000);
  autonSelector();
  skillslinear.tolerance = 0.2;

}


void disabled() {
	control.clear();
}

void competition_initialize() {}

void autonomous() {
  switch(selected){
     case 0:
		 break;
     case 1:
	 	wings();
		 break;
     case 2:
		 leftGoal();
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
	case 9:
		skills();
		break;
	case 10:
		test();
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
	int maxtemp = FrontLeft.get_temperature();
	std::string maxmotor= "FrontLeft";
	if(FrontRight.get_temperature()>maxtemp){
		maxtemp = FrontRight.get_temperature();
		maxmotor = "FrontRight";
	}
	if(MidLeft.get_temperature()>maxtemp){
		maxtemp = MidLeft.get_temperature();
		maxmotor = "MidLeft";
	}
	if(MidRight.get_temperature()>maxtemp){
		maxtemp = MidRight.get_temperature();
		maxmotor = "MidRight";
	}
	if(BackRight.get_temperature()>maxtemp){
		maxtemp = BackRight.get_temperature();
		maxmotor = "BackRight";
	}
	if(BackLeft.get_temperature()>maxtemp){
		maxtemp = BackLeft.get_temperature();
		maxmotor = "BackLeft";
	}
	if(FBarR.get_temperature()>maxtemp){
		maxtemp = FBarR.get_temperature();
		maxmotor = "FBarR";
	}
	//std::string t =std::to_string(millis());
	control.print(1, 1,(maxmotor+std::to_string(maxtemp)).c_str());
	delay(200);
}


double ringSpeed = 0;

void ring(void* param) {
		Rings.move_velocity(ringSpeed);
		delay(30);
}


double lastpress;
double lastpressROn;
double lastpressRRev;



double spin = 1;

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
		  	Task rings_task(ring);

		//Task climbmode_(climbmode);
		double power = control.get_analog(ANALOG_LEFT_Y);
		double turn = control.get_analog(ANALOG_LEFT_X);
		driverControl(multiplier*(power+1*turn/4.5), multiplier*(power - 1*turn/4.5));
		if (control.get_digital(E_CONTROLLER_DIGITAL_X)){
			piston.set_value(true);
		}
		else if (control.get_digital(E_CONTROLLER_DIGITAL_B)){
			piston.set_value(false);
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_LEFT)){
			piston2.set_value(true);
		}
		else if (control.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
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
		if(control.get_digital(E_CONTROLLER_DIGITAL_Y) && millis()-lastpress>=1000){
			if (multiplier == 6){
				multiplier = 1.5;
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
		if(control.get_digital(E_CONTROLLER_DIGITAL_R1) && millis()-lastpressROn>=500){
			if (ringSpeed != 600){
				ringSpeed=600;
			}else{
				ringSpeed=0;
			}
			lastpressROn = millis();

		}
		if(control.get_digital(E_CONTROLLER_DIGITAL_R2) && millis()-lastpressROn>=500){
			if (ringSpeed != -200){
				ringSpeed=-200;
			}else{
				ringSpeed=0;
			}
			lastpressROn = millis();
		}
		if(control.get_digital(E_CONTROLLER_DIGITAL_UP)){
			piston3.set_value(true);
		}
		if(control.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
			piston3.set_value(false);
		}
    pros::delay(20);
  }
}
