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

  IntegerNumberWriter::IntegerNumberWriter(Panel::tCOLOUR bgColour,Digit *digits,uint8_t height)
    : NumberWriter(bgColour,digits,height) {
  }


  /*
   * Write out the number and return the width in pixels
   */

  uint16_t IntegerNumberWriter::write(Flash& flash,const Point& p,uint32_t number) const {

    char buffer[10];

    // convert to ascii and write

    StringUtil::modp_uitoa10(number,buffer);
    return NumberWriter::write(flash,p,buffer);
  }
}
