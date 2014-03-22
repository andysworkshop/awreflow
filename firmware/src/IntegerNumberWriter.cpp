/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#include "Application.h"


namespace awreflow {

  /**
   * Constructor
   */

  IntegerNumberWriter::IntegerNumberWriter(Panel::tCOLOUR bgColour,const Digit *digits,uint8_t height)
    : NumberWriter(bgColour,digits,height) {
  }


  /*
   * Write out the number and return the width in pixels
   */

  uint16_t IntegerNumberWriter::write(Flash& flash,const Point& p,uint32_t number) {

    char buffer[10];

    // convert to ascii and write

    StringUtil::modp_uitoa10(number,buffer);
    return NumberWriter::write(flash,p,buffer);
  }
}
