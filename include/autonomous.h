#include "../include/functions.h"
#include "../include/main.h"
#include <cstdlib>

void disabledAuton() {}

void TWONUMOGO() {
  std::shared_ptr<ChassisController> driveauton =
      ChassisControllerBuilder()
          .withMotors({FLPort, BLPort}, {FRPort, BRPort})
          .withGains({0.002, 0, 0.0001}, {0.001, 0, 0.0001})
          .withMaxVelocity(200)

          .withDerivativeFilters(std::make_unique<AverageFilter<3>>())
          .withDimensions(AbstractMotor::gearset::green,
                          {{4_in, 11.5_in}, imev5GreenTPR})
          .withOdometry()
          .buildOdometry();
  inertial.tare();
  piston.set_value(false);
  driveForward(35, autonlinear, 0, autonrotation);
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

void goalCover(void *param) {
  piston.set_value(true);
  piston3.set_value(true);
}

void AWP1() {
  inertial.tare();
  piston2.set_value(true);
  delay(300);
  driveForward(-7, autonlinear,100);
  piston2.set_value(false);
  delay(100);
  driveForward(7, autonlinear,100);
  double currangle = inertial.get_rotation();
  while(abs(inertial.get_rotation()-currangle<97)){
    driverControl(300, 0);
  }
  Task clamp_task(goalCover);
  driveForwardBump(60,autonlinear,0,skillslinear);
  piston.set_value(false);
  driveForward(-27, skillslinear);
  FBarR.move_absolute(2000, 100);
  delay(300);
  Rings.move(600);
  delay(2000);
  Rings.move(0);
  delay(200);
  piston2.set_value(true);
}
void AWP2() {
  Clamp.move_relative(3000, 50);
  delay(3000);
  driveForward(-20, autonlinear, 0, autonrotation, 50);
  delay(1000);
  driveForward(20, autonlinear, 0, autonrotation, 50);
}



void VSNUMOGO() {
  inertial.tare();
  breakAll();
  Task clamp_task(goalCover);
  driveForwardBump(60,autonlinear,0,skillslinear);
  piston.set_value(false);
  driveForward(-27, skillslinear);
  piston2.set_value(true);
  delay(800);
  holdAll();
  FBarR.move_relative(2000, 100);
  turnAngleAbs(-90, autonlinear, 3000);
  coastAll();
  driveForward(-15, autonlinear,0,skillslinear,600,1300);
  piston2.set_value(false);
  FBarR.move_relative(600, 100);
  delay(500);
  Rings.move(400);
  turnAngleAbs(-90, autonlinear,3000);
  driveForwardPassive(30,autonlinear,200,2000);
  driveForward(-20,autonlinear,200);
  delay(500);
  driveForward(20,autonlinear,200);
  delay(1000);
  piston2.set_value(true);
  coastAll();
}

void SNUMOGO() {
  inertial.tare();
  Task clamp_task(goalCover);
  driveForwardBump(28.5, autonlinear,0,skillslinear);
  delay(200);
  piston.set_value(false);
  delay(100);
  driveForward(-27, skillslinear);
  piston2.set_value(true);
  delay(800);
  holdAll();
  FBarR.move_relative(1800, 100);
  turnAngleAbs(-90, autonlinear, 3000);
  coastAll();
  driveForward(-15, autonlinear);
  piston2.set_value(false);
  delay(500);
  Rings.move(400);
  driveForward(20, autonlinear);
  delay(3000);
  piston2.set_value(true);
}

void STWOMOGO() {
  inertial.tare();
  Task clamp_task(goalCover);
  driveForwardBump(60, autonlinear,0,skillslinear);
  piston.set_value(false);
  driveForward(-30, skillslinear);
}

void piston_fire(void *param) {
  delay(500);
  piston3.set_value(true);
  // ...
}

void wings() {
  Task wing(piston_fire);
  driveForwardVoltage(26, autonlinear,600,false);
  turnAngle(-40, autonrotation,6000, false);
  driveForward(8, autonlinear);
  piston.set_value(false);
  
}

void leftGoal() {
  inertial.tare();
  Task goal_cover(goalCover);
  track();
  piston.set_value(false);
  delay(100);
  driveForward(-45, autonlinear,0,skillslinear);
  FBarR.move_relative(1800, 100);
  holdAll();
  turnAngleAbs(-90, skillslinear,2000);
  driveForward(-10,skillslinear,200);
  Rings.move(600);
  delay(1500);
  Rings.move(0);

}

void solowinpoint() {
  piston2.set_value(true);
  delay(1000);
  holdAll();
  driveForward(-10,autonlinear,200);
  piston2.set_value(false);
  driveForward(-10,autonlinear,200);
  //driveForward(-20,autonlinear,200);
  double currangle = inertial.get_rotation();
  while(abs(inertial.get_rotation()-currangle<85)){
    driverControl(200, 0);
  }
  driverControl(0, 0);
  FBarR.move_relative(1400, 100);
  Rings.move_velocity(1200);
  driveForward(93,skillslinear,200);
  turnAngle(-110, autonlinear);
//  turnAngle(-102, autonlinear);
  Rings.move(0);
  driveForward(18,skillslinear,200);
  //driveForward(27,skillslinear);
  piston.set_value(true);
  delay(200);
  driveForward(-10,skillslinear);
  FBarR.move_absolute(0, 100);
  piston2.set_value(true);
  turnAngle(-100, autonlinear);
  driveForward(25,autonlinear);
  coastAll();
  piston.set_value(false);
  driveForward(-25,autonlinear);
}

void skills() {
  holdAll();
  int skills_speed = 150;
  piston.set_value(true);
  Clamp.move_relative(3000, 100);
  delay(2000);
  driveForward(-24, skillslinear, 0, skillslinear, skills_speed);
  Clamp.move_absolute(0, 100);
  delay(1000);
  driveForward(12, skillslinear, 0, skillslinear, 50);
  turnAngle(90, skillslinear, 200);
  driveForward(60, skillslinear, 0, skillslinear, 50);
  piston.set_value(false);
  FBarR.move_absolute(6000, -100);
  driveForward(-36, skillslinear, 0, skillslinear, 50);
  turnAngle(90, skillslinear, 200);
  driveForward(36, skillslinear, 0, skillslinear, 50);
  turnAngle(90, skillslinear, 100);
  driveForward(12, skillslinear, 0, skillslinear, 50);
  piston.set_value(true);
  driveForward(-6, skillslinear, 0, skillslinear, 50);
  FBarR.move_absolute(0, 100);
  turnAngle(-90, skillslinear, 100);
  driveForward(30, skillslinear, 0, skillslinear, 50);
  turnAngle(-90, skillslinear, 100);
  driveForward(36, skillslinear, 0, skillslinear, 50);
  piston.set_value(false);
  FBarR.move_relative(6000, -100);
  driveForward(-36, skillslinear, 0, skillslinear, 50);
  turnAngle(-90, skillslinear, 100);
  driveForward(36, skillslinear, 0, skillslinear, 50);
  turnAngle(-90, skillslinear, 100);
  driveForward(12, skillslinear, 0, skillslinear, 50);
  piston.set_value(true);
  driveForward(-12, skillslinear, 0, skillslinear, 50);
  FBarR.move_absolute(0, 100);
  turnAngle(-90, skillslinear, 100);
  driveForward(36, skillslinear, 0, skillslinear, 50);
  turnAngle(-90, skillslinear, 100);
  driveForward(84, skillslinear, 0, skillslinear, 50);
  turnAngle(90, skillslinear, 100);
  driveForward(12, skillslinear, 0, skillslinear, 50);
  turnAngle(-90, skillslinear, 100);
  driveForward(12, skillslinear, 0, skillslinear, 50);
  turnAngle(-90, skillslinear, 100);
  driveForward(24, skillslinear, 0, skillslinear, 50);
  piston.set_value(false);
  driveForward(-12, skillslinear, 0, skillslinear, 50);
  FBarR.move_relative(6000, -100);
  turnAngle(-90, skillslinear, 100);
  driveForward(96, skillslinear, 0, skillslinear, 50);
  turnAngle(90, skillslinear, 100);
  driveForward(36, skillslinear, 0, skillslinear, 50);
  turnAngle(-90, skillslinear, 100);
  driveForward(12, skillslinear, 0, skillslinear, 50);
  piston.set_value(true);
  coastAll();
}

void test() {
  inertial.tare();
  breakAll();
  Task clamp_task(goalCover);
  track();
  coastAll();
}
