/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#pragma once


namespace awreflow {


  /*
   * CRTP base class for a temperature reader. Implementation will be provided for the MAX6675
   * and MAX31855 devices.
   */

  template<class TImpl>
  struct TemperatureReader {
    uint16_t readTemperature() {
      return static_cast<TImpl *>(this)->readTemperature();
    }
  };
}
