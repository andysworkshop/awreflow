/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#pragma once


namespace awreflow {


  /**
   * Derivation of the integer number writer for writing numbers with a purple
   * background. e.g. for the oven temperature on the reflow screen
   */

  class PurpleIntegerWriter : public IntegerNumberWriter {

    protected:
      Point _location;

    public:
      PurpleIntegerWriter();
      void redraw(FlashGraphics& flash,const Point& p,uint32_t value);
  };
}
