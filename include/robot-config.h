using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor FrontLeft;
extern motor BackLeft;
extern motor FrontRight;
extern motor BackRight;
extern motor Flywheel;
extern motor ColorRoller;
extern motor Conveyor1;
extern motor Conveyor2;
extern controller Controller1;
extern signature ColorSensor__DISC;
extern signature ColorSensor__SIG_2;
extern signature ColorSensor__SIG_3;
extern signature ColorSensor__SIG_4;
extern signature ColorSensor__SIG_5;
extern signature ColorSensor__SIG_6;
extern signature ColorSensor__SIG_7;
extern vision ColorSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );