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

  void Main::run() {

    // set default pin state

    setDefaultPins();

    // declare (and construct) the objects that will live throughout the application

    Buttons buttons;
    Panel panel;

    // these objects will be created, used and destroyed when they're not required
    // to ensure we minimise our concurrent use of that precious 8Kb of SRAM

    ControlPage *controlPage;
    ReflowPage *reflowPage;

    SplashScreen *splashScreen;

    // show the splash screen

    splashScreen=new SplashScreen;
    splashScreen->show(panel);
    delete splashScreen;


    // go into a loop showing the control page followed by the reflow page

    for(;;) {

      ReflowParameters params;

      // read the parameters from flash and default them if they're not available

      if(!ReflowParametersStorage::read(params)) {
        params.P=params.I=params.D=1;
        params.Leaded=true;
      }

      // create the options page and run it. it won't return until the user
      // selects a cooking program and opts to proceed.

      controlPage=new ControlPage(panel,buttons,params);
      params=controlPage->run();
      delete controlPage;

      // attempt to store the new parameters in flash

      ReflowParametersStorage::write(params);

      // create the reflow page and run it

      reflowPage=new ReflowPage(panel,buttons,params);
      reflowPage->run();
      delete reflowPage;
    }
  }


  /*
   * Set up any pins that need to have their modes set up front
   */

  template<uint8_t... TPins>
  using InputPullDown=DigitalInputFeature<GPIO_Speed_Level_3,Gpio::PUPD_DOWN,TPins...>;

  void Main::setDefaultPins() const {

    // the two SPI NSS pins need to be set up and HIGH
    // the relay enable pin needs to be LOW

    GpioA<DefaultDigitalOutputFeature<3,4,11>> pa;

    pa[3].set();
    pa[4].set();
    pa[11].reset();

    // set the unused pins to input pull-down so anything that's floating
    // doesn't cause excessive power consumption

    GpioA<InputPullDown<8,12,15>> paUnused;
    GpioC<InputPullDown<13,15>> pcUnused;
    GpioF<InputPullDown<6,7>> pfUnused;
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

  awreflow::Main app;
  app.run();

  // not reached
  return 0;
}
