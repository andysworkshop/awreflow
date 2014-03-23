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
      void drawButtons(FlashGraphics& flash,const UiButton *buttons,uint8_t numButtons) const;
      void drawButton(FlashGraphics& flash,const UiButton& button) const;
      void drawButtonCenteredGraphic(FlashGraphics& flash,const UiButton& button,uint32_t alternateAddress=0) const;
      void onButtonPressed(ButtonIdentifier id);
      void fadeAndClear();

    public:
      PageBase(Panel& panel,Buttons& buttons);
      ~PageBase();
  };
}
