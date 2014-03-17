/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#include "Application.h"


namespace awreflow {


  /*
   * Read the temperature. The MAX6675 outputs a 12-bit temperature reading encoded into a
   * 16-bit word along with some additional status bits. It can operate at up to 5MHz. It
   * converts while CS is high and needs a conversion time of 220ms. We must ensure that we
   * call this method at a low frequency, for example once per second.
   */

  TemperatureReader<Max6675TemperatureReader>::Result Max6675TemperatureReader::readTemperature() {

    uint16_t value;
    bool retval;

    // define the SPI peripheral that we will use

    typedef Spi1_Custom<Max6675TemperatureReader,SpiFifoNotifyQuarterFullFeature> MySpi;

    // declare peripheral parameters

    MySpi::Parameters params;

    // the minimum clock period is 200ns (5MHz). we will program the SPI peripheral
    // to operate at 3MHz

    params.spi_mode=SPI_Mode_Master;
    params.spi_baudRatePrescaler=SPI_BaudRatePrescaler_16;    // PCLK/16 = 48/16 = 3MHz
    params.spi_dataSize=SPI_DataSize_16b;                     // 16 bit transfers
    params.spi_cpol=SPI_CPOL_Low;                             // SPI mode 0
    params.spi_cpha=SPI_CPHA_1Edge;

    // create the SPI peripheral

    MySpi spi(params);

    // select the peripheral

    spi.setNss(false);

    // read out the value

    retval=spi.receive(&value,1);

    // deselect the peripheral

    spi.setNss(true);

    // check for errors

    if(!retval || (value & 0x2)!=0)
      return { 0, Result::E_COMMS_FAILURE };

    // check for open thermocouple

    if((value & 0x4)==1)
      return { 0, Result::E_OPEN_THERMOCOUPLE };

    // got a valid value

    value=(value & 0x7FF8) >> 5;

    // adjust for the calibration offset

    if(CALIBRATION_OFFSET>0)
      value+=CALIBRATION_OFFSET;
    else
      value-=-CALIBRATION_OFFSET;

    // return it

    return { value, Result::NO_ERROR };
  }
}
