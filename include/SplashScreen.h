/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#pragma once


namespace awreflow {

  class Panel;


  /*
   * Display the opening splash screen for a few seconds
   */

  class SplashScreen {

    protected:
      enum {
        DISPLAY_HOLD_MILLIS = 5000
      };

    public:
      void show(Panel& panel);
  };
}
