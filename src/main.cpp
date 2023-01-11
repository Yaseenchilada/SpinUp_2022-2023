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

// VARIABLES
float MaxRotationSpeed = .55; // Normal Steering Speed no Turbo
float MaxTranslationSpeed = .80; // Normal Driving Speed no Turbo
float TurboRotationSpeed = .85; // Turbo Rotation Speed 
float TurboTranslationSpeed = 1; // Turbo Translation Speed
float currentMaxRotationSpeed = MaxRotationSpeed;
float currentMaxTranslationSpeed = MaxTranslationSpeed;

int conveyor1Speed = 45; //Normal Vertical Conveyor Speed 
int conveyor1SpeedTurbo = 85; //Turbo Vertical Conveyor Speed 
int colorRollerSpeed = 40; // Normal Intake/ColorRoller Speed
int colorRollerSpeedTurbo = 80; // Turbo Intake/ColorRoller Speed
int currentConveyor1Speed = conveyor1Speed;
int currentcolorRollerSpeed = colorRollerSpeed;
 
int conveyor2Speed = 75;
int conveyor2SpeedTurbo = 100;
int currentConveyor2Speed = conveyor2Speed;

int flywheelStrength = 100; // Flywheel Strength 

bool turboModeActive = false; // Current Turbo Status
bool imagedetection = false; // BETA IMAGE DETECTION Status
bool autonoumousActive = false; // autonmous active status

int objectCenter = 110;

int visionDriving(){
  Brain.Screen.setCursor(5, 1);
  Brain.Screen.print("WORKINGS?");
  while(420 == 420){
  ColorSensor.takeSnapshot(ColorSensor__DISC);
  if (ColorSensor.objectCount > 0){
    ColorSensor.setLedColor(0, 255, 0);
    Brain.Screen.clearLine(3);
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Detected Object");
    Brain.Screen.setCursor(4, 1);
    Brain.Screen.print(ColorSensor.largestObject.centerX);
    objectCenter = ColorSensor.largestObject.centerX;
    Controller1.Screen.clearLine(1);
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print(ColorSensor.largestObject.centerX);

  }else{
    ColorSensor.setLedColor(255, 0, 0);
    Brain.Screen.clearLine(3);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Detected not Object");
    Brain.Screen.clearLine(4);
  }
  wait(300, msec);
  }
  return 0;
}
task visionCamTask = task(visionDriving);


void toggleimage(){ // Switch to inverse of other varible

  if(imagedetection == false){
    Brain.Screen.clearLine(10); // set cursor on the brain screen to line 12
    Brain.Screen.setCursor(10, 1);
    Brain.Screen.print("VISION ON"); // 
    visionCamTask.resume(); // resume the task
    imagedetection = true;
    
  }else if(imagedetection == true){
    Brain.Screen.clearLine(10); // set cursor on the brain screen to line 12
    Brain.Screen.setCursor(9, 1);
    Brain.Screen.print("VISION OFF"); // display vision is off 
    visionCamTask.suspend(); // testing this suspend method
    imagedetection = false;
  }
}


int autonomous_mode(){ // not inuse. work in progress.
  Brain.Screen.clearScreen();
  Brain.Screen.print("Autonomous Active");
  float FL_motor_command;
  float BL_motor_command;
  float FR_motor_command;
  float BR_motor_command;
  Brain.Screen.clearScreen(1);
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(objectCenter);
  while(true){
    if (objectCenter > 160){
      FL_motor_command = -25;
      BL_motor_command = -25;
      FR_motor_command = 25;
      BR_motor_command = 25;
    } else if (objectCenter < 70){
      FL_motor_command = -25;
      BL_motor_command = -25;
      FR_motor_command = 25;
      BR_motor_command = 25;
    } else{
      FL_motor_command = 25;
      BL_motor_command = 25;
      FR_motor_command = 25;
      BR_motor_command = 25;
    }
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
    wait(25, sec);
  }
  return 0; // returns valid and complete
}

task autonomousModeTask = task(autonomous_mode); // setup task of autonomous 

void toggleAutonomous(){ // toggles the autonomous boolean to the opposite and starts the task of autonomous
  if(autonoumousActive == false){ 
    autonomousModeTask.resume(); // start autonoumous task
    Controller1.Screen.setCursor(2, 1); 
    Controller1.Screen.clearLine(2);
    Controller1.Screen.print("Autonomous On"); // display active to controller screen
    autonoumousActive = true;
  } else{
    autonomousModeTask.suspend(); // stop autonoumous task
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.clearLine(2);
    Controller1.Screen.print("Autonomous Off"); // display stop to controller screen
    autonoumousActive = false;
  }
}


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
  if (autonoumousActive == false){
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
    ColorSensor.takeSnapshot(ColorSensor__DISC); //CHANGE SIGNATURE
    if (ColorSensor.objectCount > 0) {
      ColorRoller.setVelocity(0,percent);
    }
    else { // otherwise run the motor
      ColorRoller.setVelocity(20,percent);
    }
  }

  else {
    ColorRoller.setVelocity(0,percent); // otherwise stop motors
    Conveyor1.setVelocity(0,percent);
  }

  if(Controller1.ButtonR2.pressing() == true) { //This is for the Flywheel
    Flywheel.setVelocity(flywheelStrength, percent); // Set Velocity of Flywheel to 100%
    Flywheel.spin(forward); // Start Motor
  }
  else {
    Flywheel.setVelocity(0,percent); // Stop Motor Velocity
  }


  if(Controller1.ButtonL2.pressing() == true) { //This is for Conveyor2 Forwards
    Conveyor2.setVelocity(currentConveyor2Speed,percent); // Set Velocity
    Conveyor2.spin(forward); // Start Motor
  }

  else if(Controller1.ButtonL1.pressing() == true) { //This is for Conveyor2 Reverse
    Conveyor2.setVelocity(-currentConveyor2Speed,percent); // Set Velocity
    Conveyor2.spin(forward); // Start Motor

  } 
  else {
    Conveyor2.setVelocity(0,percent); // Stop Motor Velocity 
  }


  Controller1.ButtonR1.pressed(turbocode); // Activate Turbo Mode
  Controller1.ButtonDown.pressed(toggleimage); // Activates Image Detection
  Controller1.ButtonA.pressed(toggleAutonomous);


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
  autonomousModeTask.suspend();
  //visionCamTask.suspend();
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Yaseen");

  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Yaseen <3");
  Brain.Screen.setCursor(14, 1);
  Brain.Screen.print("Hayden was here ;)");
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  setup();
  task driveTrainLoopTask = task(driveTrainLoop); // Task for drive train
  task buttonControlsTask = task(buttonControls); // Task for controller button presses
  
  while(420==420) {
    vexDelay(25);  //delay to limit resources
  }
  
}

// created by yaseen and hayden. the best