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

  FlashGraphics::FlashGraphics(Panel& panel) :
    _panel(panel) {

    static_cast<DMA_InitTypeDef&>(_txdma).DMA_MemoryInc=DMA_MemoryInc_Disable;
  }


  /*
   * Read the bitmap from SPI and write it out to the display
   * We'll use the Read Data (03H) command because our max frequency of 24MHz
   * is lower than the device's max of 44MHz so we don't have to use the Fast Read
   * command that would incur a speed penalty due to the dummy writes.
   *
   * The strategy here is to use DMA to read in the bitmap from the flash device into
   * a buffer in chunks. When half the buffer is full we transfer it to the display
   * while DMA is filling the remainder. When DMA has filled the remainder we transfer
   * it to the display. This allows us to get a good utilisation out of the SPI bus.
   *
   * Note that in master mode the SPI clock will not tick unless we transmit something.
   * Without a ticking clock the flash slave device will not latch out the data. Therefore
   * we use DMA to "transmit" fake zero bytes just to get the clock to tick so that there
   * will be data for us to receive. This is one of the oddities of ST's SPI implementation
   * that you just have to learn.
   */

  void FlashGraphics::drawBitmap(const Rectangle& rc,uint32_t offset,uint32_t length) {

     uint8_t zero,bytes[4];
     Panel::LcdPanel& gl(_panel.getGraphicsLibrary());
     Panel::LcdAccessMode& accessMode(_panel.getAccessMode());

     // set up the drawing rectangle and get ready for receiving data

     gl.moveTo(rc);
     gl.beginWriting();

     // first 32-bits are the read command and the offset

     bytes[0]='\x3';
     bytes[1]=(offset >> 16) & 0xff;
     bytes[2]=(offset >> 8) & 0xff;
     bytes[3]=offset & 0xff;

     // select our device

     SpiNssManager nss(*_spi);

     // write out as four 8-bit transfers

     _spi->send(bytes,4);

     // get a temporary buffer and set the dummy byte to zero

     uint8_t buffer[READ_BUFFER_SIZE];
     zero=0;

     while(length>=READ_BUFFER_SIZE) {

       // start a read and wait for half complete

       _rxdma.beginRead(buffer,READ_BUFFER_SIZE);
       _txdma.beginWrite(&zero,READ_BUFFER_SIZE);

       while(!_rxdma.isHalfComplete());

       // transfer the first half to the display while the other half is finishing off

       accessMode.rawTransfer(buffer,READ_BUFFER_SIZE/4);

       // wait for the full complete

       while(!_rxdma.isComplete());

       // transfer the second half

       accessMode.rawTransfer(&buffer[READ_BUFFER_SIZE/2],READ_BUFFER_SIZE/4);
       length-=READ_BUFFER_SIZE/2;
     }

     if(length>0) {

       // receive and transfer the remainder synchronously

       _spi->receive(buffer,length);
       accessMode.rawTransfer(buffer,length/2);
     }
   }
}
