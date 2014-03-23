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

  Reflow::Reflow() {

    /*
     * Set an up-timer up to tick at 10kHz with an auto-reload value of 99
     * The timer will count from 0 to 99 inclusive then reset back to 0.
     * It will take 10ms to do this (100Hz).
     */

    _timer.setTimeBaseByFrequency(10000,99);

    /*
     * Initialise the channel 4 output compare value to 99 with the default
     * action of toggle.
     */

    _timer.initCompare(99);

    /*
     * Set up for PWM output with an initial duty cycle of zero
     */

    _timer.initCompareForPwmOutput(0);
  }


  /*
   * Destructor: ensure the timer is stopped
   */

  Reflow::~Reflow() {
    stop();
  }


  /*
   * Start the reflow process
   */

  void Reflow::start() {
    _timer.enablePeripheral();
  }


  /*
   * Stop the reflow process
   */

  void Reflow::stop() {

    // switch off the duty cycle and disable the peripheral

    _timer.setDutyCycle(0);
    _timer.disablePeripheral();
  }
}
