#include "../include/main.h"
#include "../include/functions.h"


//Swap to pid Controller
std::shared_ptr<ChassisController> drive =
    ChassisControllerBuilder()
        .withMotors(FLPort,BLPort,FRPort,BRPort)
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

void skills(){
drive->moveDistance(9_in);

}
