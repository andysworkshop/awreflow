/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#include "Application.h"


namespace awreflow {


  /*
   * Start the process
   */

  void ReflowResults::start(uint16_t maxDataPoints) {
    _results.reset(new uint16_t[maxDataPoints]);
    _numDataPoints=0;
  }


  /*
   * Transmit the results at 9600 8/N/1 as a CSV file that can be imported
   * into <insert-favourite-spreadsheet-here>. Column 1 is the number of seconds,
   * column 2 is the desired temperature and column 3 is the actual temperature.
   */

  void ReflowResults::transmit(const ReflowProfile& profile) const {

    Usart1<> usart(9600);
    UsartPollingOutputStream outputStream(usart);
    uint8_t segment;
    uint16_t seconds;
    Pid::variable_t desired,step;

    desired=25;       // all profiles start at 25
    seconds=0;

    // run through all the segments

    for(segment=0;segment<profile.getSegmentCount();segment++) {

      // calculate the temperature step

      const ReflowProfile::Segment& s(profile[segment]);
      step=(s.Temperature-desired)/(s.EndingTime-seconds);

      // go over each second in the segment

      while(seconds<s.EndingTime) {

        // return if we've exhausted the number of points collected

        if(seconds==_numDataPoints)
          return;

        // write to the USART

        outputStream << seconds << ","
                     << static_cast<uint16_t>(desired) << ","
                     << _results[seconds] << "\r\n";

        // write out

        seconds++;
        desired+=step;
      }
    }
  }
}
