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
   * The per-second interrupt has fired
   */

  void Reflow::onInterrupt(TimerEventType /* tet */,uint8_t /* timerNumber */) {
  }
}
