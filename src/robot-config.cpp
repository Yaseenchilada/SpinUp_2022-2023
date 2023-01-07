#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FrontLeft = motor(PORT1, ratio18_1, false);
motor BackLeft = motor(PORT3, ratio18_1, false);
motor FrontRight = motor(PORT2, ratio18_1, true);
motor BackRight = motor(PORT4, ratio18_1, true);
motor Flywheel = motor(PORT5, ratio18_1, true);
motor ColorRoller = motor(PORT6, ratio18_1, true);
motor Conveyor1 = motor(PORT7, ratio18_1, true);
motor Conveyor2 = motor(PORT8, ratio18_1, false);
controller Controller1 = controller(primary);
/*vex-vision-config:begin*/
signature ColorSensor__DISC = signature (1, 317, 881, 600, -5461, -4853, -5158, 3, 0);
vision ColorSensor = vision (PORT9, 50, ColorSensor__DISC);
/*vex-vision-config:end*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}