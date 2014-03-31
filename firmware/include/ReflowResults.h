/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#pragma once


namespace awreflow {

  /*
   * Class to collect the results of a reflow ready for saving to USART. The results are
   * stored as a sequence of actual temperature readings. One per second from the start to
   * the end or when the user hits stop. This class trades increased flash usage for lower
   * SRAM usage (we recalculate the desired temperature).
   *
   * The memory requirements for a 270s profile is 270*2 = 540 bytes. The profile for the
   * USART is 9600bps, 8/N/1.
   */

  class ReflowResults {

    protected:
      scoped_array<uint16_t> _results;
      uint16_t _numDataPoints;

    public:
      void start(uint16_t maxDataPoints);
      void update(uint16_t temperature);

      void transmit(const ReflowProfile& profile) const;
  };


  /*
   * Add a new data point to the array
   */

  inline void ReflowResults::update(uint16_t temperature) {
    _results[_numDataPoints++]=temperature;
  }
}
