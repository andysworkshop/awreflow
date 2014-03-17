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

  NumberWriter::NumberWriter(Flash& flash,Panel::tCOLOUR bgColour,Digit *digits,uint8_t height)
    : _flash(flash),
      _backgroundColour(bgColour),
      _digits(digits),
      _height(height),
      _lastWidth(0) {
  }
}
