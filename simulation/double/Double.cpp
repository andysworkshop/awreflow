#include <iostream>
#include <cstdint>
#include "Pid.h"

struct Segment {
  uint32_t Seconds;
  Pid::variable_t Temperature;
} 
Segments[] {

  { 100, 110, },
  { 180, 125, },
  { 230, 225, },
  { 250, 225, },
  { 420, 75,  }

};


int main() {

  Pid pid(1,1,1);
  int segment,current_seconds;
  Pid::variable_t current_temperature;
  
  // reset
  
  current_seconds=0;
  current_temperature=25;
  
  // cycle over each segment
  
  for(segment=0;segment<5;segment++) {
  
    Segment& seg(Segments[segment]);
  
    // cycle the seconds
    
    for(;current_seconds<seg.Seconds;current_seconds++) {
    }
  }
}
