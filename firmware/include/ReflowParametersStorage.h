/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#pragma once


namespace awreflow {

  /*
   * The reflow parameters are saved to, and written from the last page in flash
   */

  class ReflowParametersStorage {

    public:
      static bool write(const ReflowParameters& params);
      static bool read(ReflowParameters& params);
  };
}
