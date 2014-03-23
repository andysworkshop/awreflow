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
