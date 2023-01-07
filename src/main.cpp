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

bool turboModeActive = false; // Current Turbo Status
bool imagedetection = false;

float currentMaxRotationSpeed = MaxRotationSpeed;
float currentMaxTranslationSpeed = MaxTranslationSpeed;

float conveyor1Speed = 45;
float conveyor1SpeedTurbo = 85;
float colorRollerSpeed = 40;
float colorRollerSpeedTurbo = 80;
float currentConveyor1Speed = conveyor1Speed;
float currentcolorRollerSpeed = colorRollerSpeed;

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

void turbocode(){ // BETA TURBO CODE CALLBACK FUNCTION
  if(turboModeActive == false){
    currentMaxRotationSpeed = TurboRotationSpeed; // Sets current rotation speed to turbo value
    currentMaxTranslationSpeed = TurboTranslationSpeed; // Sets current translation speed to turbo value
    currentConveyor1Speed = conveyor1SpeedTurbo;
    currentcolorRollerSpeed = colorRollerSpeedTurbo;
    
    turboModeActive = true;
    Controller1.Screen.clearLine(3);  // DELETE THESE LINES IF CODE IS BREAKING
    Controller1.Screen.setCursor(3, 1); // DELETE THESE LINES IF CODE IS BREAKING
    Controller1.Screen.print("TURBO MODE ACTIVE"); // DELETE THESE LINES IF CODE IS BREAKING

  } else if(turboModeActive == true){
    currentMaxRotationSpeed = MaxRotationSpeed; // Sets current max rotation speed back to default
    currentMaxTranslationSpeed = MaxTranslationSpeed; // Sets current translation speed back to default
    currentConveyor1Speed = conveyor1Speed;
    currentcolorRollerSpeed = colorRollerSpeed; 

    turboModeActive = false;
    Controller1.Screen.clearLine(3); // DELETE THESE LINES IF CODE IS BREAKING
    Controller1.Screen.clearLine(1);
    
  }
}




void driveTrainLoop(){ // Controls Drivetrain > Gets Joystick Position & Sets to Motors
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
    ColorRoller.setVelocity(currentcolorRollerSpeed,percent); // Set Velocity of Intake
    Conveyor1.setVelocity(currentConveyor1Speed,percent); // Set Velocity of Conveyor1
    ColorRoller.spin(forward); // Start Motor
    Conveyor1.spin(forward); // Start Motor
  }
  
  else if(Controller1.ButtonX.pressing() == true) { // This is for Conveyor1 and Intake Rejection
    ColorRoller.setVelocity(-currentcolorRollerSpeed,percent); // Set Velocity of Intake
    Conveyor1.setVelocity(-currentConveyor1Speed,percent); // Set Velocity of Conveyor1
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


  Controller1.ButtonR1.pressed(turbocode); // Activate Turbo Mode

}



void autonomous_mode(){ 
  Controller1.Screen.clearScreen();
  Controller1.Screen.print("Autonomous");
  Brain.Screen.clearScreen();
  Brain.Screen.print("Autonomous Active");
}


// Hayden's Testing Code :)

void testingFunction(){

  Controller1.Screen.setCursor(2,1);
  Controller1.Screen.print(Controller1.Axis3.position(percent));
  
  Brain.Screen.print(Brain.Battery.voltage());
  

}

void setup(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Yaseen");

  Brain.Screen.clearScreen();
  Brain.Screen.clearLine();
  Brain.Screen.print("Yaseen <3");
  Brain.Screen.setCursor(1,1);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  setup();
  while(420==420) {
    driveTrainLoop();

    buttonControls();
    // DELETE THESE LINES IF CODE IS BREAKING
    //testingFunction(); //hayden is messing with this
  }
  
}

// created by yaseen and hayden. the best