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



void REDX(){
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
      {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
      {40_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
      "A" // Profile name
    );
profileController->generatePath({
      {40_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
      {0_in, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
      "B" // Profile name
    );
//driveauton->moveDistance(40_in);
profileController->setTarget("A");
delay(1600);
Clamp.move_relative(1000, 100);
delay(100);
driveauton->moveDistance(-40_in);
}
void skills(){

}
