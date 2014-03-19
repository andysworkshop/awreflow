/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#include "Application.h"


namespace awreflow {

  /*
   * The type of profile, lead-free or leaded
   */

  enum class ProfileType : uint8_t {
    LEAD_FREE,
    LEADED
  };
}
