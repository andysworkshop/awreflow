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

  Buttons::Buttons() {

    uint8_t i;

    // set the initial button states

    for(i=0;i<sizeof(_states)/sizeof(_states[0]);i++) {

      _states[i]=ButtonState::UP;
      _sampleCounter[i]=0;
    }

    // left and right are on PF0, PF1

    GpioF<DefaultDigitalInputFeature<0,1>> pf;

    _buttons[static_cast<uint8_t>(ButtonIdentifier::LEFT)]=pf[0];
    _buttons[static_cast<uint8_t>(ButtonIdentifier::RIGHT)]=pf[1];

    // OK is PC14

    GpioC<DefaultDigitalInputFeature<14>> pc;

    _buttons[static_cast<uint8_t>(ButtonIdentifier::OK)]=pc[14];

    // set ourselves up as a subscriber to interrupts raised by the timer class

    _buttonTimer.TimerInterruptEventSender.insertSubscriber(
        TimerInterruptEventSourceSlot::bind(this,&Buttons::onInterrupt)
    );

    /*
     * Set an up-down-timer up to tick at 5000Hz with an auto-reload value of 50
     * The timer will count from 0 to 50 inclusive, raise an Update interrupt and
     * then go backwards back down to 0 where it'll raise another Update interrupt
     * and start again. Each journey from one end to the other takes 5000ms/50=10ms.
     *
     * Note that the lowest frequency you can set is 1098 for a 72Mhz timer clock source.
     * This is because the maximum prescaler value is 65536 (72Mhz/65536 = 1098Hz).
     */

    _buttonTimer.setTimeBaseByFrequency(5000,49,TIM_CounterMode_CenterAligned3);

    // enable just the Update interrupt.

    _buttonTimer.enableInterrupts(TIM_IT_Update);

    // start the timer

    _buttonTimer.enablePeripheral();
  }


  /*
   * Interrupt callback function. This is called when the update interrupt that we've
   * enabled is fired.
   */

  void Buttons::onInterrupt(TimerEventType tet,uint8_t /* timerNumber */) {

    uint8_t i;
    bool notify;

    if(tet!=TimerEventType::EVENT_UPDATE)
      return;

    for(i=0;i<sizeof(_states)/sizeof(_states[0]);i++) {

      if(_buttons[i].read()) {

        notify=false;

        switch(_states[i]) {

          case ButtonState::UP:                 // transition to down (we're debouncing now)
            _states[i]=ButtonState::DOWN;
            break;

          case ButtonState::DOWN:               // still down, notify and advance to pressed
            _states[i]=ButtonState::PRESSED;
            notify=true;
            break;

          case ButtonState::PRESSED:            // still down, count until repeating starts
            _sampleCounter[i]++;
            if(_sampleCounter[i]==INITIAL_DELAY_SAMPLES) {
              _sampleCounter[i]=0;
              _states[i]=ButtonState::REPEATING;
            }
            break;

          case ButtonState::REPEATING:          // in auto-repeat phase
            _sampleCounter[i]++;
            if(_sampleCounter[i]==REPEAT_DELAY_MS) {
              notify=true;
              _sampleCounter[i]=0;
            }
            break;
        }

        // notify subscribers

        if(notify)
          ButtonPressedEventSender.raiseEvent(static_cast<ButtonIdentifier>(i));
      }
      else {

        // button is up

        _states[i]=ButtonState::UP;
        _sampleCounter[i]=0;
      }
    }
  }
}
