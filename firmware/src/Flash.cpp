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

  Flash::Flash() {

    // create the peripheral. this will initialise it

    MySpi::Parameters params;

    params.spi_mode=SPI_Mode_Master;
    params.spi_baudRatePrescaler=SPI_BaudRatePrescaler_2;     // fastest mode = PCLK/2 = 48/2 = 24MHz
    params.spi_dataSize=SPI_DataSize_8b;                      // 8 bit transfers
    params.spi_cpol=SPI_CPOL_Low;                             // SPI mode 0
    params.spi_cpha=SPI_CPHA_1Edge;

    // create the SPI peripheral

    _spi.reset(new MySpi(params));
  }


  /*
   * Erase the last sector of the device. The smallest eraseable unit is a 4096
   * byte sector.
   */

  bool Flash::eraseLastSector() const {

    uint8_t command[4];
    bool retval;

    // create the command (0x20 + 24 bit address)
    // address = 1048576 - 4096 = 0x0FF000

    command[0]=0x20;
    command[1]=0x0F;
    command[2]=0xF0;
    command[3]=0x00;

    // sector erase requires write-enable

    if(!writeEnable())
      return false;

    // send the simple command

    _spi->setNss(false);
    retval=_spi->send(command,sizeof(command));
    _spi->setNss(true);

    // wait for it to finish

    return retval ? waitForIdle() : false;
  }


  /*
   * Write the last page. It's actually the first programmable 256 byte page
   * in the last 4096 byte sector.
   */

  bool Flash::writeLastPage(const uint8_t *page) const {

    uint8_t command[4];

    // create the command (0x02 + 24 bit address)
    // address = 1048576 - 4096 = 0x0FF000

    command[0]=0x02;
    command[1]=0x0F;
    command[2]=0xF0;
    command[3]=0x00;

    // page program requires write-enable

    if(!writeEnable())
      return false;

    // send the 4 byte command. nss must go high after the page program or the
    // write will not happen.

    {
      SpiNssManager mgr(*_spi);

      if(!_spi->send(command,sizeof(command)))
        return false;

      // send the 256 bytes

      if(!_spi->send(page,256))
        return false;
    }

    return waitForIdle();
  }


  /*
   * Read the last page. It's actually the first programmable 256 byte page
   * in the last 4096 byte sector.
   */

  bool Flash::readLastPage(uint8_t *page) const {

    uint8_t command[4];

    // create the command (0x02 + 24 bit address)
    // address = 1048576 - 4096 = 0x0FF000

    command[0]=0x03;
    command[1]=0x0F;
    command[2]=0xF0;
    command[3]=0x00;

    // manage the NSS pin

    SpiNssManager mgr(*_spi);

    // send the 4 byte command

    if(!_spi->send(command,sizeof(command)))
      return false;

    // receive the 256 bytes

    return _spi->receive(page,256);
  }


  /*
   * Read the SPI device status register. We need to do this so we can
   * see the IDLE bit
   */

  bool Flash::readStatusRegister(uint8_t& sr) const {

    uint8_t command;

    command=0x5;

    // send the 1 byte command

    SpiNssManager nss(*_spi);

    if(!_spi->send(&command,1))
      return false;

    // receive the single byte

    return _spi->receive(&sr,1);
  }


  /*
   * Wait for the flash device to become idle
   */

  bool Flash::waitForIdle() const {

    uint8_t sr;

    do {

      if(!readStatusRegister(sr))
        return false;

    } while((sr & 1)!=0);     // bit zero is WIP (write in progress)

    return true;
  }


  /*
   * Send the write-enable command
   */

  bool Flash::writeEnable() const {

    uint8_t command;

    command=0x6;

    // send the 1 byte command

    SpiNssManager nss(*_spi);
    return _spi->send(&command,1);
  }
}
