#include "../include/main.h"
#include "../include/motorSetup.h"

okapi::Controller master;
const double wheelCircumfrence = 2.75 * M_PI;

int selected = 0;
std::string autons[9] = {"Disabled", "Pop", "NUMOGO", "AWP1", "AWP2", "TWONUMOGO", "Test", "Blue Z", "Skills"};
int size = 9;//*(&autons + 1) - autons;

void autonSelector(){
  master.clear();
  pros::delay(200);
  while(true){
    master.clear();
    pros::delay(100);
    control.print(2, 1, autons[selected].c_str());
    pros::delay(100);
     if(control.get_digital(DIGITAL_RIGHT)){
       selected = (selected + 1 + size) % size;
     }else if(control.get_digital(DIGITAL_LEFT)){
       selected = (selected - 1 + size) % size;
     }else if(control.get_digital(DIGITAL_A)){
       pros::delay(200);
       if(control.get_digital(DIGITAL_A)){
         goto slctEnd;
       }
     }
   }
   slctEnd:
   master.rumble("..");
}

void driverControl(double l, double r){

	FrontLeft.move_velocity(l);
	FrontRight.move_velocity(r);
	BackLeft.move_velocity(l);
	BackRight.move_velocity(r);
}

void fourbarmove(double speed){
  FBarR.move_velocity(speed);
  FBarL.move_velocity(speed);
}

void stopDrive(bool hold = false){
  if(hold){
    FrontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    FrontRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  FrontLeft.move_velocity(0);
	FrontRight.move_velocity(0);
	BackLeft.move_velocity(0);
	BackRight.move_velocity(0);
  delay(100);
  FrontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  FrontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void runDriveValues(){
  FrontLeft.move_velocity(drive.wheelFL);
	FrontRight.move_velocity(drive.wheelFR);
	BackLeft.move_velocity(drive.wheelBL);
	BackRight.move_velocity(drive.wheelBR);
}

double getEncoders(){
  return (FrontLeft.get_position()+FrontRight.get_position()+BackLeft.get_position()+BackRight.get_position());
}

void driveForward(double inches, pidController controller, double angle, pidController rtController, int timeMax = 5000){
  controller.resetID();
  rtController.resetID();
  double initialY = ((double) getEncoders()) * wheelCircumfrence/360;
  double targetY = ((double) getEncoders()) * wheelCircumfrence/360 + inches;
  int initialT = millis();
  controller.tVal = targetY;
  controller.error = controller.tVal - ((double) getEncoders()) * wheelCircumfrence/360;
  rtController.tVal = angle;
  rtController.error = angle - inertial.get_rotation();
  while(!controller.withinTarget() && millis() - initialT < timeMax){
    rtController.update(inertial.get_rotation());
    controller.update(((double)getEncoders()) * wheelCircumfrence/360);
    drive.calculateWheelSpeeds(controller.calculateOut(), rtController.calculateOut());
    runDriveValues();
    delay(10);
  }
  stopDrive(true);
}
