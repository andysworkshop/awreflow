/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#pragma once


namespace awreflow {


  /**
   * The signature for a button press: void myHandler(ButtonIdentifier id);
   * This will be called in an IRQ context and as such should do very little.
   */

  enum class ButtonIdentifier : uint8_t {
    LEFT   = 0,
    RIGHT  = 1,
    OK     = 2
  };

  DECLARE_EVENT_SIGNATURE(ButtonPressed,void(ButtonIdentifier));

  /*
   * Manager class for the 3 buttons. We'll make use of the delegates in stm32plus to
   * provide a pub/sub mechanism for the clicks.
   */

  class Buttons {

    public:
      DECLARE_EVENT_SOURCE(ButtonPressed);

    protected:

      /*
       * Constants used by the button implementation
       */

      enum {
        INITIAL_DELAY_SAMPLES = 60,   // 600ms before repeating starts
        REPEAT_DELAY_MS       = 15    // 150ms between repeats
      };

      enum class ButtonState : uint8_t {
        UP,                           // not pressed
        DOWN,                         // pressed, but we're not confident
        PRESSED,                      // still pressed, it will be reported
        REPEATING                     // long pressed, will repeat
      };

      /*
       * Timer used to asynchronously sample the button states
       */

      Timer6<
        Timer6InternalClockFeature,
        Timer6InterruptFeature
      > _buttonTimer;

      /*
       * Current state of the buttons, and a sample count since first down and up to first repeat
       */

      GpioPinRef _buttons[3];
      ButtonState _states[3];
      uint8_t _sampleCounter[3];

    public:
      Buttons();

    protected:
      void onInterrupt(TimerEventType tet,uint8_t /* timerNumber */);
  };
}
