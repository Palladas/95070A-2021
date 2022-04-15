#include "../include/main.h"
#include "../include/motorSetup.h"

okapi::Controller master;
const double wheelCircumfrence = 10 * 3.25 * M_PI / 6;

int selected = 0;
std::string autons[11] = {"Disabled", "Wings",     "LeftGoal", "AWP1",
                          "AWP2",     "TWONUMOGO", "SNUMOGO",  "S2NUMOGO",
                          "SoloWP",   "Skills",    "Test"};
int size = 11; //*(&autons + 1) - autons;

void autonSelector() {
  master.clear();
  pros::delay(200);
  while (true) {
    master.clear();
    pros::delay(100);
    control.print(2, 1, autons[selected].c_str());
    pros::delay(100);
    if (control.get_digital(DIGITAL_RIGHT)) {
      selected = (selected + 1 + size) % size;
    } else if (control.get_digital(DIGITAL_LEFT)) {
      selected = (selected - 1 + size) % size;
    } else if (control.get_digital(DIGITAL_A)) {
      pros::delay(200);
      if (control.get_digital(DIGITAL_A)) {
        goto slctEnd;
      }
    }
  }
slctEnd:
  master.rumble("..");
}

void driverControl(double l, double r) {

  FrontLeft.move_velocity(l);
  FrontRight.move_velocity(r);
  MidLeft.move_velocity(l);
  MidRight.move_velocity(r);
  BackLeft.move_velocity(l);
  BackRight.move_velocity(r);
}

void fourbarmove(double speed) { FBarR.move_velocity(speed); }

void stopDrive(bool hold = false) {
  if (hold) {
    FrontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    FrontRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    MidLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    MidRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  FrontLeft.move_velocity(0);
  FrontRight.move_velocity(0);
  BackLeft.move_velocity(0);
  BackRight.move_velocity(0);
  MidLeft.move_velocity(0);
  MidRight.move_velocity(0);
  delay(100);
  FrontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  FrontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  MidLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  MidRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void runDriveValues() {
  FrontLeft.move_velocity(drive.wheelFL);
  FrontRight.move_velocity(drive.wheelFR);
  BackLeft.move_velocity(drive.wheelBL);
  BackRight.move_velocity(drive.wheelBR);
  MidLeft.move_velocity(drive.wheelBL);
  MidRight.move_velocity(drive.wheelBR);
}

void printOnScreen() {
  // lcd::print(1, "Velocity FL: %f", FrontLeft.get_actual_velocity());
  // lcd::print(2, "Target Velocity FL: %f", drive.wheelTL);
  lcd::print(0, "Forklift Reading: %f", Clamp.get_position());
  lcd::print(1, "Y Wheel Reading: %f", ((double)Left_Enc.get_value()));
  lcd::print(2, "X Wheel Reading: %f", ((double)Right_Enc.get_value()));
}

double getEncoders() {
  return (FrontLeft.get_position() + FrontRight.get_position()) / 2;
}

void driveForward(double inches, pidController controller,
                  double maxRPM = 600) {
  stopDrive(false);
  controller.resetID();
  double initialY = ((double)getEncoders()) * (wheelCircumfrence / 900);
  double targetY = ((double)getEncoders()) * (wheelCircumfrence / 900) + inches;

  int initialT = millis();
  controller.tVal = targetY;
  controller.error = controller.tVal - initialY;
  lcd::print(2, std::to_string(inertial.get_rotation()).c_str());
  while (!controller.withinTarget()) {
    controller.update(((double)getEncoders()) * wheelCircumfrence / 900);
    drive.calculateWheelSpeeds(maxRPM * controller.calculateOut() / 600, 0,
                               maxRPM);
    runDriveValues();
    delay(10);
  }
  FrontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  FrontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  MidLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  MidRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  FrontLeft.move_velocity(0);
  FrontRight.move_velocity(0);
  BackLeft.move_velocity(0);
  BackRight.move_velocity(0);
}

void driveForwardVoltage(double inches, pidController controller, double angle,
                         pidController rtController, double maxRPM = 600) {
  inertial.tare();
  controller.resetID();
  rtController.resetID();
  double initialY = ((double)getEncoders()) * (wheelCircumfrence / 900);
  double targetY = ((double)getEncoders()) * (wheelCircumfrence / 900) + inches;
  int initialT = millis();
  controller.tVal = targetY;
  controller.error = (controller.tVal - initialY);
  rtController.tVal = (angle);
  double rterror = angle - inertial.get_rotation();
  while (!controller.withinTarget()) {
    rtController.update(inertial.get_rotation());
    controller.update(((double)getEncoders()) * wheelCircumfrence / 900);
    drive.calculateWheelSpeeds(maxRPM * 1000 * controller.calculateOut() / 600,
                               4000 * rtController.calculateOut(), maxRPM);
    FrontLeft.move_voltage(drive.wheelFL);
    FrontRight.move_voltage(drive.wheelFR);
    BackLeft.move_voltage(drive.wheelBL);
    BackRight.move_voltage(drive.wheelBR);
    MidLeft.move_voltage(drive.wheelBL);
    MidRight.move_voltage(drive.wheelBR);
    delay(10);
  }
  stopDrive(false);
}

void driveForward(double inches, pidController controller, double angle,
                  pidController rtController, double maxRPM = 600) {
  inertial.tare();
  controller.resetID();
  rtController.resetID();
  double initialY = ((double)getEncoders()) * (wheelCircumfrence / 900);
  double targetY = ((double)getEncoders()) * (wheelCircumfrence / 900) + inches;
  int initialT = millis();
  controller.tVal = targetY;
  controller.error = controller.tVal - initialY;
  rtController.tVal = angle;
  double rterror = angle - inertial.get_rotation();
  while ((!controller.withinTarget()) && ((millis() - initialT) <= 5000)) {
    rtController.update(inertial.get_rotation());
    controller.update(((double)getEncoders()) * wheelCircumfrence / 900);
    drive.calculateWheelSpeeds(maxRPM * controller.calculateOut() / 600,
                               5 * rtController.calculateOut(), maxRPM);
    runDriveValues();
    delay(10);
  }
  stopDrive(false);
}

void turnAngle(double angle, pidController rtController, double maxRPM = 6000) {
  inertial.tare();
  stopDrive(false);
  rtController.resetID();
  int initialT = millis();
  rtController.tVal = angle;
  rtController.error = angle - inertial.get_rotation();
  lcd::print(2, std::to_string(inertial.get_rotation()).c_str());
  while (!rtController.withinTarget()) {
    lcd::print(2, std::to_string(inertial.get_rotation()).c_str());
    rtController.update(inertial.get_rotation());
    drive.calculateWheelSpeeds(0, maxRPM * rtController.calculateOut() / 600,
                               maxRPM);
    runDriveValues();
    delay(10);
  }
  stopDrive(false);
}

void holdAll() {
  FrontLeft.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  FrontRight.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  MidLeft.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  MidRight.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BackLeft.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BackRight.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  FBarR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  Clamp.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void coastAll() {
  FrontLeft.set_brake_mode(E_MOTOR_BRAKE_COAST);
  FrontRight.set_brake_mode(E_MOTOR_BRAKE_COAST);
  MidLeft.set_brake_mode(E_MOTOR_BRAKE_COAST);
  MidRight.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BackLeft.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BackRight.set_brake_mode(E_MOTOR_BRAKE_COAST);
  FBarR.set_brake_mode(E_MOTOR_BRAKE_COAST);
  Clamp.set_brake_mode(E_MOTOR_BRAKE_COAST);
}

void balance(pidController bController, double maxRPM = 600) {
  stopDrive(false);
  bController.resetID();
  bController.tVal = 0;
  bController.error = inertial.get_pitch();
  lcd::print(2, std::to_string(inertial.get_pitch()).c_str());
  while (!bController.withinTarget()) {
    lcd::print(2, std::to_string(inertial.get_pitch()).c_str());
    bController.update(inertial.get_pitch());
    drive.calculateWheelSpeeds(maxRPM * bController.calculateOut() / 600, 0,
                               maxRPM);
    runDriveValues();
    delay(10);
  }
  stopDrive(false);
}

void track() {
  double start = millis();
  while ((getEncoders() / 300) * 3.25 * M_PI < 96) {
    if (frontDist.get() <= 150 && frontDist.get() != 0 &&
        millis() - start > 200) {
      piston.set_value(false);
      break;
    }
    std::cout << frontDist.get() << '\n';
    driverControl(600, 600);
    delay(20);
  }
  double backtime = millis();
  while ((getEncoders() / 300) * 3.25 * M_PI > 10 &&
         millis() - backtime < 2000) {
    driverControl(-600, -600);
  }
}
