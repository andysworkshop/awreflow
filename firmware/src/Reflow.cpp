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

  Reflow::Reflow(const ReflowProfile& profile,const ReflowParameters& params)
    : _profile(profile),
      _pid(params.P,params.I,params.D),
      _paused(false),
      _relayPercentage(0) {

    /*
     * Set an up-timer up to tick at 10kHz with an auto-reload value of 4999
     * The timer will count from 0 to 4999 inclusive then reset back to 0.
     * It will take 500ms to do this (2Hz).
     */

    _relayTimer.setTimeBaseByFrequency(10000,4999);

    /*
     * Initialise the channel 4 output compare value to 4999 with the default
     * action of toggle.
     */

    _relayTimer.initCompare(4999);

    // set up for PWM output with an initial duty cycle of zero

    _relayTimer.initCompareForPwmOutput(0);
  }


  /*
   * Destructor: ensure the timers are stopped
   */

  Reflow::~Reflow() {
    stop();
  }


  /*
   * Start the reflow process
   */

  void Reflow::start() {

    // algorithm operational parameters. set up to start at the current ambient
    // temperature with a target of whatever the first segment ends at.

    _currentSeconds=0;
    _currentSegment=0;
    _currentTemperature=_temperatureReader.readTemperature().Temperature;
    _desiredTemperature=25;       // all profiles start at 25
    _temperatureStep=(_profile[0].Temperature-_desiredTemperature)/_profile[0].EndingTime;
    _relayPercentage=0;

    // reset the last tick value

    _lastTick=MillisecondTimer::millis();

    // enable the timer for the PWM output on PA11

    _relayTimer.setDutyCycle(0);
    _relayTimer.enablePeripheral();
  }


  /*
   * Stop the reflow process
   */

  void Reflow::stop() {

    // switch off the duty cycle and disable the peripheral

    _relayTimer.setDutyCycle(0);
    _relayTimer.disablePeripheral();
    _relayPercentage=0;
  }


  /*
   * This needs to be called more frequently than 1Hz. It checks to see if one second has
   * passed since the last call and will do the PID update if it has. Returns an UpdateResult
   * value that declares what's been done.
   */

  Reflow::UpdateResult Reflow::update() {

    // has a second elapsed since we were here last?

    if(!MillisecondTimer::hasTimedOut(_lastTick,1000))
      return NOTHING;

    // reset for the next update (now, not after we've burned some cycles doing our update)

    _lastTick=MillisecondTimer::millis();

    // get a pointer to the current segment

    const ReflowProfile::Segment *s=&_profile[_currentSegment];

    // if we're in the first second and we are below the starting temperature then auto-pause
    // until we've heated up to the starting temperature (25 degrees)

    if(_currentSeconds==0)
      _paused=_currentTemperature<_desiredTemperature;

    // advance if we're not paused

    if(!_paused) {

      // update seconds and see if we've hit the end

      if(s->EndingTime==_currentSeconds) {

        // we have hit the ending time of the current segment. if this is the last segment
        // then the whole process has completed

        _currentSegment++;
        if(_currentSegment==_profile.getSegmentCount())
          return STOP;

        // we're in a new segment. set up the parameters for this leg.

        s=&_profile[_currentSegment];
        _temperatureStep=(s->Temperature-_desiredTemperature)/(s->EndingTime-_currentSeconds);
      }

      // update seconds and desired temperature

      _currentSeconds++;
      _desiredTemperature+=_temperatureStep;
    }

    // take a temperature reading and abort if there's a hardware failure

#if 1
    DefaultTemperatureReader::Result result(_temperatureReader.readTemperature());
#else
    DefaultTemperatureReader::Result result;

    result.Status=DefaultTemperatureReader::Result::NO_ERROR;
    result.Temperature=_desiredTemperature+((rand() % 4)-2);
#endif

    if(result.Status!=DefaultTemperatureReader::Result::NO_ERROR)
      return STOP;

    _currentTemperature=result.Temperature;

    // run the PID algorithm and set the relay PWM value from the output

    _relayPercentage=_pid.update(_desiredTemperature,_currentTemperature);
    _relayTimer.setDutyCycle(_relayPercentage);

    // continue

    return UPDATED;
  }
}
