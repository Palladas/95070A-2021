#include "driveTrain.h"
#include "main.h"
#include "pid.h"

using namespace pros;

const double ticksPerDeg = 900 / 360;
const double robotSpeed = 200;
const double rotationSpeed = 200;

extern pros::Motor FrontLeft;
extern pros::Motor FrontRight;
extern pros::Motor BackLeft;
extern pros::Motor BackRight;

// Ports
const int FLPort = 17;
const int FRPort = 7;
const int MLPort = 18;
const int MRPort = 2;
const int BLPort = 9;
const int BRPort = 10;
const int FBRPort = 8;
const int CPort = 4;
const int IMUPort = 13;
const int ConvPort = 1;
const int FDistPort = 4;
const int BDistPort = 5;

pros::Controller control(pros::E_CONTROLLER_MASTER);

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

pros::Motor FrontLeft(FLPort, MOTOR_GEARSET_06, true);
pros::Motor FrontRight(FRPort, MOTOR_GEARSET_06, false);
pros::Motor MidLeft(MLPort, MOTOR_GEARSET_06, false);
pros::Motor MidRight(MRPort, MOTOR_GEARSET_06, true);
pros::Motor BackLeft(BLPort, MOTOR_GEARSET_06, true);
pros::Motor BackRight(BRPort, MOTOR_GEARSET_06, false);

pros::Motor Clamp(CPort, E_MOTOR_GEARSET_36, false);
pros::Motor Rings(ConvPort, MOTOR_GEARSET_06, true);

pros::Motor FBarR(FBRPort, E_MOTOR_GEARSET_36, false);

pros::Imu inertial(IMUPort);
pros::Distance frontDist(FDistPort);
pros::Distance backDist(BDistPort);

pros::ADIEncoder Left_Enc('G', 'F');
pros::ADIEncoder Right_Enc('E', 'F');

pros::ADIDigitalOut piston('A', true);
pros::ADIDigitalOut piston2('B', false);
pros::ADIDigitalOut piston3('C', false);

driveTrain drive = driveTrain(3.25, 11.5);
pidController autonlinear = pidController(0, 0.002, 0, 0.0001);
pidController autonrotation = pidController(0, 0.001, 0, 0.0001);
pidController skillslinear = pidController(0, 0.45, 0.0, 5);
pidController skillsrotation = pidController(0, 1, 0, 1);

void calibrateSensors() {
  lcd::print(1, "Calibrating");
  inertial.reset();

  int timeInit = millis();

  inertial.reset();
  while (inertial.is_calibrating()) {
    lcd::print(1, "Calibrating");
    delay(10);
  }
  delay(2000);
  lcd::print(1, "Calibration took %f", millis() - timeInit);

  autonlinear.tolerance = 0.2;
}
