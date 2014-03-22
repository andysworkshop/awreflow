/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#pragma once


namespace awreflow {


  /*
   * Reflow profile structure. A reflow profile consists of a list of segments. Each segment
   * defines the duration of that segment and the desired ending temperature.
   */

  class ReflowProfile {

    public:

      struct Segment {
        uint16_t Duration;
        Pid::variable_t Temperature;
      };

    protected:
      const Segment *_segments;
      uint8_t _segmentCount;

    public:
      ReflowProfile(const Segment *segments,uint8_t segmentCount);
  };


  /*
   * Constructor
   */

  inline ReflowProfile::ReflowProfile(const Segment *segments,uint8_t segmentCount)
    : _segments(segments),
      _segmentCount(segmentCount) {
  }
}
