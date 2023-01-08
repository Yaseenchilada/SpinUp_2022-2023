#include "vex.h"
using namespace vex;

// VISION_FOV_WIDTH = 316
// VISION_FOV_HEIGHT = 212
// 0,0 top left corner default
// positive x is right
// postiive y is down

int disc_signature = 1;

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
  
  //v2 testing shshiii
  /*
  if(ColorSensor.objectCount == 0){
    Brain.Screen.clearLine(3);
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("no objects :(");
  } else{
    ColorSensor.takeSnapshot(disc_signature);

  }
  */


}