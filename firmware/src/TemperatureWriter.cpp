/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#include "Application.h"


namespace awreflow {


  /*
   * Constructor
   */

  TemperatureWriter::TemperatureWriter(Panel::tCOLOUR bg,const NumberWriter::Digit *digits,uint8_t height)
    : IntegerNumberWriter(bg,digits,height),
      _lastWidth(0) {
  }


  /*
   * Redraw the control
   */

  void TemperatureWriter::redraw(FlashGraphics& flash,const Point& p,uint32_t value) {

    uint16_t width;

    // write the number

    IntegerNumberWriter::write(flash,p,value);
    width=IntegerNumberWriter::write(flash,p,value);

    // write the degrees C symbol

    flash.drawBitmap(
        Rectangle(p.X+width,p.Y,_digits[10].Width,_height),
        _digits[10].FlashAddress,
        _digits[10].Length);

    width+=_digits[10].Width;

    // erase any background overhang from last time

    if(width<_lastWidth) {

      Panel::LcdPanel& gl(flash.getGraphicsLibrary());

      gl.setBackground(_backgroundColour);
      gl.clearRectangle(Rectangle(p.X+width,p.Y,_lastWidth-width,_height));
    }

    _lastWidth=width;
  }
}
