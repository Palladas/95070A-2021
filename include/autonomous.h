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
      {15_in, 0_ft, 0_deg}},
      "Gotonumogo"
    );
    profileController->generatePath({
          {0_ft, 0_ft, 0_deg},
          {20_in, 0_ft, 0_deg}},
          "return"
        );
profileController->setTarget("Gotonumogo");
delay(1600);
piston.set_value(true);
delay(100);
profileController->generatePath({
      {0_ft, 0_ft, 0_deg},
      {15_in, 0_ft, 0_deg}},
      "Gotoamogo"
    );
profileController->setTarget("Gotoamogo",true);
delay(800);
delay(100);
piston.set_value(false);
delay(15000);
}
void AWP2(){
  FBarR.move_absolute(800, 100);
  driveForward(15,autonlinear);
  piston.set_value(false);
  driveForward(-5, autonlinear);
  FBarR.move_absolute(0, -100);
}

void SNUMOGO(){
  inertial.tare();
  piston.set_value(true);
  driveForward(35, autonlinear,0,autonrotation);
  delay(100);
  piston.set_value(false);
  FBarR.move_relative(1400,100);
  driveForward(-25, autonlinear);
  turnAngle(-60, autonrotation);
  driveForward(10, autonlinear);
  Clamp.move_relative(3000, 50);
  delay(2000);
  driveForward(-24, autonlinear);
  piston.set_value(true);
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
piston2.set_value(false);
piston.set_value(false);
driveForward(40, autonlinear,0,autonrotation);
piston.set_value(true);
delay(100);
FBarR.move_absolute(700, 100);
driveForward(-20, autonlinear,0,autonrotation);
turnAngle(48, autonrotation);
piston.set_value(false);
FBarR.move_absolute(0, -100);
delay(200);
turnAngle(-25, autonrotation);
driveForward(33, autonlinear,0,autonrotation);
piston.set_value(true);
driveForward(-40, autonlinear,0,autonrotation);
}

void wiiings(){
  inertial.tare();
  piston.set_value(false);
  driveForward(35, autonlinear,0,autonrotation);
  delay(100);
  piston.set_value(true);
  driveForward(-40, autonlinear);
}

void solowinpoint(){
  FBarR.move_absolute(800, 100);
  driveForward(15,autonlinear);
  piston.set_value(false);
  driveForward(-5, autonlinear);
  FBarR.move_absolute(0, -100);
  turnAngle(87, autonrotation);
  driveForward(-12, autonlinear);
  delay(1000);
  inertial.tare();
  turnAngle(87, autonrotation);
  driveForward(-100, autonlinear);
  Clamp.move_relative(2500, 100);
  delay(1000);
  driveForward(20, autonlinear);
  Clamp.move_absolute(0, -100);
}

void skills(){

}
