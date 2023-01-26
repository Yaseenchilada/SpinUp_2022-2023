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

    FrontRight.startRotateFor(degrees, deg, 100, rpm);
    FrontLeft.startRotateFor(degrees, deg, 100, rpm);
    BackRight.startRotateFor(degrees, deg, 100, rpm);
    BackLeft.rotateFor(degrees, deg, 100, rpm);
}

void driveTurn(float degrees){
  float turningRatio = turningDiameter / wheelDiameter;
  float wheelDegrees = turningRatio * degrees;
    FrontRight.startRotateFor(-wheelDegrees, deg, turningSpeed, rpm);
    FrontLeft.startRotateFor(wheelDegrees, deg, turningSpeed, rpm);
    BackRight.startRotateFor(-wheelDegrees, deg, turningSpeed, rpm);
    BackLeft.rotateFor(wheelDegrees, deg, turningSpeed, rpm);
}

void driveStrafe(float inches){
    float speed = 100;
    float inchesPerDegree = wheelCircumference / 360;
    float degrees = (inches / inchesPerDegree)/2;
    FrontRight.startRotateFor(degrees, deg, speed, rpm);
    FrontLeft.startRotateFor(-degrees, deg, speed, rpm);
    BackRight.startRotateFor(-degrees, deg, speed, rpm);
    BackLeft.rotateFor(degrees, deg, speed, rpm);
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

void startFlywheel(int powera){
  Flywheel.setVelocity(powera, percent);
  Flywheel.spin(forward);
}
void stopFlywheel(){
  Flywheel.setVelocity(0, percent);
}

void startConveyorToFlywheel(){
  Conveyor2.setVelocity(55, percent);
  Conveyor2.spin(forward);
}

void startConveyorToFlywheelIntermittent(){
  Conveyor2.setVelocity(75, percent);
  Conveyor2.spin(forward);
  wait(.5, sec);
  Conveyor2.setVelocity(40, percent);
  wait(.5, sec);
  Conveyor2.setVelocity(75, percent);
}

void stopConveyorToFlywheel(){
  Conveyor2.setVelocity(0, percent);
}


void autonomous_mode(){
  wait(2, sec);
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("ih ate you");
  driveForward(tile*4);
  wait(10,sec);
  //wait(2,sec); //delay
  Controller1.Screen.print("josh is");
  //driveTurn(90);
  //wait(3,sec);


  //startIntake();
  //wait(.5, sec);
  //driveForward(3);

  /*
  driveForward(2*tile, translationSpeed);
  wait(.5,sec); //delay
  driveTurn(-90);
  wait(2, sec);
  startFlywheel(80);
  wait(2,sec);
  stopIntake();
  wait(.5,sec); //delay
  startConveyorToFlywheelIntermittent();
  wait(4, sec);
  stopConveyorToFlywheel();
  stopFlywheel();
  wait(.5,sec); //delay
  driveTurn(45);
  driveForward(2*tile, translationSpeed);
  wait(.5,sec); //delay
  driveTurn(45);
  driveForward(tile, 50);
  */
}
