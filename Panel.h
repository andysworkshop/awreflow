/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#pragma once


namespace awreflow {


  class Panel {

    public:

      typedef Gpio16BitAccessMode<Panel,COLOURS_16BIT,48,42,42> LcdAccessMode;
      typedef R61523_Landscape_64K_TypeB<LcdAccessMode> LcdPanel;
      typedef R61523PwmBacklight<LcdAccessMode> LcdBacklight;

      enum {
        Port_DATA    = GPIOB_BASE,
        Port_CONTROL = GPIOA_BASE,

        Pin_RESET    = GPIO_Pin_0,
        Pin_WR       = GPIO_Pin_1,
        Pin_RS       = GPIO_Pin_2
      };

      // declare the access mode carefully so that we pick up the optimised implementation

      typedef LcdPanel::tCOLOUR tCOLOUR;

    protected:

      LcdAccessMode *_accessMode;
      LcdPanel *_gl;
      LcdBacklight *_backlight;

    public:
      Panel();

      LcdPanel& getGraphicsLibrary();
      LcdAccessMode& getAccessMode();
      LcdBacklight& getBacklight();

      void clearScreen() const;
      void setBacklight(uint8_t newPercent);
  };


  /*
   * Get the panel (graphics library) object
   */

  inline Panel::LcdPanel& Panel::getGraphicsLibrary() {
    return *_gl;
  }


  /*
   * Get the access mode
   */

  inline Panel::LcdAccessMode& Panel::getAccessMode() {
    return *_accessMode;
  }


  /*
   * Get the backlight object
   */

  inline Panel::LcdBacklight& Panel::getBacklight() {
    return *_backlight;
  }


  /*
   * Clear to black
   */

  inline void Panel::clearScreen() const {
    _gl->setBackground(ColourNames::BLACK);
    _gl->clearScreen();
  }


  /*
   * Set the new backlight percentage
   */

  inline void Panel::setBacklight(uint8_t newPercent) {
    _backlight->setPercentage(newPercent);
  }
}
