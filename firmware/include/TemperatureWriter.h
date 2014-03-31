/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#pragma once


namespace awreflow {


  /**
   * Derivation of the integer number writer for a temperature display. The number
   * digits array contains the digits 0..9 in the respective array positions. The degrees-C
   * symbol is at position 10 and the "broken" symbol is at position 11.
   */

  class TemperatureWriter : public IntegerNumberWriter {

    protected:
      uint16_t _lastWidth;
      Size _brokenIconOffset;

      /*
       * Positions in the digits array
       */

      enum {
        DEGREES_C = 10,
        BROKEN = 11
      };

      /*
       * Constant height for the broken icon
       */

      enum {
        BROKEN_HEIGHT = 26
      };

    public:
      TemperatureWriter(
          Panel::tCOLOUR bg,
          const NumberWriter::Digit *digits,
          uint8_t height,
          const Size& brokenIconOffset);

      void redraw(FlashGraphics& flash,const Point& p,const DefaultTemperatureReader::Result& result);
  };
}
