/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#include "Application.h"


namespace awreflow {


  /*
   * The 10 digits for the temperature display
   */

  static const Digit TemperatureDigits[10]=
  {
    { FlashInfo::N0_GREY::OFFSET,FlashInfo::N0_GREY::LENGTH,FlashInfo::N0_GREY::WIDTH },
    { FlashInfo::N1_GREY::OFFSET,FlashInfo::N0_GREY::LENGTH,FlashInfo::N0_GREY::WIDTH },
    { FlashInfo::N2_GREY::OFFSET,FlashInfo::N0_GREY::LENGTH,FlashInfo::N0_GREY::WIDTH },
    { FlashInfo::N3_GREY::OFFSET,FlashInfo::N0_GREY::LENGTH,FlashInfo::N0_GREY::WIDTH },
    { FlashInfo::N4_GREY::OFFSET,FlashInfo::N0_GREY::LENGTH,FlashInfo::N0_GREY::WIDTH },
    { FlashInfo::N5_GREY::OFFSET,FlashInfo::N0_GREY::LENGTH,FlashInfo::N0_GREY::WIDTH },
    { FlashInfo::N6_GREY::OFFSET,FlashInfo::N0_GREY::LENGTH,FlashInfo::N0_GREY::WIDTH },
    { FlashInfo::N7_GREY::OFFSET,FlashInfo::N0_GREY::LENGTH,FlashInfo::N0_GREY::WIDTH },
    { FlashInfo::N8_GREY::OFFSET,FlashInfo::N0_GREY::LENGTH,FlashInfo::N0_GREY::WIDTH },
    { FlashInfo::N9_GREY::OFFSET,FlashInfo::N0_GREY::LENGTH,FlashInfo::N0_GREY::WIDTH }
  };


  /*
   * Constructor
   */

  TemperatureControlWriter::TemperatureControlWriter()
    : IntegerNumberWriter(0x7a828c,TemperatureDigits,16) {
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
        width=IntegerNumberWriter::write(flash,p,result.Result);
        flash.drawBitmap(
            Rectangle(p.X+width,p.Y,FlashInfo::DEGREESC::WIDTH,FlashInfo::DEGREESC::HEIGHT),
            FlashInfo::DEGREESC::OFFSET,
            FlashInfo::DEGREESC::LENGTH);
        break;
    }
  }
}
