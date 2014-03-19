/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#pragma once


namespace awreflow {

  class Pid {
    public:
      typedef double variable_t;

    protected:
      variable_t _kp;
      variable_t _ki;
      variable_t _kd;

      variable_t _lastError;
      variable_t _integral;

    public:
      Pid(variable_t kp,variable_t ki,variable_t kd);

      uint8_t update(variable_t desiredTemperature,variable_t currentTemperature);
  };
}
