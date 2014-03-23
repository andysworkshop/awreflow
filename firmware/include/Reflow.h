/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#include "Application.h"


namespace awreflow {


  /*
   * The reflow class manages the actual PID-controlled reflow process. It takes per-second ticks
   * as input and will apply PID-controlled adjustments to the relay output
   */

  class Reflow {

    protected:

      /*
       * The relay output is on PA11. One of PA11's alternate functions is timer1 channel 4 output.
       * We'll use that facility to produce a hardware-controlled PWM waveform on PA11.
       */

      typedef Timer1<
        Timer1InternalClockFeature,       // the timer clock source is internal
        TimerChannel4Feature,             // we're going to use channel 4
        Timer1GpioFeature<                // we want to output something to GPIO
          TIMER_REMAP_NONE,               // the GPIO output will not be remapped
          TIM1_CH4_OUT                    // we will output channel 4 to GPIO
        >
      > MyTimer;

      MyTimer _timer;

    public:
      Reflow();
      ~Reflow();

      void start();
      void stop();
      void tick();
  };
}
