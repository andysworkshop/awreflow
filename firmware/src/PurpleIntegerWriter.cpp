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
    { FlashInfo::N0_PURPLE::OFFSET,FlashInfo::N0_PURPLE::LENGTH,FlashInfo::N0_PURPLE::WIDTH },
    { FlashInfo::N1_PURPLE::OFFSET,FlashInfo::N1_PURPLE::LENGTH,FlashInfo::N1_PURPLE::WIDTH },
    { FlashInfo::N2_PURPLE::OFFSET,FlashInfo::N2_PURPLE::LENGTH,FlashInfo::N2_PURPLE::WIDTH },
    { FlashInfo::N3_PURPLE::OFFSET,FlashInfo::N3_PURPLE::LENGTH,FlashInfo::N3_PURPLE::WIDTH },
    { FlashInfo::N4_PURPLE::OFFSET,FlashInfo::N4_PURPLE::LENGTH,FlashInfo::N4_PURPLE::WIDTH },
    { FlashInfo::N5_PURPLE::OFFSET,FlashInfo::N5_PURPLE::LENGTH,FlashInfo::N5_PURPLE::WIDTH },
    { FlashInfo::N6_PURPLE::OFFSET,FlashInfo::N6_PURPLE::LENGTH,FlashInfo::N6_PURPLE::WIDTH },
    { FlashInfo::N7_PURPLE::OFFSET,FlashInfo::N7_PURPLE::LENGTH,FlashInfo::N7_PURPLE::WIDTH },
    { FlashInfo::N8_PURPLE::OFFSET,FlashInfo::N8_PURPLE::LENGTH,FlashInfo::N8_PURPLE::WIDTH },
    { FlashInfo::N9_PURPLE::OFFSET,FlashInfo::N9_PURPLE::LENGTH,FlashInfo::N9_PURPLE::WIDTH }
  };


  /*
   * Constructor
   */

  PurpleIntegerWriter::PurpleIntegerWriter()
    : IntegerNumberWriter(0x9f489e,Digits,15) {
  }


  /*
   * Redraw the control
   */

  void PurpleIntegerWriter::redraw(FlashGraphics& flash,const Point& p,uint32_t value) {

    // write the number

    IntegerNumberWriter::write(flash,p,value);
  }
}
