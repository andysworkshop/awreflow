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

  TemperatureWriter::TemperatureWriter(Panel::tCOLOUR bg,const NumberWriter::Digit *digits,uint8_t height,const Size& brokenIconOffset)
    : IntegerNumberWriter(bg,digits,height),
      _lastWidth(0),
      _brokenIconOffset(brokenIconOffset) {
  }


  /*
   * Redraw the control
   */

  void TemperatureWriter::redraw(FlashGraphics& flash,const Point& p,const DefaultTemperatureReader::Result& result) {

    uint16_t width;

    if(result.Status==DefaultTemperatureReader::Result::NO_ERROR) {

      // write the number

      width=IntegerNumberWriter::write(flash,p,result.Temperature);

      // write the degrees C symbol

      flash.drawBitmap(
          Rectangle(p.X+width,p.Y,_digits[DEGREES_C].Width,_height),
          _digits[DEGREES_C].FlashAddress,
          _digits[DEGREES_C].Length);

      width+=_digits[DEGREES_C].Width;

      // erase any background overhang from last time

      if(width<_lastWidth) {

        Panel::LcdPanel& gl(flash.getGraphicsLibrary());

        gl.setBackground(_backgroundColour);
        gl.clearRectangle(Rectangle(p.X+width,p.Y,_lastWidth-width,_height));
      }

      _lastWidth=width;
    }
    else {

      // there's something wrong with the comms, show a "broken" icon

      flash.drawBitmap(
          Rectangle(p.X+_brokenIconOffset.Width,p.Y+_height-BROKEN_HEIGHT+_brokenIconOffset.Height,_digits[BROKEN].Width,BROKEN_HEIGHT),
          _digits[BROKEN].FlashAddress,
          _digits[BROKEN].Length);
    }
  }
}
