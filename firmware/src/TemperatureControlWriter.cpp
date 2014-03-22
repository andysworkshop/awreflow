/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#include "Application.h"


namespace awreflow {


  /*
   * The 10 digits for the temperature display
   */

  static const NumberWriter::Digit TemperatureDigits[10]=
  {
    { FlashInfo::N0_GREY::OFFSET,FlashInfo::N0_GREY::LENGTH,FlashInfo::N0_GREY::WIDTH },
    { FlashInfo::N1_GREY::OFFSET,FlashInfo::N1_GREY::LENGTH,FlashInfo::N1_GREY::WIDTH },
    { FlashInfo::N2_GREY::OFFSET,FlashInfo::N2_GREY::LENGTH,FlashInfo::N2_GREY::WIDTH },
    { FlashInfo::N3_GREY::OFFSET,FlashInfo::N3_GREY::LENGTH,FlashInfo::N3_GREY::WIDTH },
    { FlashInfo::N4_GREY::OFFSET,FlashInfo::N4_GREY::LENGTH,FlashInfo::N4_GREY::WIDTH },
    { FlashInfo::N5_GREY::OFFSET,FlashInfo::N5_GREY::LENGTH,FlashInfo::N5_GREY::WIDTH },
    { FlashInfo::N6_GREY::OFFSET,FlashInfo::N6_GREY::LENGTH,FlashInfo::N6_GREY::WIDTH },
    { FlashInfo::N7_GREY::OFFSET,FlashInfo::N7_GREY::LENGTH,FlashInfo::N7_GREY::WIDTH },
    { FlashInfo::N8_GREY::OFFSET,FlashInfo::N8_GREY::LENGTH,FlashInfo::N8_GREY::WIDTH },
    { FlashInfo::N9_GREY::OFFSET,FlashInfo::N9_GREY::LENGTH,FlashInfo::N9_GREY::WIDTH }
  };


  /*
   * Constructor
   */

  TemperatureControlWriter::TemperatureControlWriter()
    : IntegerNumberWriter(0x7a828c,TemperatureDigits,16),
      _lastWidth(0) {
  }


  /*
   * Draw the display
   */

  void TemperatureControlWriter::redraw(Panel& panel) {

    Point p;
    uint16_t width;

    // take a reading

    DefaultTemperatureReader reader;
    DefaultTemperatureReader::Result result=reader.readTemperature();

    // declare the flash device

    Flash flash(panel);

    // the position

    p.X=352;
    p.Y=317;

    switch(result.Status) {

      case DefaultTemperatureReader::Result::NO_ERROR:
        width=IntegerNumberWriter::write(flash,p,result.Temperature);
        flash.drawBitmap(
            Rectangle(p.X+width,p.Y,FlashInfo::DEGREESC::WIDTH,FlashInfo::DEGREESC::HEIGHT),
            FlashInfo::DEGREESC::OFFSET,
            FlashInfo::DEGREESC::LENGTH);
        width+=FlashInfo::DEGREESC::WIDTH;
        break;

      default:
        width=0;
        break;
    }

    if(width<_lastWidth) {

      Panel::LcdPanel& gl(panel.getGraphicsLibrary());

      gl.setBackground(0x7a828c);
      gl.clearRectangle(Rectangle(352+width,317,_lastWidth-width,16));
    }

    _lastWidth=width;
  }
}
