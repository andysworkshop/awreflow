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

  Pid::Pid(variable_t kp,variable_t ki,variable_t kd)
    : _kp(kp),
      _ki(ki),
      _kd(kd),
      _lastError(0),
      _integral(0) {
  }


  /*
   * Update the algorithm with the current error and get a percentage value back
   * that can be used as a PWM duty cycle (0..100). This method should be called at
   * a fixed time interval.
   */

  uint8_t Pid::update(variable_t desiredTemperature,variable_t currentTemperature) {

    variable_t error,pwm,derivative;

    // current error term is the difference between desired and current temperature

    error=desiredTemperature-currentTemperature;

    // update the integral (historical error)

    _integral+=error;

    // the derivative term

    derivative=error-_lastError;

    // calculate the control variable

    pwm=(_kp*error)+(_ki*_integral)+(_kd*derivative);
    pwm=Max(Min(255.0,pwm),0.0);

    // save the last error

    _lastError=error;

    // return the control variable

    return static_cast<uint8_t>(pwm);
  }
}
