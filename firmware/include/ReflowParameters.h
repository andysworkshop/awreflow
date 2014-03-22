/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#pragma once


namespace awreflow {

  /*
   * Parameters gathered by the control page and used by
   * the reflow page
   */

  struct ReflowParameters {
    uint32_t P,I,D;
    bool Leaded;
  };
}

