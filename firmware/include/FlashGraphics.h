/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#pragma once


namespace awreflow {

  /*
   * This class manages writing bitmaps from SPI flash on to the display.
   */

  class Panel;

  class FlashGraphics : public Flash {

    protected:

      /*
       * Size of the buffer for the DMA transfer
       */

      enum {
        READ_BUFFER_SIZE = 1024
      };

      /*
       * Declare the SPI1 DMA channel that we'll use. It operates in 8-bit mode
       */

      typedef Spi1RxDmaChannel<SpiDmaReaderFeature<Spi1PeripheralTraits> > MyRxDma;
      typedef Spi1TxDmaChannel<SpiDmaWriterFeature<Spi1PeripheralTraits> > MyTxDma;

      MyRxDma _rxdma;
      MyTxDma _txdma;

      Panel& _panel;

    public:
      FlashGraphics(Panel& panel);

      void drawBitmap(const Rectangle& rc,uint32_t offset,uint32_t length);

      Panel::LcdPanel& getGraphicsLibrary();
  };


  /*
   * Convenience method to get the graphics library object
   */

  inline Panel::LcdPanel& FlashGraphics::getGraphicsLibrary() {
    return _panel.getGraphicsLibrary();
  }
}
