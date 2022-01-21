#include "../include/main.h"
#include "../include/motorSetup.h"

okapi::Controller master;
const double wheelCircumfrence = 10*3.25 * M_PI/6;

int selected = 0;
std::string autons[9] = {"Disabled", "Pop", "LeftGoal", "AWP1", "AWP2", "TWONUMOGO", "SNUMOGO", "S2NUMOGO", "Skills"};
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
  MidLeft.move_velocity(l);
	MidRight.move_velocity(r);
	BackLeft.move_velocity(l);
	BackRight.move_velocity(r);
}

void fourbarmove(double speed){
  FBarR.move_velocity(speed);
}

void stopDrive(bool hold = false){
  if(hold){
    FrontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    FrontRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    MidLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    MidRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  FrontLeft.move_velocity(0);
	FrontRight.move_velocity(0);
	BackLeft.move_velocity(0);
	BackRight.move_velocity(0);
  MidLeft.move_velocity(0);
  MidRight.move_velocity(0);
  delay(100);
  FrontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  FrontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  MidLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  MidRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void runDriveValues(){
  FrontLeft.move_velocity(drive.wheelFL);
	FrontRight.move_velocity(drive.wheelFR);
	BackLeft.move_velocity(drive.wheelBL);
	BackRight.move_velocity(drive.wheelBR);
  MidLeft.move_velocity(drive.wheelBL);
	MidRight.move_velocity(drive.wheelBR);
}

void printOnScreen(){
	//lcd::print(1, "Velocity FL: %f", FrontLeft.get_actual_velocity());
	//lcd::print(2, "Target Velocity FL: %f", drive.wheelTL);
  lcd::print(0, "Forklift Reading: %f", Clamp.get_position());
  lcd::print(1, "Y Wheel Reading: %f", ((double) Left_Enc.get_value()));
  lcd::print(2, "X Wheel Reading: %f", ((double) Right_Enc.get_value()));
}


double getEncoders(){
  return (FrontLeft.get_position()+FrontRight.get_position())/2;
}

void driveForward(double inches, pidController controller, double maxRPM = 600){
  stopDrive(false);
  controller.resetID();
  double initialY = ((double) getEncoders()) *( wheelCircumfrence/900);
  double targetY = ((double) getEncoders()) * (wheelCircumfrence/900) + inches;

  int initialT = millis();
  controller.tVal = targetY;
  controller.error = controller.tVal - initialY;
  lcd::print(2, std::to_string(inertial.get_rotation()).c_str());
  while(!controller.withinTarget()){
    controller.update(((double)getEncoders()) * wheelCircumfrence/900);
    drive.calculateWheelSpeeds(controller.calculateOut(), 0,maxRPM);
    runDriveValues();
    delay(10);
  }
  FrontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  FrontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  MidLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  MidRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  FrontLeft.move_velocity(0);
	FrontRight.move_velocity(0);
	BackLeft.move_velocity(0);
	BackRight.move_velocity(0);
}

void driveForward(double inches, pidController controller, double angle, pidController rtController, double maxRPM = 600){
  controller.resetID();
  rtController.resetID();
  double initialY = ((double) getEncoders()) *( wheelCircumfrence/900);
  double targetY = ((double) getEncoders()) * (wheelCircumfrence/900) + inches;
  int initialT = millis();
  controller.tVal = targetY;
  controller.error = controller.tVal - initialY;
  rtController.tVal = angle;
  rtController.error = angle - inertial.get_rotation();
  while(!controller.withinTarget()){
    rtController.update(inertial.get_rotation());
    controller.update(((double)getEncoders()) * wheelCircumfrence/900);
    drive.calculateWheelSpeeds(controller.calculateOut(), rtController.calculateOut(),maxRPM);
    runDriveValues();
    delay(10);
  }
  stopDrive(false);
}

void turnAngle(double angle, pidController rtController, double maxRPM= 600){
  inertial.tare();
  stopDrive(false);
  rtController.resetID();
  int initialT = millis();
  rtController.tVal = angle;
  rtController.error = angle - inertial.get_rotation();
  lcd::print(2, std::to_string(inertial.get_rotation()).c_str());
  while(!rtController.withinTarget()){
    lcd::print(2, std::to_string(inertial.get_rotation()).c_str());
    rtController.update(inertial.get_rotation());
    drive.calculateWheelSpeeds(0, 3*rtController.calculateOut(), maxRPM);
    runDriveValues();
    delay(10);
  }
  stopDrive(false);
}
