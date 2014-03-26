/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#pragma once


namespace awreflow {


  /**
   * Derivation of the integer number writer for a temperature display.
   */

  class TemperatureWriter : public IntegerNumberWriter {

    protected:
      uint16_t _lastWidth;

    public:
      TemperatureWriter(Panel::tCOLOUR bg,const NumberWriter::Digit *digits,uint8_t height);

      void redraw(FlashGraphics& flash,const Point& p,uint32_t value);
  };
}
