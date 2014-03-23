/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#include "Application.h"


namespace awreflow {

  static const ReflowProfile::Segment ProfileSegments[]= {
    { 90,  150 },       // pre-heating zone
    { 180, 180 },
    { 200, 210 },       // reflow zone
    { 220, 210 },
    { 240, 180 },
    { 270, 25  }        // cool down
  };


  /*
   * Constructor
   */

  LeadedReflowProfile::LeadedReflowProfile()
    : ReflowProfile(
        ProfileSegments,
        sizeof(ProfileSegments)/sizeof(ProfileSegments[0]),
        210,
        270) {
  }
}
