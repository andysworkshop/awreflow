/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#pragma once


namespace awreflow {


  /*
   * Implementation of the temperature reader for the MAX6675
   */

  struct Max6675TemperatureReader : TemperatureReader<Max6675TemperatureReader> {
    uint16_t readTemperature();
  };


  /*
   * Declare this temperature reader as the one we're going to use
   */

  typedef Max6675TemperatureReader DefaultTemperatureReader;
}
