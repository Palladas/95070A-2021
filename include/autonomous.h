#include "../include/main.h"
#include "../include/functions.h"





void disabledAuton(){

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
    inertial.tare();
  piston.set_value(false);
  driveForward(35, autonlinear,0,autonrotation);
  delay(100);
  piston.set_value(true);
  driveForward(-5, autonlinear);
  turnAngle(110, autonrotation);
  Clamp.move_relative(4200, 100);
  delay(1000);
  driveForward(-25, autonlinear);
  Clamp.move_absolute(0, -100);
  driveauton->turnAngle(60_deg);
  driveForward(30, autonlinear);
}


void AWP1(){
  FBarR.move_absolute(1600, 100);
  delay(1000);
  driveForward(5, autonlinear,0,autonrotation,100);
  piston.set_value(true);
  delay(500);
  driveForward(-5, autonlinear,0,autonrotation,100);
  FBarR.move_absolute(0,100);
  delay(1000);
  driveForward(8, autonlinear,0,autonrotation,100);
  piston.set_value(false);
  driveForward(-13, autonlinear,0,autonrotation,100);
  piston.set_value(true);
}
void AWP2(){
  Clamp.move_relative(3000, 50);
  delay(3000);
  driveForward(-20, autonlinear,0,autonrotation, 50);
  delay(1000);
  driveForward(20, autonlinear,0,autonrotation,50);
}

void goalCover(void* param){
  piston3.set_value(true);
  delay(100);
  piston.set_value(true);
}

void SNUMOGO(){
  inertial.tare();
  Task goal_cover(goalCover);
  driveForward(31, autonlinear,0,autonrotation);
  delay(100);
  piston.set_value(false);
  FBarR.move_relative(1400,100);
  driveForward(-17, autonlinear);
  delay(800);
  holdAll();
  turnAngle(-90,autonlinear,3000);
  coastAll();
  piston2.set_value(true);
  driveForward(-12,autonlinear,200);
  piston2.set_value(false);
  delay(500);
  Rings.move_velocity(1200);
  driveForward(20,autonlinear,200);
  Rings.move(0);
  piston2.set_value(true);
}

void STWOMOGO(){
  inertial.tare();
  piston.set_value(true);
  Clamp.move_relative(3000, 50);
  driveForward(35, autonlinear,0,autonrotation);
  piston.set_value(false);
  delay(100);
  FBarR.move_absolute(1400, -100);
  driveForward(-15, autonlinear,0,autonrotation);
  turnAngle(110, autonrotation);
  delay(200);
  driveForward(-33, autonlinear,0,autonrotation);
  Clamp.move_absolute(2000,-100);
  turnAngle(10, autonrotation);
  driveForward(55, autonlinear,0,autonrotation);

}

 void piston_fire(void* param) {
     delay(500);
     piston2.set_value(true);
     delay(400);
     piston2.set_value(false);
     // ...
 }

void wings(){
  Task my_task(piston_fire);
  driveForwardVoltage(35, autonlinear,60,autonrotation);
  delay(100);
  driveForwardVoltage(-25, skillslinear,60,autonrotation);
  piston2.set_value(true);
  driveForward(-5,autonlinear,0,autonrotation);
  piston2.set_value(false);

  
  
}

void leftGoal(){
  inertial.tare();
  piston.set_value(true);
  driveForward(33, autonlinear,0,autonrotation);
  delay(100);
  piston.set_value(false);
  driveForward(-33, autonlinear);
}

void solowinpoint(){
  holdAll();
  FBarR.move_absolute(1600, 100);
  driveForward(12, skillslinear,0, autonrotation, 100);
  piston.set_value(true);
  delay(500);
  driveForward(-10, skillslinear,0, autonrotation, 100);
  FBarR.move_absolute(0, -100);
  turnAngle(90, skillsrotation,1000);
  driveForward(-20, skillslinear,0, autonrotation, 200);
  delay(300);
  inertial.tare();
  turnAngle(90, skillsrotation,1000);
  driveForward(-60, skillslinear, 400);
  Clamp.move_relative(3000, 100);
  delay(1500);
  driveForward(-28, skillslinear, 300);
  delay(500);
  Clamp.move_absolute(2000, -100);
  driveForward(20, skillslinear, 300);
  Clamp.move_absolute(3000, 100);
  driveForward(10, skillslinear, 300);
  coastAll();
}


void skills(){
  holdAll();
  int skills_speed = 150;
  piston.set_value(true);
  Clamp.move_relative(3000,100);
  delay(2000);
  driveForward(-24, skillslinear,0, skillslinear, skills_speed);
  Clamp.move_absolute(0,100);
  delay(1000);
  driveForward(12, skillslinear,0, skillslinear, 50);
  turnAngle(90,skillslinear,200);
  driveForward(60, skillslinear,0, skillslinear, 50);
  piston.set_value(false);
  FBarR.move_absolute(6000,-100);
  driveForward(-36, skillslinear,0, skillslinear, 50);
  turnAngle(90,skillslinear,200);
  driveForward(36, skillslinear,0, skillslinear, 50);
  turnAngle(90,skillslinear,100);
  driveForward(12, skillslinear,0, skillslinear, 50);
  piston.set_value(true);
  driveForward(-6, skillslinear,0, skillslinear, 50);
  FBarR.move_absolute(0,100);
  turnAngle(-90,skillslinear,100);
  driveForward(30, skillslinear,0, skillslinear, 50);
  turnAngle(-90,skillslinear,100);
  driveForward(36, skillslinear,0, skillslinear, 50);
  piston.set_value(false);
  FBarR.move_relative(6000,-100);
  driveForward(-36, skillslinear,0, skillslinear, 50);
  turnAngle(-90,skillslinear,100);
  driveForward(36, skillslinear,0, skillslinear, 50);
  turnAngle(-90,skillslinear,100);
  driveForward(12, skillslinear,0, skillslinear, 50);
  piston.set_value(true);
  driveForward(-12, skillslinear,0, skillslinear, 50);
  FBarR.move_absolute(0,100);
  turnAngle(-90,skillslinear,100);
  driveForward(36, skillslinear,0, skillslinear, 50);
  turnAngle(-90,skillslinear,100);
  driveForward(84, skillslinear,0, skillslinear, 50);
  turnAngle(90,skillslinear,100);
  driveForward(12, skillslinear,0, skillslinear, 50);
  turnAngle(-90,skillslinear,100);
  driveForward(12, skillslinear,0, skillslinear, 50);
  turnAngle(-90,skillslinear,100);
  driveForward(24, skillslinear,0, skillslinear, 50);
  piston.set_value(false);
  driveForward(-12, skillslinear,0, skillslinear, 50);
  FBarR.move_relative(6000,-100);
  turnAngle(-90,skillslinear,100);
  driveForward(96, skillslinear,0, skillslinear, 50);
  turnAngle(90,skillslinear,100);
  driveForward(36, skillslinear,0, skillslinear, 50);
  turnAngle(-90,skillslinear,100);
  driveForward(12, skillslinear,0, skillslinear, 50);
  piston.set_value(true);
  coastAll();
}

void test(){
  holdAll();
  driveForward(24,skillslinear,0,skillslinear);
  coastAll();
}
