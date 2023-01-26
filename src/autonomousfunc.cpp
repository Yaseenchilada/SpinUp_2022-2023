#include "autonomousfunc.h"
#include "vex.h"

using namespace vex;

float wheelDiameter = 3.5;
float wheelCircumference = wheelDiameter * 3.141; //inches
float turningDiameter = 22;
float translationSpeed = 100;
float turningSpeed = 50;
float tile = 24;

void driveForward(float inches) {
    float inchesPerDegree = wheelCircumference / 360;
    float degrees = inches / inchesPerDegree;

    FrontRight.startRotateFor(degrees, deg, translationSpeed, rpm);
    FrontLeft.startRotateFor(degrees, deg, translationSpeed, rpm);
    BackRight.startRotateFor(degrees, deg, translationSpeed, rpm);
    BackLeft.rotateFor(degrees, deg, translationSpeed, rpm);
}

void driveTurn(float degrees){
  float turningRatio = turningDiameter / wheelDiameter;
  float wheelDegrees = turningRatio * degrees;

    FrontRight.startRotateFor(-wheelDegrees, deg, turningSpeed, rpm);
    FrontLeft.startRotateFor(wheelDegrees, deg, turningSpeed, rpm);
    BackRight.startRotateFor(-wheelDegrees, deg, turningSpeed, rpm);
    BackLeft.rotateFor(wheelDegrees, deg, turningSpeed, rpm);
}

void startIntake(){
  ColorRoller.setVelocity(40,percent); // Set Velocity of Intake
  Conveyor1.setVelocity(45,percent); // Set Velocity of Conveyor1
  ColorRoller.spin(forward); // Start Motor
  Conveyor1.spin(forward); // Start Motor
}

void stopIntake(){
  ColorRoller.setVelocity(0, percent);
  Conveyor1.setVelocity(0, percent);
}

void startFlywheel(){
  Flywheel.setVelocity(70, percent);
  Flywheel.spin(forward);
}
void stopFlywheel(){
  Flywheel.setVelocity(0, percent);
}

void startConveyorToFlywheel(){
  Conveyor2.setVelocity(55, percent);
  Conveyor2.spin(forward);
}

void stopConveyorToFlywheel(){
  Conveyor2.setVelocity(0, percent);
}

void autonomous_mode(){
  wait(2, sec);


  driveForward(tile*2);

  driveTurn(90);
  wait(1, sec);

  startIntake();
  wait(.5, sec);

  driveForward(tile);
  wait(4, sec);
  stopIntake();
  wait(1,sec);

  driveTurn(-45);
  driveForward(tile/2);

  startFlywheel();
  wait(3, sec);
  startConveyorToFlywheel();
  wait(2, sec);
  stopConveyorToFlywheel();
  stopFlywheel();

  driveForward(tile);

}
