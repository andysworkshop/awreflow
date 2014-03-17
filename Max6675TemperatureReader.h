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

    enum {
      Port_NSS = GPIOA_BASE,
      Port_SCK = GPIOA_BASE,
      Port_MISO = GPIOA_BASE,
      Port_MOSI = GPIOA_BASE,

      Pin_NSS  = GPIO_Pin_4,
      Pin_SCK  = GPIO_Pin_5,
      Pin_MISO = GPIO_Pin_6,
      Pin_MOSI = GPIO_Pin_7
    };

    Result readTemperature();
  };


  /*
   * Declare this temperature reader as the one we're going to use
   */

  typedef Max6675TemperatureReader DefaultTemperatureReader;
}
