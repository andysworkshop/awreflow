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
      _pid(params.P,params.I,params.D) {

    /*
     * Set an up-timer up to tick at 10kHz with an auto-reload value of 99
     * The timer will count from 0 to 99 inclusive then reset back to 0.
     * It will take 10ms to do this (100Hz).
     */

    _relayTimer.setTimeBaseByFrequency(10000,99);

    /*
     * Initialise the channel 4 output compare value to 99 with the default
     * action of toggle.
     */

    _relayTimer.initCompare(99);

    /*
     * Set up for PWM output with an initial duty cycle of zero
     */

    _relayTimer.initCompareForPwmOutput(0);

    /*
     * Set ourselves up as an observer for interrupts raised by the timer class.
     */

    _perSecondTimer.TimerInterruptEventSender.insertSubscriber(
        TimerInterruptEventSourceSlot::bind(this,&Reflow::onInterrupt)
      );

    /*
     * Set an up-down-timer up to tick at 5000Hz with an auto-reload value of 4999
     * The timer will count from 0 to 4999 inclusive, raise an Update interrupt and
     * then go backwards back down to 0 where it'll raise another Update interrupt
     * and start again. Each journey from one end to the other takes 1 second.
     *
     * Note that the lowest frequency you can set is 1098 for a 72Mhz timer clock source.
     * This is because the maximum prescaler value is 65536 (72Mhz/65536 = 1098Hz).
     */

    _perSecondTimer.setTimeBaseByFrequency(5000,4999,TIM_CounterMode_CenterAligned3);

    /*
     * Enable just the Update interrupt after ensuring that it won't fire immediately
     */

    _perSecondTimer.clearPendingInterruptsFlag(TIM_IT_Update);
    _perSecondTimer.enableInterrupts(TIM_IT_Update);

    /*
     * At this point the timers are all configured but not enabled so nothing happens. We'll
     * enable them when start() gets called in response to the user clicking the start icon.
     */
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
    _desiredTemperature=_currentTemperature;
    _temperatureStep=(_profile[0].Temperature-_desiredTemperature)/_profile[0].EndingTime;

    // reset the tick notification

    _ticked=false;

    // enable both the timers, the PWM output on PA11 and the per-second ticker on TIM14.

    _relayTimer.enablePeripheral();
    _perSecondTimer.enablePeripheral();
  }


  /*
   * Stop the reflow process
   */

  void Reflow::stop() {

    // unsubscribe from tick events

    _perSecondTimer.TimerInterruptEventSender.removeSubscriber(
        TimerInterruptEventSourceSlot::bind(this,&Reflow::onInterrupt)
    );

    // disable the ticker

    _perSecondTimer.disablePeripheral();

    // switch off the duty cycle and disable the peripheral

    _relayTimer.setDutyCycle(0);
    _relayTimer.disablePeripheral();
  }


  /*
   * This needs to be called more frequently than 1Hz. It checks to see if the per-second timer has
   * ticked since the last call and will do the PID update if it has. Returns true if the process should
   * continue or false if it should stop.
   */

  bool Reflow::update() {

    // has the timer ticked?

    if(!_ticked)
      return true;

    // reset the ticked flag

    _ticked=false;

    const ReflowProfile::Segment *s=&_profile[_currentSegment];

    // update seconds and see if we've hit the end

    if(s->EndingTime==_currentSeconds) {

      // we have hit the ending time of the current segment. if this is the last segment
      // then the whole process has completed

      _currentSegment++;
      if(_currentSegment==_profile.getSegmentCount())
        return false;

      // we're in a new segment. set up the parameters for this leg.

      s=&_profile[_currentSegment];
      _temperatureStep=(s->Temperature-_desiredTemperature)/(s->EndingTime-_currentSeconds);
    }

    // update seconds and desired temperature

    _currentSeconds++;
    _desiredTemperature+=_temperatureStep;

    // take a temperature reading and abort if there's a hardware failure

    DefaultTemperatureReader::Result result(_temperatureReader.readTemperature());

    if(result.Status!=DefaultTemperatureReader::Result::NO_ERROR)
      return false;

    // run the PID algorithm and set the relay PWM value from the output

    uint8_t pwm=_pid.update(_desiredTemperature,_currentTemperature);
    _relayTimer.setDutyCycle(pwm);

    // continue

    return true;
  }


  /*
   * The per-second interrupt has fired
   */

  void Reflow::onInterrupt(TimerEventType /* tet */,uint8_t /* timerNumber */) {
    _ticked=true;
  }
}
