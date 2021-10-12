#include "main.h"
#include  "autonomous.h"




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
const int height2 = 50;
const int height3 = 100;


const int heights[NUM_HEIGHTS] = {height1, height2,height3};


void opcontrol() {
  int goalHeight = 0;
  while (true){
    drive->getModel()->arcade(master.getAnalog(ControllerAnalog::leftY),master.getAnalog(ControllerAnalog::leftX));
    if (RUp.changedToPressed() && goalHeight < NUM_HEIGHTS - 1) {
      goalHeight++;
      liftControl->setTarget(heights[goalHeight]);
    } else if (RDown.changedToPressed() && goalHeight > 0) {
      goalHeight--;
      liftControl->setTarget(heights[goalHeight]);
    }
    pros::delay(20);
  }
}
