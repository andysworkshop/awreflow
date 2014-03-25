/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#pragma once


namespace awreflow {


  /*
   * Dummy implementation of the temperature reader for testing that just
   * returns a constant "room temperature". Not used in the actual code.
   */

  struct DummyTemperatureReader : TemperatureReader<DummyTemperatureReader> {

    enum {
      ROOM_TEMPERATURE = 25
    };

    Result readTemperature() {
      return { ROOM_TEMPERATURE, Result::NO_ERROR };
    }
  };
}
