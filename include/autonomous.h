#include "../include/main.h"
#include "../include/functions.h"
std::shared_ptr<AsyncPositionController<double, double>> liftControl =
    AsyncPosControllerBuilder().withMotor(PBPort).build();
std::shared_ptr<AsyncPositionController<double, double>> fourbar =
    AsyncPosControllerBuilder().withMotor({FBRPort,-FBLPort}).build();

//This file has all of the autonomous
void disabledAuton(){

}

void pop(){

}



void NUMOGO(){

  std::shared_ptr<ChassisController> driveauton =
  ChassisControllerBuilder()
  .withMotors({FLPort,BLPort},{FRPort,BRPort})
  .withGains(
  {0.002, 0, 0.0001}, // Distance controller gains
  {0.001, 0, 0.0001} // Turn controller gains
  )
  .withMaxVelocity(200)

  .withDerivativeFilters(
        std::make_unique<AverageFilter<3>>()
    )
  // green gearset, 4 inch wheel diameter, 11.5 inch wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
  .withOdometry() // use the same scales as the chassis (above)
  .buildOdometry(); // build an odometry chassis

  std::shared_ptr<ChassisController> driveautonnotpid =
  ChassisControllerBuilder()
  .withMotors({FLPort,BLPort},{FRPort,BRPort})
  .withMaxVelocity(200)

  // green gearset, 4 inch wheel diameter, 11.5 inch wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
  .build(); // build an odometry chassis

  std::shared_ptr<AsyncMotionProfileController> profileController =
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      1.0, // Maximum linear velocity of the Chassis in m/s
      2.0, // Maximum linear acceleration of the Chassis in m/s/s
      10.0 // Maximum linear jerk of the Chassis in m/s/s/s
    })
    .withOutput(driveauton)
    .buildMotionProfileController();
profileController->generatePath({
      {0_ft, 0_ft, 0_deg},
      {40_in, 0_ft, 0_deg}},
      "Gotonumogo"
    );
    profileController->generatePath({
          {0_ft, 0_ft, 0_deg},
          {40_in, 0_ft, 0_deg}},
          "return"
        );
//driveauton->moveDistance(40_in);
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
Clamp.move_absolute(0, -100);
delay(100);
delay(15000);
}

void AWP1(){

    std::shared_ptr<ChassisController> driveauton =
    ChassisControllerBuilder()
    .withMotors({FLPort,BLPort},{FRPort,BRPort})
    .withGains(
    {0.002, 0, 0.0001}, // Distance controller gains
    {0.001, 0, 0.0001} // Turn controller gains
    )
    .withMaxVelocity(200)

    .withDerivativeFilters(
          std::make_unique<AverageFilter<3>>()
      )
    // green gearset, 4 inch wheel diameter, 11.5 inch wheel track
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
    .withOdometry() // use the same scales as the chassis (above)
    .buildOdometry(); // build an odometry chassis

    std::shared_ptr<ChassisController> driveautonnotpid =
    ChassisControllerBuilder()
    .withMotors({FLPort,BLPort},{FRPort,BRPort})
    .withMaxVelocity(200)

    // green gearset, 4 inch wheel diameter, 11.5 inch wheel track
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
    .build(); // build an odometry chassis

    std::shared_ptr<AsyncMotionProfileController> profileController2 =
    AsyncMotionProfileControllerBuilder()
      .withLimits({
        1.0, // Maximum linear velocity of the Chassis in m/s
        2.0, // Maximum linear acceleration of the Chassis in m/s/s
        10.0 // Maximum linear jerk of the Chassis in m/s/s/s
      })
      .withOutput(driveauton)
      .buildMotionProfileController();
    profileController2->generatePath({
          {0_ft, 0_ft, 0_deg},
          {20_in, 0_ft, 0_deg}},
          "test"
        );
      profileController2->setTarget("test");
    delay(860);
    Clamp.move_relative(1000, 100);
    delay(100);
    driverControl(-100, -100);
     delay(600);
     driverControl(0, 0);
    Clamp.move_relative(-1000, -100);
    delay(15000);
}
void AWP2(){

  std::shared_ptr<ChassisController> driveauton =
  ChassisControllerBuilder()
  .withMotors({FLPort,BLPort},{FRPort,BRPort})
  .withGains(
  {0.002, 0, 0.0001}, // Distance controller gains
  {0.001, 0, 0.0001} // Turn controller gains
  )
  .withMaxVelocity(200)

  .withDerivativeFilters(
        std::make_unique<AverageFilter<3>>()
    )
  // green gearset, 4 inch wheel diameter, 11.5 inch wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
  .withOdometry() // use the same scales as the chassis (above)
  .buildOdometry(); // build an odometry chassis

  std::shared_ptr<ChassisController> driveautonnotpid =
  ChassisControllerBuilder()
  .withMotors({FLPort,BLPort},{FRPort,BRPort})
  .withMaxVelocity(200)

  // green gearset, 4 inch wheel diameter, 11.5 inch wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
  .build(); // build an odometry chassis

  std::shared_ptr<AsyncMotionProfileController> profileController2 =
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      1.0, // Maximum linear velocity of the Chassis in m/s
      2.0, // Maximum linear acceleration of the Chassis in m/s/s
      10.0 // Maximum linear jerk of the Chassis in m/s/s/s
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
void skills(){

}
