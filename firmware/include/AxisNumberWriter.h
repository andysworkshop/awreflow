/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#pragma once


namespace awreflow {


  /**
   * Derivation of the integer number writer for the numbers plotted
   * against the reflow axes
   */

  class AxisNumberWriter : public IntegerNumberWriter {

    public:
      AxisNumberWriter();
  };
}
