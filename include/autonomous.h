#include "main.h"
#include "functions.h"


//Swap to pid Controller
std::shared_ptr<ChassisController> drive =
    ChassisControllerBuilder()
        .withMotors(FLPort,-BLPort, FRPort,-BRPort)
        // Green gearset, 4 in wheel diam, 11.5 in wheel track
        .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, okapi::imev5GreenTPR})
        .build();
std::shared_ptr<AsyncPositionController<double, double>> liftControl =
    AsyncPosControllerBuilder().withMotor(PBPort).build();

//This file has all of the autonomous
void disabledAuton(){

}

void pop(){

}

void skills(){
  // Move 1 meter to the first goal
drive->moveDistance(1_m);
// Turn 90 degrees to face second goal
drive->turnAngle(90_deg);
// Drive 1 and a half feet toward second goal
drive->moveDistance(1.5_ft);
}
