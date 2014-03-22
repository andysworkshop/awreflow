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

  static const NumberWriter::Digit TemperatureDigits[10]=
  {
    { FlashInfo::N0_BLUE::OFFSET,FlashInfo::N0_BLUE::LENGTH,FlashInfo::N0_BLUE::WIDTH },
    { FlashInfo::N1_BLUE::OFFSET,FlashInfo::N1_BLUE::LENGTH,FlashInfo::N1_BLUE::WIDTH },
    { FlashInfo::N2_BLUE::OFFSET,FlashInfo::N2_BLUE::LENGTH,FlashInfo::N2_BLUE::WIDTH },
    { FlashInfo::N3_BLUE::OFFSET,FlashInfo::N3_BLUE::LENGTH,FlashInfo::N3_BLUE::WIDTH },
    { FlashInfo::N4_BLUE::OFFSET,FlashInfo::N4_BLUE::LENGTH,FlashInfo::N4_BLUE::WIDTH },
    { FlashInfo::N5_BLUE::OFFSET,FlashInfo::N5_BLUE::LENGTH,FlashInfo::N5_BLUE::WIDTH },
    { FlashInfo::N6_BLUE::OFFSET,FlashInfo::N6_BLUE::LENGTH,FlashInfo::N6_BLUE::WIDTH },
    { FlashInfo::N7_BLUE::OFFSET,FlashInfo::N7_BLUE::LENGTH,FlashInfo::N7_BLUE::WIDTH },
    { FlashInfo::N8_BLUE::OFFSET,FlashInfo::N8_BLUE::LENGTH,FlashInfo::N8_BLUE::WIDTH },
    { FlashInfo::N9_BLUE::OFFSET,FlashInfo::N9_BLUE::LENGTH,FlashInfo::N9_BLUE::WIDTH }
  };


  /*
   * Constructor
   */

  BlueIntegerWriter::BlueIntegerWriter(uint32_t value,uint32_t minvalue,uint32_t maxvalue,const Point& p)
    : IntegerNumberWriter(0x2e5fae,TemperatureDigits,21),
      _location(p),
      _value(value),
      _min(minvalue),
      _max(maxvalue) {
  }


  /*
   * Redraw the control
   */

  void BlueIntegerWriter::redraw(Panel& panel) {

    // declare the flash device

    Flash flash(panel);

    // write the number

    IntegerNumberWriter::write(flash,_location,_value);
  }
}
