/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\abdel                                            */
/*    Created:      Tue Jan 03 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontLeft            motor         1               
// BackLeft             motor         3               
// FrontRight           motor         2               
// BackRight            motor         4               
// Flywheel             motor         5               
// ColorRoller          motor         6               
// Conveyor1            motor         7               
// Conveyor2            motor         8               
// Controller1          controller                    
// ColorSensor          vision        9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

float cap(float inputVal, float maxMinVal) {

  if (inputVal > maxMinVal){
    return maxMinVal;
  } else if (inputVal < -maxMinVal) {
    return -maxMinVal;
  } else{
    return inputVal;
  };
  // if inputVal is greater than max min val, return max min val
  // if less than min val then return -maxMinVal
  // else return inputVal
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  
  while(420==420) {

    float currentMaxRotationSpeed = 0.4;
    float currentMaxTranslationSpeed = 1;

    //THE MOVE PLACE
    float V = Controller1.Axis3.position(percent);
    //V is forward and backwards
    float H = Controller1.Axis4.position(percent);
    //H is straif
    float S = Controller1.Axis1.position(percent);
    //S is steering input
    float vA = V * currentMaxTranslationSpeed;
    float hA = H * currentMaxTranslationSpeed;
    float sA = S * currentMaxRotationSpeed;
    
    float drivetrainMax = 100 - abs(sA);
    //this is the max speed
    // ---------------------

    float FL_motor_command = sA + cap(vA + hA, drivetrainMax);
    float BL_motor_command = sA + cap(vA + -hA, drivetrainMax);
    float FR_motor_command = -sA + cap(vA + -hA, drivetrainMax);
    float BR_motor_command = -sA + cap(vA + hA, drivetrainMax);

    FrontLeft.setVelocity(FL_motor_command, percent);
    BackLeft.setVelocity(BL_motor_command, percent);
    FrontRight.setVelocity(FR_motor_command, percent);
    BackRight.setVelocity(BR_motor_command, percent);

    FrontLeft.spin(forward);
    FrontRight.spin(forward);
    BackLeft.spin(forward);
    BackRight.spin(forward);

    //This is for Conveyor1 and Intake
    if(Controller1.ButtonY.pressing() == true) {
      ColorRoller.setVelocity(40,percent);
      Conveyor1.setVelocity(80,percent);
      ColorRoller.spin(forward);
      Conveyor1.spin(forward);
    }
    
    else if (Controller1.ButtonB.pressing() == true) {
      Conveyor1.setVelocity(0,percent);
      // if the first object detected in the vision sensor is wider than 120, then stop the motor
      if (ColorSensor.objects[0].width >= 120) { 
        ColorRoller.setVelocity(0,percent);
      }
      // otherwise run the motor
      else {
        ColorRoller.setVelocity(20,percent);
      }
    }

    else {
      ColorRoller.setVelocity(0,percent);
      Conveyor1.setVelocity(0,percent);
    }

    //This is for the Flywheel
    if(Controller1.ButtonR2.pressing() == true) {
      Flywheel.setVelocity(100,percent);
      Flywheel.spin(forward);
    }
    else {
      Flywheel.setVelocity(0,percent);
    }
    
    //This is for Conveyor2
    if(Controller1.ButtonL2.pressing() == true) {
      Conveyor2.setVelocity(30,percent);
      Conveyor2.spin(forward);
    }
    else {
      Conveyor2.setVelocity(0,percent);
    }

  }
  
}

