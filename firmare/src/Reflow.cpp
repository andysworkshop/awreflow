/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#include "Application.h"


namespace awreflow {

  /*
   * Run the application
   */

  void Reflow::run() {

    // set default pin state

    setDefaultPins();

    // declare (and construct) the objects that will live throughout the application

    Buttons buttons;
    Panel panel;

    // these objects will be created, used and destroyed when they're not required
    // to ensure we minimise our concurrent use of that precious 8Kb of SRAM

    ControlPage *controlPage;
    SplashScreen *splashScreen;

    // show the splash screen

    splashScreen=new SplashScreen;
    splashScreen->show(panel);
    delete splashScreen;

    for(;;) {

      // create the options page and run it. it won't ever return unless the user
      // selects a cooking program and opts to proceed.

      controlPage=new ControlPage(panel,buttons);
      controlPage->run();
      delete controlPage;
    }
  }


  /*
   * Set up any pins that need to have their modes set up front
   */

  void Reflow::setDefaultPins() const {

    // the two SPI NSS pins need to be set up and pulled high

    GpioA<DefaultDigitalOutputFeature<3,4>> pa;

    pa[3].set();
    pa[4].set();
  }
}


/*
 * Main entry point
 */

int main() {

  // we're using interrupts, initialise NVIC

  Nvic::initialise();

  // initialise the millisecond timer

  MillisecondTimer::initialise();

  // declare and run the application

  awreflow::Reflow app;
  app.run();

  // not reached
  return 0;
}
