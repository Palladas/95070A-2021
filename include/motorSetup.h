#include "main.h"

using namespace pros;

const double ticksPerDeg = 900/360;
//200*4.125*pi/60 * sqrt(2), = 60
const double robotSpeed = 43.196 * sqrt(2);
const double rotationSpeed = 200;

extern pros::Motor FrontLeft;
extern pros::Motor FrontRight;
extern pros::Motor BackLeft;
extern pros::Motor BackRight;


//Ports
const int FLPort = 3;
const int FRPort = 7;
const int BLPort = 11;
const int BRPort = 5;
const int PBPort = 10;
const int FBRPort = 8;
const int FBLPort = 9;
const int CPort = 12;


pros::Controller control (pros::E_CONTROLLER_MASTER);

ControllerButton RUp(ControllerDigital::R1);
ControllerButton RDown(ControllerDigital::R2);
ControllerButton A(ControllerDigital::A);
ControllerButton B(ControllerDigital::B);
ControllerButton X(ControllerDigital::X);
ControllerButton Y(ControllerDigital::Y);
ControllerButton left(ControllerDigital::left);
ControllerButton right(ControllerDigital::right);
ControllerButton up(ControllerDigital::up);
ControllerButton down(ControllerDigital::down);
/*
pros::Controller control (E_CONTROLLER_MASTER);*/
pros::Motor Clamp(CPort, false);

pros::Motor FrontLeft(FLPort, true);
pros::Motor FrontRight(FRPort, false);
pros::Motor BackLeft(BLPort, true);
pros::Motor BackRight(BRPort, false);
pros::Motor FBarR(FBRPort, false);
pros::Motor FBarL(FBLPort, true);

/*
pros::Motor LeftIntake(LIPort, false);
pros::Motor RightIntake(RIPort, true);
pros::Motor BackRoller(LRPort, true);
pros::Motor MainRoller(RRPort, true);
pros::Imu inertial(IMUPort);

ADIEncoder yWheel('C', 'D', true);
ADIEncoder xWheel('A', 'B', false);


//Calibrate the sensors
void calibrateSensors(){
  xWheel.reset();
  yWheel.reset();
  inertial.reset();

  int timeInit = pros::millis();

  inertial.reset();
  while(inertial.is_calibrating()){
    lcd::print(1, "Calibrating");
    delay(10);
  }
  delay(2000);
  lcd::print(1, "Calibration took %f", millis() - timeInit);
}*/
