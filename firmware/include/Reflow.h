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
       * The relay output is on PA11. One of PA11's alternate functions is TIM1 channel 4 output.
       * We'll use that facility to produce a hardware-controlled PWM waveform on PA11.
       */

      Timer1<
        Timer1InternalClockFeature,       // the timer clock source is internal
        TimerChannel4Feature,             // we're going to use channel 4
        Timer1GpioFeature<                // we want to output something to GPIO
          TIMER_REMAP_NONE,               // the GPIO output will not be remapped
          TIM1_CH4_OUT                    // we will output channel 4 to GPIO
        >
      > _relayTimer;

      /*
       * We'll sample the temperature and run the PID operations once per second. We want to do all
       * this asynchronously so lets set up TIM14 to fire a 1Hz interrupt that we'll use to operate
       * the PID algorithm and make the results available to the ReflowPage.
       */

      Timer14<
        Timer14InternalClockFeature,
        Timer14InterruptFeature
      > _perSecondTimer;

      DefaultTemperatureReader _temperatureReader;

      const ReflowProfile& _profile;
      Pid _pid;

      volatile bool _ticked;                // the per-second timer ticked
      uint16_t _currentSeconds;             // elapsed seconds counter
      uint8_t _currentSegment;              // the reflow segment we're currently processing
      Pid::variable_t _desiredTemperature;  // the current desired temperature
      Pid::variable_t _currentTemperature;  // the current actual temperature
      Pid::variable_t _temperatureStep;     // how much to add each second to the desired temperature

    protected:
      void onInterrupt(TimerEventType tet,uint8_t /* timerNumber */);

    public:
      Reflow(const ReflowProfile& profile,const ReflowParameters& params);
      ~Reflow();

      void start();
      void stop();

      bool update();
  };
}
