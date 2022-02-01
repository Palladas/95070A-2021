#include "../include/main.h"
#include "../include/functions.h"





void disabledAuton(){

}

void pop(){

}



void NUMOGO(){
  std::shared_ptr<ChassisController> driveauton =
      ChassisControllerBuilder()
      .withMotors({FLPort,BLPort},{FRPort,BRPort})
      .withGains(
      {0.002, 0, 0.0001},
      {0.001, 0, 0.0001}
      )
      .withMaxVelocity(200)

      .withDerivativeFilters(
            std::make_unique<AverageFilter<3>>()
        )
      .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
      .withOdometry()
      .buildOdometry();

      std::shared_ptr<AsyncMotionProfileController> profileController =
          AsyncMotionProfileControllerBuilder()
            .withLimits({
              1.0,
              2.0,
              10.0
            })
            .withOutput(driveauton)
            .buildMotionProfileController();

	profileController->generatePath({
			  {0_ft, 0_ft, 0_deg},
			  {40_in, 0_ft, 0_deg}},
			  "Gotonumogo"
	);
profileController->setTarget("Gotonumogo");
delay(1600);
piston.set_value(true);
delay(100);
profileController->generatePath({
      {0_ft, 0_ft, 0_deg},
      {35_in, 0_ft, 0_deg}},
      "Gotoamogo"
    );
profileController->setTarget("Gotoamogo",true);
delay(800);
delay(100);
delay(15000);
}

void TWONUMOGO(){
  std::shared_ptr<ChassisController> driveauton =
      ChassisControllerBuilder()
      .withMotors({FLPort,BLPort},{FRPort,BRPort})
      .withGains(
      {0.002, 0, 0.0001},
      {0.001, 0, 0.0001}
      )
      .withMaxVelocity(200)

      .withDerivativeFilters(
            std::make_unique<AverageFilter<3>>()
        )
      .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
      .withOdometry()
      .buildOdometry();
    inertial.tare();
  piston.set_value(false);
  driveForward(35, autonlinear,0,autonrotation);
  delay(100);
  piston.set_value(true);
  driveForward(-5, autonlinear);
  turnAngle(110, autonrotation);
  Clamp.move_relative(4200, 100);
  delay(1000);
  driveForward(-25, autonlinear);
  Clamp.move_absolute(0, -100);
  driveauton->turnAngle(60_deg);
  driveForward(30, autonlinear);
}


void AWP1(){
  FBarR.move_absolute(-1600, 100);
  delay(1000);
  driveForward(5, autonlinear,0,autonrotation,100);
  piston.set_value(true);
  delay(500);
  driveForward(-5, autonlinear,0,autonrotation,100);
  FBarR.move_absolute(0,100);
  delay(1000);
  driveForward(8, autonlinear,0,autonrotation,100);
  piston.set_value(false);
  driveForward(-13, autonlinear,0,autonrotation,100);
  piston.set_value(true);
}
void AWP2(){
  Clamp.move_relative(3000, 50);
  delay(3000);
  driveForward(-20, autonlinear,0,autonrotation, 50);
  delay(1000);
  driveForward(20, autonlinear,0,autonrotation,50);
}

void SNUMOGO(){
  inertial.tare();
  piston.set_value(true);
  driveForward(33, autonlinear,0,autonrotation);
  delay(100);
  piston.set_value(false);
  FBarR.move_relative(1400,100);
  driveForward(-25, autonlinear);
  turnAngle(-63, autonrotation);
  driveForward(10, autonlinear);
  piston.set_value(true);
  Clamp.move_relative(3000, 50);
  delay(2000);
  driveForward(-24, autonlinear,0, autonrotation, 200);
  Clamp.move_relative(-1000, 100);
  delay(300);
  driveForward(10, autonlinear);
  turnAngle(90, autonrotation);
  Clamp.move_relative(1200, 100);
  delay(1000);
  driveForward(10, autonlinear);
  Clamp.move_absolute(0, -100);
}

void STWOMOGO(){
inertial.tare();
piston.set_value(true);
Clamp.move_relative(3000, 50);
driveForward(35, autonlinear,0,autonrotation);
piston.set_value(false);
delay(100);
FBarR.move_absolute(1400, -100);
driveForward(-15, autonlinear,0,autonrotation);
turnAngle(110, autonrotation);
delay(200);
driveForward(-33, autonlinear,0,autonrotation);
Clamp.move_absolute(2000,-100);
turnAngle(10, autonrotation);
driveForward(55, autonlinear,0,autonrotation);

}

void wiiings(){
  inertial.tare();
  piston.set_value(true);
  driveForward(33, autonlinear,0,autonrotation);
  delay(100);
  piston.set_value(false);
  driveForward(-33, autonlinear);
}

void solowinpoint(){
  FrontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  FrontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  MidLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  MidRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  FBarR.move_absolute(-1600, 100);
  driveForward(10, autonlinear,0, autonrotation, 100);
  piston.set_value(true);
  delay(500);
  driveForward(-5, autonlinear,0, autonrotation, 100);
  FBarR.move_absolute(0, -100);
  turnAngle(70, autonrotation);
  driveForward(-13, autonlinear,0, autonrotation, 200);
  delay(300);
  inertial.tare();
  turnAngle(70, autonrotation);
  driveForward(-70, autonlinear, 400);
  Clamp.move_relative(3000, 100);
  delay(1000);
  driveForward(-23, autonlinear, 300);
  delay(500);
  Clamp.move_absolute(2000, -100);
  driveForward(20, autonlinear, 300);
  Clamp.move_absolute(3000, 100);
  driveForward(10, autonlinear, 300);

}

void skills(){
driveForward(75, autonlinear,0,autonrotation,600);

}
