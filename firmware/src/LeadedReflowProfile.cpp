/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#include "Application.h"


namespace awreflow {

  static const ReflowProfile::Segment ProfileSegments[]= {
    { 90, 150 },
    { 90, 180 },
    { 20, 210 },
    { 20, 210 },
    { 20, 180 },
    { 30, 25  }
  };


  /*
   * Constructor
   */

  LeadedReflowProfile::LeadedReflowProfile()
    : ReflowProfile(ProfileSegments,sizeof(ProfileSegments)/sizeof(ProfileSegments[0])) {
  }
}
