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

  PageBase::PageBase(Panel& panel,Buttons& buttons)
    : _panel(panel),
      _gl(panel.getGraphicsLibrary()),
      _buttons(buttons),
      _buttonPressed(false) {

    // subscribe to button events

    _buttons.ButtonPressedEventSender.insertSubscriber(ButtonPressedEventSourceSlot::bind(this,&PageBase::onButtonPressed));
  }


  /*
   * Destructor
   */

  PageBase::~PageBase() {

    // unsubscribe from button events

    _buttons.ButtonPressedEventSender.removeSubscriber(ButtonPressedEventSourceSlot::bind(this,&ControlPage::onButtonPressed));
  }


  /*
   * Redraw the buttons
   */

  void PageBase::drawButtons(FlashGraphics& flash,const UiButton *buttons,uint8_t numButtons) {

    const UiButton *button;

    for(button=buttons;numButtons;numButtons--,button++)
      drawButton(flash,button);
  }


  /*
   * Draw a single button
   */

  void PageBase::drawButton(FlashGraphics& flash,const UiButton *button) {

    uint16_t x,y;
    Panel::LcdPanel& gl(_panel.getGraphicsLibrary());

    // draw the accent line

    gl.setForeground(button->AccentColour);
    gl.drawLine(Point(button->X,button->Y),Point(button->X+button->Width-1,button->Y));

    // fill the button rectangle

    Rectangle rc(button->X,button->Y+1,button->Width,button->Height-1);

    gl.setForeground(button->BackgroundColour);
    gl.fillRectangle(rc);

    // draw the graphic, centered

    x=button->X+(button->Width/2)-(button->IconWidth)/2;
    y=button->Y+(button->Height/2)-(button->IconHeight)/2;

    flash.drawBitmap(
        Rectangle(x,y,button->IconWidth,button->IconHeight),
        static_cast<uint32_t>(button->IconFlashAddress),
        button->IconSize
      );

    // draw the prompt, bottom right

    x=button->X+button->Width-button->PromptWidth-7;
    y=button->Y+button->Height-button->PromptHeight-7;

    flash.drawBitmap(
        Rectangle(x,y,button->PromptWidth,button->PromptHeight),
        static_cast<uint32_t>(button->PromptFlashAddress),
        button->PromptSize
      );
  }


  /*
   * Fade out and clear the screen
   */

  void PageBase::fadeAndClear() {
    _panel.setBacklight(0);
    MillisecondTimer::delay(1000);
    clearBackground();
  }


  /*
   * Redraw the buttons
   */

  void PageBase::clearBackground() {

    Panel::LcdPanel& gl(_panel.getGraphicsLibrary());

    gl.setBackground(ColourNames::BLACK);
    gl.clearScreen();
  }


  /*
   * Subscription callback for button events. This is IRQ code so don't
   * get carried away with your code here.
   */

  void PageBase::onButtonPressed(ButtonIdentifier id) {

    // if the main thread is ready for another event then signal it

    if(!_buttonPressed) {
      _buttonPressed=true;
      _buttonId=id;
    }
  }
}
