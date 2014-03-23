/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#pragma once


namespace awreflow {


  /*
   * Main class. Handles initialisation and the user's workflow through
   * the system.
   */

  class Main {

    protected:
      void setDefaultPins() const;

    public:
      void run();
  };
}
