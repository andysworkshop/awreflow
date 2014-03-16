/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#include "Application.h"


namespace awreflow {


  /*
   * Show the splash screen and hold for 5 seconds
   */

  void SplashScreen::show(Panel& panel) {

    Flash flash(panel);

    // lights off (this is an async fade)

    panel.setBacklight(0);
    MillisecondTimer::delay(1000);

    // draw the splash

    flash.drawBitmap(
        Rectangle(0,0,FlashInfo::Logo::WIDTH,FlashInfo::Logo::HEIGHT),
        FlashInfo::Logo::OFFSET,
        FlashInfo::Logo::LENGTH);

    // lights on and hold

    panel.setBacklight(100);
    MillisecondTimer::delay(DISPLAY_HOLD_MILLIS);
  }
}
