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

  class Flash {

    public:

      enum {
        Port_NSS = GPIOA_BASE,
        Port_SCK = GPIOA_BASE,
        Port_MISO = GPIOA_BASE,
        Port_MOSI = GPIOA_BASE,

        Pin_NSS  = GPIO_Pin_3,
        Pin_SCK  = GPIO_Pin_5,
        Pin_MISO = GPIO_Pin_6,
        Pin_MOSI = GPIO_Pin_7
      };

      enum {
        READ_BUFFER_SIZE = 1024
      };

    protected:

      /*
       * Declare the SPI peripheral that we'll use both directly and indirectly via DMA.
       */

      typedef Spi1_Custom<Flash,SpiFifoNotifyQuarterFullFeature> MySpi;
      MySpi *_spi;

      /*
       * Declare the SPI1 DMA channel that we'll use. It operates in 8-bit mode
       */

      typedef Spi1RxDmaChannel<SpiDmaReaderFeature<Spi1PeripheralTraits> > MyRxDma;
      typedef Spi1TxDmaChannel<SpiDmaWriterFeature<Spi1PeripheralTraits> > MyTxDma;

      MyRxDma *_rxdma;
      MyTxDma *_txdma;

      /*
       * The panel
       */

      Panel& _panel;

    public:
      Flash(Panel& panel);
      ~Flash();

      void drawBitmap(const Rectangle& rc,uint32_t offset,uint32_t length);

      Panel::LcdPanel& getGraphicsLibrary();
  };


  /*
   * Convenience method to get the graphics library object
   */

  inline Panel::LcdPanel& Flash::getGraphicsLibrary() {
    return _panel.getGraphicsLibrary();
  }
}
