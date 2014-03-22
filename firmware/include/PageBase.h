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

      volatile bool _buttonPressed;
      volatile ButtonIdentifier _buttonId;

    protected:
      void clearBackground();
      void drawButtons(Flash& flash,const UiButton *buttons,uint8_t numButtons);
      void drawButton(Flash& flash,const UiButton *button);
      void onButtonPressed(ButtonIdentifier id);
      void fadeAndClear();

    public:
      PageBase(Panel& panel,Buttons& buttons);
      ~PageBase();
  };
}
