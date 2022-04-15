#include "main.h"

class driveTrain {
public:
  driveTrain(double wheelDiameter, double wheelToWheel)
      : wheelCircumfrence(wheelDiameter * M_PI),
        wheelBaseCircumfrence(wheelToWheel * M_PI) {}

  driveTrain(double wheelDiameter, double wheelToWheel, double linScale,
             double rScale)
      : wheelCircumfrence(wheelDiameter * M_PI),
        wheelBaseCircumfrence(wheelToWheel * M_PI), yScaleJoy(linScale),
        rScaleJoy(rScale) {}

  driveTrain(double wheelDiameter, double wheelToWheel, double xScale,
             double yScale, double rScale)
      : wheelCircumfrence(wheelDiameter * M_PI),
        wheelBaseCircumfrence(wheelToWheel * M_PI), yScaleJoy(yScale),
        rScaleJoy(rScale) {}

  double root2 = sqrt(2);
  double DPS2RPM = 3;
  double degToRad = M_PI / 180;
  double wheelCircumfrence;
  double wheelBaseCircumfrence;
  double maxRPM = 600;

  double yScaleJoy;
  double rScaleJoy;

  double yVel;
  double rVel;
  double linearVel;
  double joyAngle;
  double robotAngle;
  double modAngle;

  double wheelFL;
  double wheelFR;
  double wheelBL;
  double wheelBR;

  void calculateWheelSpeeds(double y, double r, double maxRPM) {
    yVel = y;
    rVel = r;

    linearVel = y;

    double yRPM = (yVel / (wheelCircumfrence)) * (900 / DPS2RPM);
    double rRPM = rVel;

    pros::lcd::print(3, "%f", rRPM);
    if (rRPM > maxRPM)
      rRPM = getSign(rRPM) * maxRPM;
    if (rRPM > maxRPM)
      yRPM = getSign(yRPM) * maxRPM;
    wheelFL = yRPM + rRPM;
    wheelFR = yRPM - rRPM;
    wheelBL = yRPM + rRPM;
    wheelBR = yRPM - rRPM;
    pros::lcd::print(4, "%f", wheelFL);
    pros::lcd::print(5, "%f", wheelFR);
  }

private:
  double getSign(double input) {
    if (input == 0)
      return 0;
    return abs(input) / input;
  }
  double abs(double input) {
    if (input > 0)
      return input;
    return -input;
  }
};
