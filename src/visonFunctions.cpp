#include "visionFunctions.h"
#include "vex.h"

using namespace vex;

int objectCenter = 0;

int visionDetection(){
  //int objectCenter = 100;
  Brain.Screen.setCursor(5, 1);
  Brain.Screen.print("WORKINGS?");
  while(420 == 420){
  ColorSensor.takeSnapshot(ColorSensor__DISC);
  if (ColorSensor.objectCount > 0){
    ColorSensor.setLedColor(0, 255, 0); // Green if disc
    objectCenter = ColorSensor.largestObject.centerX;

    Brain.Screen.clearLine(2);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Detected Object");
    Controller1.Screen.clearLine(1);
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print(objectCenter);

  }else{
    ColorSensor.setLedColor(255, 0, 0); // Red if no disc
    Brain.Screen.clearLine(2);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Detected Mo Object");
    objectCenter = 0;
  }
  wait(100, msec);
  }
  return 0;
}

int visionDriving(){ // not inuse. work in progress.
  wait(2, sec); // Inital Delay to not mess other stuff
  Brain.Screen.setCursor(8,1);
  Brain.Screen.print("object center: %d",objectCenter);
  float FL_motor_command;
  float BL_motor_command;
  float FR_motor_command;
  float BR_motor_command;

  while(true){
    if (objectCenter > 100){
      FL_motor_command = 25;
      BL_motor_command = 25;
      FR_motor_command = -25;
      BR_motor_command = -25;
    } else if (objectCenter < 70){
      FL_motor_command = -25;
      BL_motor_command = -25;
      FR_motor_command = 25;
      BR_motor_command = 25;
    } else if (objectCenter == 0){
      FL_motor_command = 0;
      BL_motor_command = 0;
      FR_motor_command = 0;
      BR_motor_command = 0;
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
    wait(2, sec);
   
  }
  return 0; // returns valid and complete
}

