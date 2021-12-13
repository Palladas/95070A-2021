#include "main.h"
#include  "../include/autonomous.h"
#include  "image.h"

/*
lv_obj_t * myButton;
lv_obj_t * myButtonLabel;
lv_obj_t * myLabel;

lv_style_t myButtonStyleREL; //relesed style
lv_style_t myButtonStylePR; //pressed style

static lv_res_t btn_click_action(lv_obj_t * btn)
{
    uint8_t id = lv_obj_get_free_num(btn); //id usefull when there are multiple buttons

    if(id == 0)
    {
        char buffer[100];
		sprintf(buffer, "button was clicked %i milliseconds from start", pros::millis());
		lv_label_set_text(myLabel, buffer);
    }

    return LV_RES_OK;
}*/

LV_IMG_DECLARE(logo_lvgl);

void leftBtn(){

}
void centerBtn(){

}
void rightBtn(){

}
void initialize() {
  LV_IMG_DECLARE(logo_lvgl)
  lv_obj_t * icon = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(icon, &logo_lvgl);
	/*lv_style_copy(&myButtonStyleREL, &lv_style_plain);
    myButtonStyleREL.body.main_color = LV_COLOR_MAKE(150, 0, 0);
    myButtonStyleREL.body.grad_color = LV_COLOR_MAKE(0, 0, 150);
    myButtonStyleREL.body.radius = 0;
    myButtonStyleREL.text.color = LV_COLOR_MAKE(255, 255, 255);

    lv_style_copy(&myButtonStylePR, &lv_style_plain);
    myButtonStylePR.body.main_color = LV_COLOR_MAKE(255, 0, 0);
    myButtonStylePR.body.grad_color = LV_COLOR_MAKE(0, 0, 255);
    myButtonStylePR.body.radius = 0;
    myButtonStylePR.text.color = LV_COLOR_MAKE(255, 255, 255);

    myButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
    lv_obj_set_free_num(myButton, 0); //set button is to 0
    lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
    lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL); //set the relesed style
    lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR); //set the pressed style
    lv_obj_set_size(myButton, 200, 50); //set the button size
    lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10); //set the position to top mid

    myButtonLabel = lv_label_create(myButton, NULL); //create label and puts it inside of the button
    lv_label_set_text(myButtonLabel, "Click the Button"); //sets label text

    myLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
    lv_label_set_text(myLabel, "Button has not been clicked yet"); //sets label text
    lv_obj_align(myLabel, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0); //set the position to centerx*/
	inertial.tare();
	FrontLeft.set_brake_mode(MOTOR_BRAKE_COAST);
	FrontRight.set_brake_mode(MOTOR_BRAKE_COAST);
	BackRight.set_brake_mode(MOTOR_BRAKE_COAST);
	BackLeft.set_brake_mode(MOTOR_BRAKE_COAST);
	piston.set_value(true);
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
		 NUMOGO();
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
		 	skills();
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



void opcontrol() {
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
		//Task climbmode_(climbmode);
		double power = control.get_analog(ANALOG_LEFT_Y);
		double turn = control.get_analog(ANALOG_LEFT_X);
		driverControl(multiplier*power+turn, multiplier*power - turn);
		if (control.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
		//	autonomous();
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_X)){
			piston.set_value(true);
		}
		else if (control.get_digital(E_CONTROLLER_DIGITAL_B)){
			piston.set_value(false);
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      fourbarmove(200);

    } else if (control.get_digital(E_CONTROLLER_DIGITAL_L2)) {
      fourbarmove(-86);
    } else {
			fourbarmove(0);
		}
		if (control.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
			//AWP1();
		}
		if(control.get_digital(E_CONTROLLER_DIGITAL_Y)){
			if (multiplier == 2){
				multiplier = 0.75;
				FrontLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
				FrontRight.set_brake_mode(MOTOR_BRAKE_HOLD);
				BackRight.set_brake_mode(MOTOR_BRAKE_HOLD);
				BackLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
				std::string climbstring = "Climb";
			}else{
				multiplier = 2;
				FrontLeft.set_brake_mode(MOTOR_BRAKE_COAST);
				FrontRight.set_brake_mode(MOTOR_BRAKE_COAST);
				BackRight.set_brake_mode(MOTOR_BRAKE_COAST);
				BackLeft.set_brake_mode(MOTOR_BRAKE_COAST);
				std::string climbstring = "No Climb";
			}

		}
    pros::delay(20);
  }
}
