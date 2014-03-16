/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#pragma once


namespace awreflow {


  /*
   * The options page manages the selection of the profile and the
   * customisation of the PID parameters.
   */

  class ControlPage : public PageBase {

    protected:
      enum {
        LEADED    = 0,
        LEAD_FREE = 1,
        REFLOW    = 2,
        P         = 4,
        I         = 5,
        D         = 6
      } _selectedButton;

      bool _leadedChecked;

    protected:
      void redrawAll();
      void drawSelection(Flash& flash,bool draw);
      void drawSelection(Panel::LcdPanel& gl,Flash& flash,uint8_t selbtn,uint32_t offset,uint32_t length,Panel::tCOLOUR colour,uint8_t deselbtn);

    public:
      ControlPage(Panel& panel,Buttons& buttons);

      void run();
  };


  /*
   * Constructor
   */

  inline ControlPage::ControlPage(Panel& panel,Buttons& buttons)
    : PageBase(panel,buttons),
      _selectedButton(REFLOW),
      _leadedChecked(true) {
  }
}
