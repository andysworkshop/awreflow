/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#include "Application.h"


namespace awreflow {

/*
 * The 10 digits for the display
 */

  static const NumberWriter::Digit Digits[10]=
  {
    { FlashInfo::N0_BLACK::OFFSET,FlashInfo::N0_BLACK::LENGTH,FlashInfo::N0_BLACK::WIDTH },
    { FlashInfo::N1_BLACK::OFFSET,FlashInfo::N1_BLACK::LENGTH,FlashInfo::N1_BLACK::WIDTH },
    { FlashInfo::N2_BLACK::OFFSET,FlashInfo::N2_BLACK::LENGTH,FlashInfo::N2_BLACK::WIDTH },
    { FlashInfo::N3_BLACK::OFFSET,FlashInfo::N3_BLACK::LENGTH,FlashInfo::N3_BLACK::WIDTH },
    { FlashInfo::N4_BLACK::OFFSET,FlashInfo::N4_BLACK::LENGTH,FlashInfo::N4_BLACK::WIDTH },
    { FlashInfo::N5_BLACK::OFFSET,FlashInfo::N5_BLACK::LENGTH,FlashInfo::N5_BLACK::WIDTH },
    { FlashInfo::N6_BLACK::OFFSET,FlashInfo::N6_BLACK::LENGTH,FlashInfo::N6_BLACK::WIDTH },
    { FlashInfo::N7_BLACK::OFFSET,FlashInfo::N7_BLACK::LENGTH,FlashInfo::N7_BLACK::WIDTH },
    { FlashInfo::N8_BLACK::OFFSET,FlashInfo::N8_BLACK::LENGTH,FlashInfo::N8_BLACK::WIDTH },
    { FlashInfo::N9_BLACK::OFFSET,FlashInfo::N9_BLACK::LENGTH,FlashInfo::N9_BLACK::WIDTH }
  };


  /*
   * Constructor
   */

  AxisNumberWriter::AxisNumberWriter()
    : IntegerNumberWriter(ColourNames::BLACK,Digits,13) {
  }
}
