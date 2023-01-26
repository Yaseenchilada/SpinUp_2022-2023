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
#include "gifclass.h"
#include "visionFunctions.h"
#include "calculations.h"
#include "variables.h"
#include "autonomousfunc.h"

using namespace vex;

competition Competition;




void turbocode(){ // BETA TURBO CODE CALLBACK FUNCTION
  if(turboModeActive == false){
    currentMaxRotationSpeed = TurboRotationSpeed; // Sets current rotation speed to turbo value
    currentMaxTranslationSpeed = TurboTranslationSpeed; // Sets current translation speed to turbo value
    currentConveyor1Speed = conveyor1SpeedTurbo;
    currentcolorRollerSpeed = colorRollerSpeedTurbo;
    currentConveyor2Speed = conveyor2SpeedTurbo;
    turboModeActive = true;

    Controller1.Screen.clearLine(3);  
    Controller1.Screen.setCursor(3, 1); 
    Controller1.Screen.print("TURBO MODE ACTIVE");

  } else if(turboModeActive == true){
    currentMaxRotationSpeed = MaxRotationSpeed; // Sets current max rotation speed back to default
    currentMaxTranslationSpeed = MaxTranslationSpeed; // Sets current translation speed back to default
    currentConveyor1Speed = conveyor1Speed;
    currentcolorRollerSpeed = colorRollerSpeed; 
    currentConveyor2Speed = conveyor2Speed;
    turboModeActive = false;

    Controller1.Screen.clearLine(3);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(" ");
  }
}


int driveTrainLoop(){ // Controls Drivetrain > Gets Joystick Position & Sets to Motors
  while(69 == 69){
  //THE MOVE PLACE
  float V = Controller1.Axis3.position(percent); // Forward and backwards
  float H = Controller1.Axis4.position(percent); // Strafe
  float S = Controller1.Axis1.position(percent); // Steering
    
  float vA = V * currentMaxTranslationSpeed; // Limit Forward/Backwards Speed
  float hA = H * currentMaxTranslationSpeed; // Limit Strafe Speed
  float sA = S * currentMaxRotationSpeed; // Limit Steering Speed

  float drivetrainMax = 100 - fabsf(sA); // Max motor movement given steering is constant

  // Set Motor Velocity with Steering Prioritized with 
  float FL_motor_command = sA + cap(vA + hA, drivetrainMax);
  float BL_motor_command = sA + cap(vA + -hA, drivetrainMax);
  float FR_motor_command = -sA + cap(vA + -hA, drivetrainMax);
  float BR_motor_command = -sA + cap(vA + hA, drivetrainMax);
  if (autonoumousActive == false && visionDrivingActive == false){
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

  wait(25,msec);
  }
  return 0;
}


int buttonControls(){ // Controller Button Actions
  while(true){
  if (autonoumousActive == false){
  if(Controller1.ButtonY.pressing() == true) { //This is for Conveyor1 and Intake
    ColorRoller.setVelocity(currentcolorRollerSpeed,percent); // Set Velocity of Intake
    Conveyor1.setVelocity(currentConveyor1Speed,percent); // Set Velocity of Conveyor1
    ColorRoller.spin(forward); // Start Motor
    Conveyor1.spin(forward); // Start Motor
  } else if(Controller1.ButtonX.pressing() == true) { // This is for Conveyor1 and Intake Rejection
    ColorRoller.setVelocity(-currentcolorRollerSpeed,percent); // Set Velocity of Intake
    Conveyor1.setVelocity(-currentConveyor1Speed,percent); // Set Velocity of Conveyor1
    ColorRoller.spin(forward); // Start Motor 
    Conveyor1.spin(forward); // Start Motor
  } else if (Controller1.ButtonB.pressing() == true) {
    ColorSensor.takeSnapshot(ColorSensor__DISC); //CHANGE SIGNATURE
    if (ColorSensor.objectCount > 0) {
      ColorRoller.setVelocity(0,percent);
    } else { // otherwise run the motor
      ColorRoller.setVelocity(20,percent);
    }
} else {
    ColorRoller.setVelocity(0,percent); // otherwise stop motors
    Conveyor1.setVelocity(0,percent);
  }


  if(Controller1.ButtonR2.pressing() == true) { //This is for the Flywheel
    Flywheel.setVelocity(flywheelStrength, percent); // Set Velocity of Flywheel to 100%
    Flywheel.spin(forward); // Start Motor
  } else {
    Flywheel.setVelocity(0,percent); // Stop Motor Velocity
  }


  if(Controller1.ButtonL2.pressing() == true) { //This is for Conveyor2 Forwards
    Conveyor2.setVelocity(currentConveyor2Speed,percent); // Set Velocity
    Conveyor2.spin(forward); // Start Motor
  } else if(Controller1.ButtonL1.pressing() == true) { //This is for Conveyor2 Reverse
    Conveyor2.setVelocity(-currentConveyor2Speed,percent); // Set Velocity
    Conveyor2.spin(forward); // Start Motor
  } else {
    Conveyor2.setVelocity(0,percent); // Stop Motor Velocity 
  }

  }

  Controller1.ButtonR1.pressed(turbocode); // Activate Turbo Mode
  

  if(Controller1.ButtonLeft.pressing() == true){ //Decreases flywheel strength
    if(flywheelStrength > 10){
      flywheelStrength-=10;
      Controller1.Screen.clearLine(2);
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print(flywheelStrength);
    }
    wait(500,msec);
  } else if(Controller1.ButtonRight.pressing() == true){ //Increases flywheel strength
    if(flywheelStrength < 100){
      flywheelStrength+=10;
      Controller1.Screen.clearLine(2);
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print(flywheelStrength);
    }
    wait(500,msec);
  }
  wait(25,msec);
  }
  return 0;
}


void setup(){ // Setup Code -- Only Runs Once
  // Screen Setup
  Controller1.Screen.clearScreen();
  Brain.Screen.drawImageFromFile("yaseencute.png", 1, 1);
  Brain.Screen.setCursor(1,1);
  Brain.Screen.setFillColor(vex::color(0,0,0));
  Brain.Screen.print("Programming by Hayden <3 <o/");
}

void driverControl(){
  task driveTrainLoopTask = task(driveTrainLoop); // Task for drive train
  task buttonControlsTask = task(buttonControls); // Task for controller button presses
}


void autonomous_mode_callback2(void){
  autonomous_mode();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  setup();
  
  Competition.autonomous(autonomous_mode_callback2);
  Competition.drivercontrol(driverControl);

  vex::Gif gif("kanye.gif", 270, 120); 
  int count=0;
  while(420==420) {
    Brain.Screen.printAt(0,0, "render %d", count++);
    Brain.Screen.render();
    vexDelay(50);  //delay to limit resources
  }
}

// created by yaseen and hayden. the best
