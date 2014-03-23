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
        uint16_t EndingTime;
        uint16_t Temperature;
      };

    protected:
      const Segment *_segments;
      uint8_t _segmentCount;
      uint16_t _maxTemperature;
      uint16_t _totalDuration;

    public:
      ReflowProfile(const Segment *segments,uint8_t segmentCount,uint16_t maxTemperature,uint16_t totalDuration);

      const Segment& operator[](uint8_t index) const;
      uint16_t getMaxTemperature() const;
      uint16_t getTotalDuration() const;
      uint8_t getSegmentCount() const;
  };


  /*
   * Constructor
   */

  inline ReflowProfile::ReflowProfile(const Segment *segments,uint8_t segmentCount,uint16_t maxTemperature,uint16_t totalDuration)
    : _segments(segments),
      _segmentCount(segmentCount),
      _maxTemperature(maxTemperature),
      _totalDuration(totalDuration) {
  }


  /*
   * Get a reference to a segment
   */

  inline const ReflowProfile::Segment& ReflowProfile::operator[](uint8_t index) const {
    return _segments[index];
  }


  /*
   * Get the maximum temperature
   */

  inline uint16_t ReflowProfile::getMaxTemperature() const {
    return _maxTemperature;
  }


  /*
   * Get the total duration
   */

  inline uint16_t ReflowProfile::getTotalDuration() const {
    return _totalDuration;
  }


  /*
   * Get the total number of segments
   */

  inline uint8_t ReflowProfile::getSegmentCount() const {
    return _segmentCount;
  }
}
