/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#pragma once


namespace awreflow {

  class PageBase {

    protected:
      enum class ButtonSelectionType : uint8_t {
        NORMAL,
        SELECTED
      };

      Panel& _panel;
      Panel::LcdPanel& _gl;
      Buttons& _buttons;

    protected:
      void clearBackground();
      void drawButtons(Flash& flash,const UiButton *buttons,uint8_t numButtons);
      void drawButton(Flash& flash,const UiButton *button);

    public:
      PageBase(Panel& panel,Buttons& buttons);
  };


  /*
   * Constructor
   */

  inline PageBase::PageBase(Panel& panel,Buttons& buttons)
    : _panel(panel),
      _gl(panel.getGraphicsLibrary()),
      _buttons(buttons) {
  }
}
