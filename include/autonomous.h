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

    std::shared_ptr<AsyncMotionProfileController> profileController =
    AsyncMotionProfileControllerBuilder()
      .withLimits({
        1,
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
  delay(1700);
  piston.set_value(true);
  delay(100);
  profileController->generatePath({
        {0_ft, 0_ft, 0_deg},
        {35_in, 0_ft, 0_deg}},
        "return"
      );
  profileController->setTarget("return",true);
  delay(900);
  fourbarmove(200);
  delay(500);
  fourbarmove(0);
  driveauton->turnAngle(90_deg);
  piston.set_value(false);
  driveauton->turnAngle(-130_deg);
  fourbarmove(-200);
  delay(500);
  fourbarmove(0);
  profileController->generatePath({
        {0_ft, 0_ft, 0_deg},
        {30_in, 0_ft, 0_deg}},
        "return"
      );
  profileController->setTarget("return");
  delay(1300);
  piston.set_value(true);
  delay(200);
  profileController->generatePath({
        {0_ft, 0_ft, 0_deg},
        {50_in, 0_ft, 0_deg}},
        "return"
      );
  profileController->setTarget("return",true);
  delay(15000);
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
  piston.set_value(false);
  driveForward(35, autonlinear,0,autonrotation);
  delay(100);
  piston.set_value(true);
  driveForward(-20, autonlinear);
  turnAngle(-75, autonrotation);
  driveForward(-20, autonlinear);
  delay(300);
  Clamp.move_relative(2500, 100);
  delay(1000);
  driveForward(20, autonlinear);
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
turnAngle(-27, autonrotation);
driveForward(33, autonlinear,0,autonrotation);
piston.set_value(true);
driveForward(-40, autonlinear,0,autonrotation);
}

void wiiings(){
  driveForward(28, autonlinear,0,autonrotation);
  piston2.set_value(false);
  driveForward(-30, autonlinear);
  piston2.set_value(true);
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
