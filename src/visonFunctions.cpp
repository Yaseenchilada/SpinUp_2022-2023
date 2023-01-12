#include "visionFunctions.h"
#include "vex.h"

using namespace vex;

int visionDrive(int objectCenter){
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
    Controller1.Screen.print(ColorSensor.largestObject.centerX);

  }else{
    ColorSensor.setLedColor(255, 0, 0); // Red if no disc
    Brain.Screen.clearLine(2);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Detected Mo Object");
    objectCenter = 0;
  }
  wait(300, msec);
  }
  return 0;


}