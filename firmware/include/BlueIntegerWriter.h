/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
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
