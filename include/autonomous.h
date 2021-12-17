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


  std::shared_ptr<AsyncMotionProfileController> profileController2 =
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      1.0,
      2.0,
      10.0
    })
    .withOutput(driveauton)
    .buildMotionProfileController();
  profileController2->generatePath({
        {0_ft, 0_ft, 0_deg},
        {6_in, 0_ft, 0_deg}},
        "test"
      );
    profileController2->setTarget("test");
  delay(860);
  piston.set_value(true);
  delay(100);
  profileController2->generatePath({
        {0_ft, 0_ft, 0_deg},
        {12_in, 0_ft, 0_deg}},
        "plz"
      );
  profileController2->setTarget("plz",true);
   delay(800);
piston.set_value(false);
  delay(15000);
}

void SNUMOGO(){
  piston.set_value(false);
  driveForward(40, autonlinear,0,autonrotation);
  delay(100);
  piston.set_value(true);
  driveForward(-30, autonlinear);
}
void STWOMOGO(){
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
piston2.set_value(false);
piston2.set_value(true);
piston.set_value(false);
driveForward(40, autonlinear,0,autonrotation);
piston.set_value(true);
delay(100);
driveForward(-20, autonlinear,0,autonrotation);
fourbarmove(200);
delay(500);
fourbarmove(0);
driveauton->turnAngle(90_deg);
piston.set_value(false);
driveauton->turnAngle(-132_deg);
fourbarmove(-200);
delay(500);
fourbarmove(0);
driveForward(30, autonlinear,0,autonrotation);
piston.set_value(true);
delay(200);
driveForward(-40, autonlinear,0,autonrotation);
}

void twoGoal(){
  driveForward(28, autonlinear,0,autonrotation);
  piston2.set_value(false);
  driveForward(-30, autonlinear);
  piston2.set_value(true);
}


void skills(){

}
