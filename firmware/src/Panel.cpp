/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#include "Application.h"


namespace awreflow {


  /*
   * Constructor
   */

  Panel::Panel() {

    // declare a panel

    _accessMode=new LcdAccessMode;
    _gl=new LcdPanel(*_accessMode);

    // apply the gamma curve. Note that gammas are panel specific. This curve is appropriate
    // to a replacement (non-original) panel obtained from ebay.

    uint8_t levels[13]={ 0xe,0,1,1,0,0,0,0,0,0,3,4,0 };
    R61523Gamma gamma(levels);
    _gl->applyGamma(gamma);

    // create the default backlight and leave it switched off for now

    _backlight=new LcdBacklight(*_accessMode);

    // clear to black while the lights are out

    _gl->setBackground(ColourNames::BLACK);
    _gl->clearScreen();
  }
}

