/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#include "Application.h"


namespace awreflow {

  static const ReflowProfile::Segment ProfileSegments[]= {
    { 90, 150 },        // pre-heating zone
    { 180, 217 },
    { 200, 240 },       // reflow zone
    { 220, 240 },
    { 240, 217 },
    { 270, 25  }        // cool down
  };


  /*
   * Constructor
   */

  LeadFreeReflowProfile::LeadFreeReflowProfile()
    : ReflowProfile(
        ProfileSegments,
        sizeof(ProfileSegments)/sizeof(ProfileSegments[0]),
        240,
        270) {
  }
}


