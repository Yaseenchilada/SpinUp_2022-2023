#include "vex.h"
using namespace vex;

void visionDriving(){
  ColorSensor.setLedColor(0, 255, 255);
  if (ColorSensor.objects[0].exists){
    Brain.Screen.clearLine(3);
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Detected Object");
    Brain.Screen.setCursor(4, 1);
    Brain.Screen.print(ColorSensor.objects[0].angle);
  }else{
    Brain.Screen.clearLine(3);
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Detected Object");
  }
  
}