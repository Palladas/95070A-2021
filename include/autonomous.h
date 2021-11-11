#include "../include/main.h"
#include "../include/functions.h"

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
std::shared_ptr<AsyncPositionController<double, double>> liftControl =
    AsyncPosControllerBuilder().withMotor(GHPort).build();
std::shared_ptr<AsyncPositionController<double, double>> fourbar =
    AsyncPosControllerBuilder().withMotor({FBRPort,-FBLPort}).build();

//This file has all of the autonomous
void disabledAuton(){

}

void pop(){

}



void NUMOGO(){
  //gets neutral mobile goal in front of bot
profileController->generatePath({
      {0_ft, 0_ft, 0_deg},
      {40_in, 0_ft, 0_deg}},
      "Gotonumogo"
    );

//driveauton->moveDistance(40_in);
profileController->setTarget("Gotonumogo");
delay(1600);
Clamp.move_relative(1000, 100);
delay(100);
driveauton->moveDistance(-40_in);
delay(15000);
}

void AWP1(){
  //makes mogo clear AWP line, scores ring on it
  profileController->generatePath({
        {0_ft, 0_ft, 0_deg},
        {20_in, 0_ft, 0_deg}},
        "Gotoamogo"
      );
      profileController->generatePath({
            {0_ft, 0_ft, 0_deg},
            {20_in, 0_ft, 0_deg}},
            "return"
          );
  profileController->setTarget("Gotoamogo");
  delay(860);
  Clamp.move_relative(1000, 100);
  delay(100);
  driveauton->moveDistance(-20_in);
  delay(800);
  Clamp.move_relative(-1000, -100);
  delay(15000);
}
void AWP2(){
  //scores ring inside alliance mobile goal that is on the platform
  profileController->generatePath({
        {0_ft, 0_ft, 0_deg},
        {6_in, 0_ft, 0_deg}},
        "Gotoamogo"
      );
      profileController->generatePath({
            {0_ft, 0_ft, 0_deg},
            {20_in, 0_ft, 0_deg}},
            "return"
          );
  profileController->setTarget("Gotoamogo");
  delay(860);
  Clamp.move_relative(1000, 100);
  delay(100);
  driveauton->moveDistance(-6_in);
  delay(800);
  Clamp.move_relative(-1000, -100);
  delay(15000);
}
void skills(){
  profileController->generatePath({
        {0_ft, 0_ft, 0_deg},
        {20_in, 0_ft, 0_deg}},
        "test"
      );
    profileController->setTarget("test",true);
}
