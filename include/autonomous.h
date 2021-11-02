#include "../include/main.h"
#include "../include/functions.h"


//Swap to pid Controller
std::shared_ptr<ChassisController> drive =
    ChassisControllerBuilder()
        .withMotors(FLPort,BLPort,FRPort,BRPort)
        .withGains(
        {0.001, 0, 0.0001}, // Distance controller gains
        {0.001, 0, 0.0001}, // Turn controller gains
        {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
    )
        // Green gearset, 4 in wheel diam, 11.5 in wheel track
        .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, okapi::imev5GreenTPR})
        .build();
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
.withMotors(FLPort,BLPort,FRPort,BRPort) // left motor is 1, right motor is 2 (reversed)
// green gearset, 4 inch wheel diameter, 11.5 inch wheel track
.withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
.withOdometry() // use the same scales as the chassis (above)
.buildOdometry(); // build an odometry chassis


driveauton->moveDistance(40_in);
Clamp.move_relative(1000, 100);
delay(1000);
driveauton->moveDistance(-30_in);

}
void skills(){

}
