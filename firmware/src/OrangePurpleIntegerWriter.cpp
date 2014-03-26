/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#include "Application.h"


namespace awreflow {

/*
 * The 10 digits for the number display
 */

  static const NumberWriter::Digit Digits[10]=
  {
    { FlashInfo::N0_ORANGE_PURPLE::OFFSET,FlashInfo::N0_ORANGE_PURPLE::LENGTH,FlashInfo::N0_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N1_ORANGE_PURPLE::OFFSET,FlashInfo::N1_ORANGE_PURPLE::LENGTH,FlashInfo::N1_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N2_ORANGE_PURPLE::OFFSET,FlashInfo::N2_ORANGE_PURPLE::LENGTH,FlashInfo::N2_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N3_ORANGE_PURPLE::OFFSET,FlashInfo::N3_ORANGE_PURPLE::LENGTH,FlashInfo::N3_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N4_ORANGE_PURPLE::OFFSET,FlashInfo::N4_ORANGE_PURPLE::LENGTH,FlashInfo::N4_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N5_ORANGE_PURPLE::OFFSET,FlashInfo::N5_ORANGE_PURPLE::LENGTH,FlashInfo::N5_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N6_ORANGE_PURPLE::OFFSET,FlashInfo::N6_ORANGE_PURPLE::LENGTH,FlashInfo::N6_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N7_ORANGE_PURPLE::OFFSET,FlashInfo::N7_ORANGE_PURPLE::LENGTH,FlashInfo::N7_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N8_ORANGE_PURPLE::OFFSET,FlashInfo::N8_ORANGE_PURPLE::LENGTH,FlashInfo::N8_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N9_ORANGE_PURPLE::OFFSET,FlashInfo::N9_ORANGE_PURPLE::LENGTH,FlashInfo::N9_ORANGE_PURPLE::WIDTH }
  };


  /*
   * Constructor
   */

  OrangePurpleIntegerWriter::OrangePurpleIntegerWriter()
    : IntegerNumberWriter(0x9f489e,Digits,15) {
  }


  /*
   * Redraw the control
   */

  void OrangePurpleIntegerWriter::redraw(FlashGraphics& flash,const Point& p,uint32_t value) {

    // write the number

    IntegerNumberWriter::write(flash,p,value);
  }
}
