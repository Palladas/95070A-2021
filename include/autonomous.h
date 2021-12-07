#include "../include/main.h"
#include "../include/functions.h"
std::shared_ptr<AsyncPositionController<double, double>> liftControl =
    AsyncPosControllerBuilder().withMotor(PBPort).build();
std::shared_ptr<AsyncPositionController<double, double>> fourbar =
    AsyncPosControllerBuilder().withMotor({FBRPort,-FBLPort}).build();
    std::shared_ptr<ChassisController> turndrive =
    ChassisControllerBuilder()
    .withMotors({FLPort,BLPort},{FRPort,BRPort})
    .withMaxVelocity(200)
    .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 13.5_in}, imev5GreenTPR})
    .build();




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
Clamp.move_relative(1000, 100);
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
  Clamp.move_relative(1000, 100);
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
  Clamp.move_absolute(0, 100);
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
  Clamp.move_absolute(1000, 100);
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
Clamp.move_relative(1000, 100);
delay(100);
profileController->generatePath({
      {0_ft, 0_ft, 0_deg},
      {15_in, 0_ft, 0_deg}},
      "Gotoamogo"
    );
profileController->setTarget("Gotoamogo",true);
delay(800);
delay(100);
Clamp.move_absolute(0,100);
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
  Clamp.move_relative(1000, 100);
  delay(100);
  profileController2->generatePath({
        {0_ft, 0_ft, 0_deg},
        {12_in, 0_ft, 0_deg}},
        "plz"
      );
  profileController2->setTarget("plz",true);
   delay(800);
  Clamp.move_relative(-1000, -100);
  delay(15000);
}

void SNUMOGO(){
  driveForward(80, autonlinear,0,autonrotation);
  delay(100);
  Clamp.move_relative(1000, 100);
  driveForward(-60, autonlinear);
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
driveForward(80, autonlinear,0,autonrotation);
Clamp.move_relative(1000, 100);
delay(100);
driveForward(-60, autonlinear,0,autonrotation);
fourbarmove(200);
delay(500);
fourbarmove(0);
turnAngle(90,autonrotation);
Clamp.move_absolute(0, 100);
turnAngle(-132,autonrotation);
fourbarmove(-200);
delay(500);
fourbarmove(0);
driveForward(60, autonlinear,0,autonrotation);
Clamp.move_absolute(1000, 100);
delay(200);
driveForward(-80, autonlinear,0,autonrotation);
}


void skills(){

}
