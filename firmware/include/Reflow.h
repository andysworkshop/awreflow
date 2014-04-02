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

    public:

      /*
       * Actions that can happen as a result of the update() call.
       */

      enum UpdateResult {
        NOTHING,
        UPDATED,
        STOP
      };

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

      DefaultTemperatureReader _temperatureReader;

      const ReflowProfile& _profile;
      Pid _pid;

      uint32_t _lastTick;                   // the last millisecond timer value
      uint16_t _currentSeconds;             // elapsed seconds counter
      uint8_t _currentSegment;              // the reflow segment we're currently processing
      Pid::variable_t _desiredTemperature;  // the current desired temperature
      Pid::variable_t _currentTemperature;  // the current actual temperature
      Pid::variable_t _temperatureStep;     // how much to add each second to the desired temperature
      ReflowResults _results;               // the results of the reflow

    public:
      Reflow(const ReflowProfile& profile,const ReflowParameters& params);
      ~Reflow();

      void start();
      void stop();
      UpdateResult update();

      uint16_t getCurrentSeconds() const;
      const Pid::variable_t& getCurrentTemperature() const;
      const Pid::variable_t& getDesiredTemperature() const;

      void transmitResults() const;
  };


  /*
   * Get the current elapsed seconds
   */

  inline uint16_t Reflow::getCurrentSeconds() const {
    return _currentSeconds;
  }


  /*
   * Get the current temperature
   */

  inline const Pid::variable_t& Reflow::getCurrentTemperature() const {
    return _currentTemperature;
  }


  /*
   * Get the desired temperature
   */

  inline const Pid::variable_t& Reflow::getDesiredTemperature() const {
    return _desiredTemperature;
  }


  /*
   * Get the reflow results
   */

  inline void Reflow::transmitResults() const {
    _results.transmit(_profile);
  }
}
