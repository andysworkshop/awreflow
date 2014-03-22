/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#pragma once


namespace awreflow {


  /**
   * Derivation of the integer number writer for writing numbers with a blue
   * background. e.g. P-I-D coefficients
   */

  class BlueIntegerWriter : public IntegerNumberWriter {

    protected:
      Point _location;
      uint32_t _value;
      uint32_t _min;
      uint32_t _max;

    public:
      BlueIntegerWriter(uint32_t value,uint32_t minvalue,uint32_t maxvalue,const Point& p);

      void redraw(Panel& panel);

      uint32_t getValue() const;

      BlueIntegerWriter& operator++();
      BlueIntegerWriter& operator--();
  };


  /*
   * ++ operator
   */

  inline BlueIntegerWriter& BlueIntegerWriter::operator++() {

    if(_value<_max)
      _value++;

    return *this;
  }


  /*
   * -- operator
   */

  inline BlueIntegerWriter& BlueIntegerWriter::operator--() {

    if(_value>_min)
      _value--;

    return *this;
  }


  /*
   * Get the current value
   */

  inline uint32_t BlueIntegerWriter::getValue() const {
    return _value;
  }
}
