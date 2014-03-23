/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#pragma once


namespace awreflow {

  /**
   * This base class manages writing out numbers to the display. The digits are stored in flash
   * anti-aliased into the desired background colour. This class should be instantiated once per
   * area of the screen where a number is expected to be maintained.
   */

  class NumberWriter {

    public:
      struct Digit {
        uint32_t FlashAddress;      // flash address
        uint16_t Length;            // byte size of the digit
        uint8_t Width;              // width in pixels
      };

    protected:
      Panel::tCOLOUR _backgroundColour;   // background colour
      uint8_t _height;                    // pixel height of the digits
      const Digit *_digits;               // 0..9 and '.' (dec point). 11 "digits" in total.
      uint16_t _lastWidth;                // last output width for this number

    protected:
      uint16_t write(FlashGraphics& flash,const Point& p,const char *buffer);

    public:
      NumberWriter(Panel::tCOLOUR bgColour,const Digit *digits,uint8_t height);
  };
}
