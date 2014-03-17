/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#include "Application.h"


namespace awreflow {

  /**
   * Constructor
   */

  NumberWriter::NumberWriter(Panel::tCOLOUR bgColour,const Digit *digits,uint8_t height)
    : _backgroundColour(bgColour),
      _height(height),
      _digits(digits),
      _lastWidth(0) {
  }


  /*
   * Write out the number and return the width in pixels. The previous number, if any, is completely erased
   */

  uint16_t NumberWriter::write(Flash& flash,const Point& p,const char *buffer) const {

    const char *ptr;
    const Digit *digit;
    Rectangle rc;
    int origin,width;

    // set up the numbers

    rc.X=origin=p.X;
    rc.Y=p.Y;
    rc.Height=_height;

    // parse the buffer

    for(ptr=buffer;*ptr;ptr++) {

      // if it's not a digit then it's the point

      if(*ptr>='0' && *ptr<='9')
        digit=&_digits[*ptr-'0'];
      else
        digit=&_digits[10];

      rc.Width=digit->Width;

      // draw it

      flash.drawBitmap(rc,digit->FlashAddress,digit->Length);

      // update

      rc.X+=rc.Width;
    }

    // get the width

    width=rc.X-origin;

    // if the new width is less than the previous width then we need to wipe out the overflow

    if(_lastWidth && width<_lastWidth) {

      Panel::LcdPanel& gl(flash.getGraphicsLibrary());

      rc.Width=_lastWidth-width;
      gl.setBackground(_backgroundColour);
      gl.clearRectangle(rc);
    }

    // return the width

    return width;
  }
}
