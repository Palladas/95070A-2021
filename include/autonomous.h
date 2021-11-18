#include "../include/main.h"
#include "../include/functions.h"
std::shared_ptr<AsyncPositionController<double, double>> liftControl =
    AsyncPosControllerBuilder().withMotor(GHPort).build();
std::shared_ptr<AsyncPositionController<double, double>> fourbar =
    AsyncPosControllerBuilder().withMotor({FBRPort,-FBLPort}).build();

//This file has all of the autonomous
void disabledAuton(){

}

void pop(){

}

void Drive(){

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
  // green gearset, 4 inch wheel diameter, 15 inch wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 15_in}, imev5GreenTPR})
  .withOdometry() // use the same scales as the chassis (above)
  .buildOdometry(); // build an odometry chassis

  std::shared_ptr<ChassisController> driveautonnotpid =
  ChassisControllerBuilder()
  .withMotors({FLPort,BLPort},{FRPort,BRPort})
  .withMaxVelocity(200)

  // green gearset, 4 inch wheel diameter, 15 inch wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 15_in}, imev5GreenTPR})
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
Clamp.move_relative(5000, 100);
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
    // green gearset, 4 inch wheel diameter, 15 inch wheel track
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 15_in}, imev5GreenTPR})
    .withOdometry() // use the same scales as the chassis (above)
    .buildOdometry(); // build an odometry chassis

    std::shared_ptr<ChassisController> driveautonnotpid =
    ChassisControllerBuilder()
    .withMotors({FLPort,BLPort},{FRPort,BRPort})
    .withMaxVelocity(200)

    // green gearset, 4 inch wheel diameter, 15 inch wheel track
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 15_in}, imev5GreenTPR})
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
      
    Clamp.move_relative(1000, 200);
    delay(100);
    driverControl(-100, -100);
     delay(1000);
    Clamp.move_relative(-1000, 100);
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
  // green gearset, 4 inch wheel diameter, 15 inch wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 15_in}, imev5GreenTPR})
  .withOdometry() // use the same scales as the chassis (above)
  .buildOdometry(); // build an odometry chassis

  std::shared_ptr<ChassisController> driveautonnotpid =
  ChassisControllerBuilder()
  .withMotors({FLPort,BLPort},{FRPort,BRPort})
  .withMaxVelocity(200)

  // green gearset, 4 inch wheel diameter, 15 inch wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 15_in}, imev5GreenTPR})
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
    driveauton->moveDistance(25_in);
    Clamp.move_relative(5000, 10);
    delay(1000);
    driveauton->moveDistance(-20_in);
    delay(300);
    Clamp.move_relative(-1000,50);
    delay(200);
    driveauton->turnAngle(180_deg);


}
void skills(){

}

void TEST_GO_1() {
  std::shared_ptr<ChassisController> driveauton =
    ChassisControllerBuilder()
    .withMotors({FLPort,BLPort},{FRPort,BRPort})
    .withGains(
    {0.002, 0, 0.0001}, // Distance controller gains
    {0.001, 0, 0.0001} // Turn controller gains
    )
    .withMaxVelocity(150)
    .withDerivativeFilters(
          std::make_unique<AverageFilter<3>>()
      )
    // green gearset, 4 inch wheel diameter, 15 inch wheel track
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 16_in}, imev5GreenTPR})
    .withOdometry() // use the same scales as the chassis (above)
    .buildOdometry(); // build an odometry chassis

  std::shared_ptr<ChassisController> driveautonnotpid =
  ChassisControllerBuilder()
  .withMotors({FLPort,BLPort},{FRPort,BRPort})
  .withMaxVelocity(120)
  // green gearset, 4 inch wheel diameter, 15 inch wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 16_in}, imev5GreenTPR})
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

  // Target location path
  profileController->generatePath({
      {58_in, 0_in, 0_deg},
      {0_ft, 0_ft, 0_deg}},
      "first_move"
  );
  profileController->generatePath({
      {50_in, 0_in, 0_deg},
      {0_ft, 0_ft, 0_deg}},
      "retreat"
  );

profileController->setTarget("first_move",true);
delay(10);
Clamp.move_relative(2500, 50);
delay(6000);
profileController->setTarget("first_move",false);



}

void TEST_GO_2() {
  std::shared_ptr<ChassisController> driveauton =
    ChassisControllerBuilder()
    .withMotors({FLPort,BLPort},{FRPort,BRPort})
    .withGains(
    {0.002, 0, 0.0001}, // Distance controller gains
    {0.001, 0, 0.0001} // Turn controller gains
    )
    .withMaxVelocity(150)
    .withDerivativeFilters(
          std::make_unique<AverageFilter<3>>()
      )
    // green gearset, 4 inch wheel diameter, 15 inch wheel track
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 16_in}, imev5GreenTPR})
    .withOdometry() // use the same scales as the chassis (above)
    .buildOdometry(); // build an odometry chassis

  std::shared_ptr<ChassisController> driveautonnotpid =
  ChassisControllerBuilder()
  .withMotors({FLPort,BLPort},{FRPort,BRPort})
  .withMaxVelocity(120)
  // green gearset, 4 inch wheel diameter, 15 inch wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 16_in}, imev5GreenTPR})
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

  // Target location path
  profileController->generatePath({
      {54_in, 0_in, 0_deg},
      {0_ft, 0_ft, 0_deg}},
      "first_move"
  );
  profileController->generatePath({
      {0_ft, 0_ft, 0_deg},
      {50_in, 0_in, 0_deg}},
      "run_home"
  );

profileController->setTarget("first_move",true);
GHold.move_relative(7500, 10);
delay(3000);
driveauton->turnAngle(90_deg);
delay(500);
driveauton->moveDistance(36_in);
delay(300);
driveauton->turnAngle(270_deg);
Clamp.move_relative(5000,10);
driveauton->moveDistance(-20_in);
}

void TEST_GO_3() {
  std::shared_ptr<ChassisController> driveauton =
    ChassisControllerBuilder()
    .withMotors({FLPort,BLPort},{FRPort,BRPort})
    .withGains(
    {0.002, 0, 0.0001}, // Distance controller gains
    {0.001, 0, 0.0001} // Turn controller gains
    )
    .withMaxVelocity(150)
    .withDerivativeFilters(
          std::make_unique<AverageFilter<3>>()
      )
    // green gearset, 4 inch wheel diameter, 15 inch wheel track
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 16_in}, imev5GreenTPR})
    .withOdometry() // use the same scales as the chassis (above)
    .buildOdometry(); // build an odometry chassis

  std::shared_ptr<ChassisController> driveautonnotpid =
  ChassisControllerBuilder()
  .withMotors({FLPort,BLPort},{FRPort,BRPort})
  .withMaxVelocity(100)
  // green gearset, 4 inch wheel diameter, 15 inch wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 16_in}, imev5GreenTPR})
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

  // Target location path
  profileController->generatePath({
      {54_in, 0_in, 0_deg},
      {0_ft, 0_ft, 0_deg}},
      "first_move"
  );
  profileController->generatePath({
      {0_ft, 0_ft, 0_deg},
      {50_in, 0_in, 0_deg}},
      "run_home"
  );

GHold.move_relative(2500, 10);
delay(1000);

driveauton->moveDistance(72_in);
GHold.move_relative(-2500,10);
delay(100);
driveauton->moveDistance(-24_in);
driveauton->turnAngle(225_deg);
delay(500);
driveauton->moveDistance(27_in);
Clamp.move_relative(5000,10);
driveauton->moveDistance(20_in);
}
