/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#include "Application.h"


namespace awreflow {

  /*
   * Buttons on this page.
   */

  static const UiButton GuiButtons[7]=
  {
    { 20,64,186,128, 0x26ccd9, 0x00c3d2,
        FlashInfo::SNPB::OFFSET,FlashInfo::SNPB::WIDTH,FlashInfo::SNPB::HEIGHT,FlashInfo::SNPB::LENGTH,
        FlashInfo::LEAD::OFFSET,FlashInfo::LEAD::WIDTH,FlashInfo::LEAD::HEIGHT,FlashInfo::LEAD::LENGTH },

    { 20,212,186,128, 0x26d4a8, 0x00cd99,
        FlashInfo::SNAGCU::OFFSET,FlashInfo::SNAGCU::WIDTH,FlashInfo::SNAGCU::HEIGHT,FlashInfo::SNAGCU::LENGTH,
        FlashInfo::LEADFREE::OFFSET,FlashInfo::LEADFREE::WIDTH,FlashInfo::LEADFREE::HEIGHT,FlashInfo::LEADFREE::LENGTH },

    { 227,64,186,128, 0xad63ac, 0x9f489e,
        FlashInfo::OVEN::OFFSET,FlashInfo::OVEN::WIDTH,FlashInfo::OVEN::HEIGHT,FlashInfo::OVEN::LENGTH,
        FlashInfo::REFLOW::OFFSET,FlashInfo::REFLOW::WIDTH,FlashInfo::REFLOW::HEIGHT,FlashInfo::REFLOW::LENGTH },

    { 227,212,186,128, 0x8e959d, 0x7a828c,
        FlashInfo::FLAME::OFFSET,FlashInfo::FLAME::WIDTH,FlashInfo::FLAME::HEIGHT,FlashInfo::FLAME::LENGTH,
        FlashInfo::DEGREESC::OFFSET,FlashInfo::DEGREESC::WIDTH,FlashInfo::DEGREESC::HEIGHT,FlashInfo::DEGREESC::LENGTH },

    { 433,64,186,78, 0x4d77ba, 0x2e5fae,
        UiButton::NO_GRAPHIC, 0,0,0,
        FlashInfo::PROPORTIONAL::OFFSET,FlashInfo::PROPORTIONAL::WIDTH,FlashInfo::PROPORTIONAL::HEIGHT,FlashInfo::PROPORTIONAL::LENGTH },

    { 433,162,186,78, 0x4d77ba, 0x2e5fae,
        UiButton::NO_GRAPHIC, 0,0,0,
        FlashInfo::INTEGER::OFFSET,FlashInfo::INTEGER::WIDTH,FlashInfo::INTEGER::HEIGHT,FlashInfo::INTEGER::LENGTH },

    { 433,261,186,78, 0x4d77ba, 0x2e5fae,
        UiButton::NO_GRAPHIC, 0,0,0,
        FlashInfo::DERIVATIVE::OFFSET, FlashInfo::DERIVATIVE::WIDTH,FlashInfo::DERIVATIVE::HEIGHT,FlashInfo::DERIVATIVE::LENGTH }
  };


  /*
   * Run the options page
   */

  void ControlPage::run() {

    uint32_t start;

    // subscribe to button events

    _buttons.ButtonPressedEventSender.insertSubscriber(ButtonPressedEventSourceSlot::bind(this,&ControlPage::onButtonPressed));

    // draw the full GUI

    redrawAll();

    // go into a keypress/timeout event loop

    for(start=MillisecondTimer::millis();;) {

      // each second, sample the temperature and display it

      if(MillisecondTimer::hasTimedOut(start,1000)) {
        _temperature.redraw(_panel);
        start=MillisecondTimer::millis();
      }

      if(_buttonPressed) {

        // interrupt handler has indicated that a button is down

        switch(_buttonId) {

          case ButtonIdentifier::LEFT:
            handleLeft();
            break;

          case ButtonIdentifier::RIGHT:
            handleRight();
            break;

          case ButtonIdentifier::OK:
            handleOk();
            break;
        }

        // ready for the next press

        _buttonPressed=false;
      }
    }

    // unsubscribe from button events

    _buttons.ButtonPressedEventSender.removeSubscriber(ButtonPressedEventSourceSlot::bind(this,&ControlPage::onButtonPressed));
  }


  /*
   * Left button pressed: navigate backwards
   */

  void ControlPage::handleLeft() {

    // erase old selection

    drawSelection(false);

    // set the new selection

    switch(_selectedButton) {

      case LEADED:
        _selectedButton=DERIVATIVE;
        break;

      case LEAD_FREE:
        _selectedButton=REFLOW;
        break;

      case REFLOW:
        _selectedButton=LEADED;
        break;

      case PROPORTIONAL:
        _selectedButton=LEAD_FREE;
        break;

      case INTEGER:
        _selectedButton=PROPORTIONAL;
        break;

      case DERIVATIVE:
        _selectedButton=INTEGER;
        break;
    }

    // draw the new selection

    drawSelection(true);
  }


  /*
   * Right button pressed: navigate forwards through the items
   */

  void ControlPage::handleRight() {

    // erase old selection

    drawSelection(false);

    // set the new selection

    switch(_selectedButton) {

      case LEADED:
        _selectedButton=REFLOW;
        break;

      case LEAD_FREE:
        _selectedButton=PROPORTIONAL;
        break;

      case REFLOW:
        _selectedButton=LEAD_FREE;
        break;

      case PROPORTIONAL:
        _selectedButton=INTEGER;
        break;

      case INTEGER:
        _selectedButton=DERIVATIVE;
        break;

      case DERIVATIVE:
        _selectedButton=LEADED;
        break;
    }

    // draw the new selection

    drawSelection(true);
  }


  /*
   * Handle the OK button
   */

  void ControlPage::handleOk() {

    if(_captive) {
      _captive=false;
      drawSelection(true);
    }
    else {

      switch(_selectedButton) {

        case PROPORTIONAL:
        case INTEGER:
        case DERIVATIVE:
          _captive=true;      // move into the captive state where left/right are directed to these buttons
          drawSelection(true);
          break;

        case LEADED:
        case LEAD_FREE:
          {
            // change the selected profile to leaded/unleaded

            Flash flash(_panel);

            _leadedChecked=_selectedButton==LEADED;
            drawCheck(flash);
          }
          break;

        default:
          break;
      }
    }
  }


  /*
   * Clear down and redraw everything
   */

  void ControlPage::redrawAll() {

    Flash flash(_panel);

    // fade out (it's asynchronous and takes about a second)

    _panel.setBacklight(0);
    MillisecondTimer::delay(1000);
    clearBackground();

    // draw the lot

    flash.drawBitmap(Rectangle(20,20,91,24),FlashInfo::CONTROL::OFFSET,FlashInfo::CONTROL::LENGTH);

    drawButtons(flash,GuiButtons,sizeof(GuiButtons)/sizeof(GuiButtons[0]));
    drawSelectionAndCheck(flash,true);

    // lights back on

    _panel.setBacklight(95);
  }


  /*
   * Draw the selection and check boxes
   */

  void ControlPage::drawSelectionAndCheck(Flash& flash,bool draw) {

    drawSelection(draw);
    drawCheck(flash);

  }


  /*
   * Draw the selection box
   */

  void ControlPage::drawSelection(bool draw) {

    // selection box

    const UiButton& button=GuiButtons[static_cast<uint8_t>(_selectedButton)];

    _gl.setForeground(draw ? (_captive ? ColourNames::GREEN : ColourNames::ORANGE) : ColourNames::BLACK);
    _gl.drawRectangle(
        Rectangle(button.X-5,button.Y-5,button.Width+10,button.Height+10)
      );
  }


  /*
   * Draw the check box
   */

  void ControlPage::drawCheck(Flash& flash) {

    // check box

    if(_leadedChecked)
      drawCheck(flash,LEADED,FlashInfo::LEADCHECKED::OFFSET,FlashInfo::LEADCHECKED::LENGTH,0x00cd99,LEAD_FREE);
    else
      drawCheck(flash,LEAD_FREE,FlashInfo::LEADFREECHECKED::OFFSET,FlashInfo::LEADFREECHECKED::LENGTH,0x00c3d2,LEADED);
  }


  /*
   * Draw the checkbox and erase the area of the other check box
   */

  void ControlPage::drawCheck(
      Flash& flash,
      uint8_t selbtn,
      uint32_t offset,
      uint32_t length,
      Panel::tCOLOUR colour,
      uint8_t deselbtn) {

    // draw the checkbox

    flash.drawBitmap(
        Rectangle(GuiButtons[selbtn].X+GuiButtons[selbtn].Width-26-7,
                  GuiButtons[selbtn].Y+7,
                  26,
                  26),
                  offset,
                  length);

    // erase other checkbox space

    _gl.setForeground(colour);
    _gl.fillRectangle(
        Rectangle(GuiButtons[deselbtn].X+GuiButtons[deselbtn].Width-26-7,
                  GuiButtons[deselbtn].Y+7,
                  26,
                  26));
  }


  /*
   * Subscription callback for button events. This is IRQ code so don't
   * get carried away with your code here.
   */

  void ControlPage::onButtonPressed(ButtonIdentifier id) {

    // if the main thread is ready for another event then signal it

    if(!_buttonPressed) {
      _buttonPressed=true;
      _buttonId=id;
    }
  }
}
