/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#pragma once


namespace awreflow {


  /**
   * An extension of NumberWriter to write out 32-bit decimal integers. This is intended
   * for areas of the display that need to show temperatures or seconds
   */

  class IntegerNumberWriter : public NumberWriter {

    public:
      IntegerNumberWriter(Panel::tCOLOUR bgColour,const Digit *digits,uint8_t height);

      uint16_t write(Flash& flash,const Point& p,uint32_t number);
  };
}
