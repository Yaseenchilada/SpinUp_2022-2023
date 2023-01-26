#include "autonomousfunc.h"
#include "vex.h"

using namespace vex;

float wheelDiameter = 3.5;
float wheelCircumference = wheelDiameter * 3.141; //inches
float turningDiameter = 22;
float translationSpeed = 100;
float turningSpeed = 50;
float tile = 24;

void driveForward(float inches, float speed) {
    float inchesPerDegree = wheelCircumference / 360;
    float degrees = inches / inchesPerDegree;

    FrontRight.startRotateFor(degrees, deg, speed, rpm);
    FrontLeft.startRotateFor(degrees, deg, speed, rpm);
    BackRight.startRotateFor(degrees, deg, speed, rpm);
    BackLeft.rotateFor(degrees, deg, speed, rpm);
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

  driveForward(.5*tile, translationSpeed);
  driveTurn(45);

  startIntake();
  wait(.5, sec);

  driveForward(2*tile, translationSpeed);
  
  driveTurn(-90);
  wait(2, sec);
  startFlywheel();
  wait(2,sec);
  stopIntake();

  startConveyorToFlywheel();
  wait(4, sec);
  stopConveyorToFlywheel();
  stopFlywheel();

  driveForward(tile, translationSpeed);

}
