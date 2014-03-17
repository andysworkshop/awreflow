/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
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
      uint16_t write(Flash& flash,const Point& p,const char *buffer) const;

    public:
      NumberWriter(Panel::tCOLOUR bgColour,const Digit *digits,uint8_t height);
  };
}
