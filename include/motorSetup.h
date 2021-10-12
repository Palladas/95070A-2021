#include "main.h"



const double ticksPerDeg = 900/360;
//200*4.125*pi/60 * sqrt(2), = 60
const double robotSpeed = 43.196 * sqrt(2);
const double rotationSpeed = 200;

extern Motor FrontLeft;
extern Motor FrontRight;
extern Motor BackLeft;
extern Motor BackRight;
extern Motor LeftIntake;
extern Motor RightIntake;

//Ports
const int FLPort = 1;
const int FRPort = 4;
const int BLPort = 16;
const int BRPort = 20;
const int PBPort = 8;

Controller master;

pros::Controller control (pros::E_CONTROLLER_MASTER);

ControllerButton RUp(ControllerDigital::R1);
ControllerButton RDown(ControllerDigital::R2);
ControllerButton A(ControllerDigital::A);
ControllerButton B(ControllerDigital::B);
ControllerButton X(ControllerDigital::X);
ControllerButton Y(ControllerDigital::Y);
ControllerButton LUp(ControllerDigital::L1);
ControllerButton LDown(ControllerDigital::L2);
ControllerButton left(ControllerDigital::left);
ControllerButton right(ControllerDigital::right);
ControllerButton up(ControllerDigital::up);
ControllerButton down(ControllerDigital::down);
/*
pros::Controller control (E_CONTROLLER_MASTER);
pros::Motor FrontLeft(FLPort, true);
pros::Motor FrontRight(FRPort, true);
pros::Motor BackLeft(BLPort, true);
pros::Motor BackRight(BRPort, false);
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
