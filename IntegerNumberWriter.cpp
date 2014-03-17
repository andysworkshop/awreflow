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

  IntegerNumberWriter::IntegerNumberWriter(Flash& flash,Panel::tCOLOUR bgColour,Digit *digits,uint8_t height)
    : NumberWriter(flash,bgColour,digits,height) {
  }


  /*
   * Write out the number and return the width in pixels
   */

  uint16_t IntegerNumberWriter::write(uint16_t number) {

    char buffer[10];
    const char *ptr;

    // convert to ascii

    StringUtil::modp_uitoa10(number,buffer);

    // parse the buffer

    for(ptr=buffer;*ptr;ptr++) {

    }
  }
}
