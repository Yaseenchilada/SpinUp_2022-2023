#include "calculations.h"
#include "vex.h"

using namespace vex;

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