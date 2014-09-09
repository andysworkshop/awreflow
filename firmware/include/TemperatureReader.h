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
  class TemperatureReader {

    public:

      struct Result {
        uint16_t Temperature;

        enum {
          NO_ERROR,
          E_OPEN_THERMOCOUPLE,
	  E_SHORT_THERMOCOUPLE,
          E_COMMS_FAILURE
        } Status;
      };

    public:
      Result readTemperature();
  };


  /**
   * Read back the temperature from the sensor
   */

  template<class TImpl>
  inline typename TemperatureReader<TImpl>::Result TemperatureReader<TImpl>::readTemperature() {
    return static_cast<TImpl *>(this)->readTemperature();
  }
}
