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


float MaxRotationSpeed = .55; // Normal Steering Speed no Turbo
float MaxTranslationSpeed = .80; // Normal Driving Speed no Turbo

float TurboRotationSpeed = .85; // Turbo Rotation Speed 
float TurboTranslationSpeed = 1; // Turbo Translation Speed

float currentMaxRotationSpeed = MaxRotationSpeed;
float currentMaxTranslationSpeed = MaxTranslationSpeed;


float cap(float inputVal, float maxMinVal) { // Cap allow full use of motor range with steering
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


void driveTrainLoop(){ // Controls Drivetrain > Gets Joystick Position & Sets to Motors
  //THE MOVE PLACE
  float V = Controller1.Axis3.position(percent); // Forward and backwards
  float H = Controller1.Axis4.position(percent); // Strafe
  float S = Controller1.Axis1.position(percent); // Steering
    
  float vA = V * currentMaxTranslationSpeed; // Limit Forward/Backwards Speed
  float hA = H * currentMaxTranslationSpeed; // Limit Strafe Speed
  float sA = S * currentMaxRotationSpeed; // Limit Steering Speed
    
  float drivetrainMax = 100 - fabs(sA); // Max motor movement given steering is constant

  // Set Motor Velocity with Steering Prioritized with 
  float FL_motor_command = sA + cap(vA + hA, drivetrainMax);
  float BL_motor_command = sA + cap(vA + -hA, drivetrainMax);
  float FR_motor_command = -sA + cap(vA + -hA, drivetrainMax);
  float BR_motor_command = -sA + cap(vA + hA, drivetrainMax);

  // Assign Proper Velocity for Each Motor
  FrontLeft.setVelocity(FL_motor_command, percent);
  BackLeft.setVelocity(BL_motor_command, percent);
  FrontRight.setVelocity(FR_motor_command, percent);
  BackRight.setVelocity(BR_motor_command, percent);

  // Start Motors
  FrontLeft.spin(forward);
  FrontRight.spin(forward);
  BackLeft.spin(forward);
  BackRight.spin(forward);
}



void buttonControls(){ // Controller Button Actions

  if(Controller1.ButtonY.pressing() == true) { //This is for Conveyor1 and Intake
    ColorRoller.setVelocity(40,percent); // Set Velocity of Intake
    Conveyor1.setVelocity(45,percent); // Set Velocity of Conveyor1
    ColorRoller.spin(forward); // Start Motor
    Conveyor1.spin(forward); // Start Motor
  }
  
  else if(Controller1.ButtonX.pressing() == true) { // This is for Conveyor1 and Intake Rejection
    ColorRoller.setVelocity(-100,percent); // Set Velocity of Intake
    Conveyor1.setVelocity(-100,percent); // Set Velocity of Conveyor1
    ColorRoller.spin(forward); // Start Motor 
    Conveyor1.spin(forward); // Start Motor
  }

  else if (Controller1.ButtonB.pressing() == true) {
    Conveyor1.setVelocity(0,percent); // 

    if (ColorSensor.objects[0].width >= 120) { // if the first object detected in the vision sensor is wider than 120, then stop the motor
      ColorRoller.setVelocity(0,percent);
    }
    else { // otherwise run the motor
      ColorRoller.setVelocity(20,percent);
    }
  }

  else {
    ColorRoller.setVelocity(0,percent);
    Conveyor1.setVelocity(0,percent);
  }

  if(Controller1.ButtonR2.pressing() == true) { //This is for the Flywheel
    Flywheel.setVelocity(100,percent); // Set Velocity of Flywheel to 100%
    Flywheel.spin(forward); // Start Motor
  }
  else {
    Flywheel.setVelocity(0,percent); // Stop Motor Velocity
  }


  if(Controller1.ButtonL2.pressing() == true) { //This is for Conveyor2 Forwards
    Conveyor2.setVelocity(75,percent); // Set Velocity
    Conveyor2.spin(forward); // Start Motor
  }

  else if(Controller1.ButtonL1.pressing() == true) { //This is for Conveyor2 Reverse
    Conveyor2.setVelocity(-35,percent); // Set Velocity
    Conveyor2.spin(forward); // Start Motor

  } 
  else {
    Conveyor2.setVelocity(0,percent); // Stop Motor Velocity 
  }



  // BETA TURBO CODE
  if(Controller1.ButtonR1.pressing() == true){
    currentMaxRotationSpeed = TurboRotationSpeed; // Sets current rotation speed to turbo value
    currentMaxTranslationSpeed = TurboTranslationSpeed; // Sets current translation speed to turbo value
  } else{
    currentMaxRotationSpeed = MaxRotationSpeed; // Sets current max rotation speed back to default
    currentMaxTranslationSpeed = MaxTranslationSpeed; // Sets current translation speed back to default
  }


}


// Hayden's Testing Code :)

void testingFunction(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Yaseen");
  //Controller1.Screen.setCursor(2,1);
  //Controller1.Screen.print(Brain.Battery.voltage());

  //Brain.Screen.clearLine();
  //Brain.Screen.print("Yaseen");
  //Brain.Screen.setCursor(1,1);
  //Brain.Screen.print(Controller1.Axis3.position(percent));
}



int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while(420==420) {
    driveTrainLoop();

    buttonControls();
    testingFunction(); //hayden is messing with this
  }
  
}

// created by yaseen and hayden. the best