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

  static const UiButton GuiButtons[4]=
  {
    { 555,10,75,96, 0xad63ac, 0x9f489e,
        UiButton::NO_GRAPHIC, 0,0,0,
        UiButton::NO_GRAPHIC, 0,0,0 },

    { 555,116,75,55, 0x4d77ba, 0x2e5fae,
        FlashInfo::PLAY::OFFSET,FlashInfo::PLAY::WIDTH,FlashInfo::PLAY::HEIGHT,FlashInfo::PLAY::LENGTH,
        UiButton::NO_GRAPHIC, 0,0,0 },

    { 555,181,75,55, 0x4d77ba, 0x2e5fae,
        FlashInfo::STOP_DISABLED::OFFSET,FlashInfo::STOP_DISABLED::WIDTH,FlashInfo::STOP_DISABLED::HEIGHT,FlashInfo::STOP_DISABLED::LENGTH,
        UiButton::NO_GRAPHIC, 0,0,0 },

    { 555,246,75,55, 0x4d77ba, 0x2e5fae,
        FlashInfo::EXIT::OFFSET,FlashInfo::EXIT::WIDTH,FlashInfo::EXIT::HEIGHT,FlashInfo::EXIT::LENGTH,
        UiButton::NO_GRAPHIC, 0,0,0 }
  };


  /*
   * Run the reflow page
   */

  void ReflowPage::run() {

    redrawAll();

    for(;;) {

      if(_buttonPressed) {

        switch(_buttonId) {

          case ButtonIdentifier::LEFT:
            handleDirection();
            break;

          case ButtonIdentifier::RIGHT:
            handleDirection();
            break;

          case ButtonIdentifier::OK:
            if(handleOk())
              return;

            break;
        }

        // ready for the next press

        _buttonPressed=false;
      }
    }
  }


  /*
   * Left/right button pressed: navigate
   */

  void ReflowPage::handleDirection() {

    // erase old selection

    drawSelection(false);

    // set the new selection

    switch(_selectedButton) {

      case START:               // mode must be WAITING
        _selectedButton=EXIT;
        break;

      case EXIT:                // if WAITING then can go to start
        if(_mode==WAITING)
          _selectedButton=START;
        break;

      default:
        break;
    }

    // draw the new selection

    drawSelection(true);
  }


  /*
   * Handle the OK button
   */

  bool ReflowPage::handleOk() {

    switch(_selectedButton) {

      case EXIT:
        return true;

      default:
        return false;
    }
  }


  /*
   * Redraw all the controls on the page at startup
   */

  void ReflowPage::redrawAll() {

    Flash flash(_panel);

    // fade out (it's asynchronous and takes about a second)

    fadeAndClear();

    // draw the lot

    drawButtons(flash,GuiButtons,sizeof(GuiButtons)/sizeof(GuiButtons[0]));
    drawTemperatureIcon(flash);
    drawSelection(true);
    drawAxes(flash);

    // lights back on

    _panel.setBacklight(95);
  }


  /*
   * Draw both axes
   */

  void ReflowPage::drawAxes(Flash& flash) const {

    Panel::LcdPanel& gl(_panel.getGraphicsLibrary());

    // draw the Y label

    flash.drawBitmap(
        Rectangle(LEFT_MARGIN+6,
                  TOP_MARGIN,
                  FlashInfo::DEGREESC_BLACK::WIDTH,
                  FlashInfo::DEGREESC_BLACK::WIDTH
                 ),
        FlashInfo::DEGREESC_BLACK::OFFSET,
        FlashInfo::DEGREESC_BLACK::LENGTH);

    // the most efficient way to draw these 2px wide axes is to use the
    // rectangle function

    gl.setForeground(ColourNames::WHITESMOKE);

    // X-axis

    gl.fillRectangle(
        Rectangle(
            LEFT_MARGIN,
            360-BOTTOM_MARGIN-1,
            640-LEFT_MARGIN-RIGHT_MARGIN,
            2
        )
      );

    // Y-axis

    gl.fillRectangle(
        Rectangle(
            LEFT_MARGIN,
            TOP_MARGIN,
            2,
            360-10-BOTTOM_MARGIN
        )
      );

  }


  /*
   * Plot a fat line (2px wide) using bresenham
   */

#if 0
  void wideLine(const Point& p1,const Point& p2,Panel::tCOLOUR cr) {

  }
#endif

  /*
   * Draw the temperature icon
   */

  void ReflowPage::drawTemperatureIcon(Flash& flash) {

    // this is the thermometer at the top of the purple box

    flash.drawBitmap(
        Rectangle(586,18,FlashInfo::THERMOMETER::WIDTH,FlashInfo::THERMOMETER::HEIGHT),
        FlashInfo::THERMOMETER::OFFSET,
        FlashInfo::THERMOMETER::LENGTH
      );
  }


  /*
   * Draw the selection box
   */

  void ReflowPage::drawSelection(bool draw) const {

    // selection box

    const UiButton& button=GuiButtons[static_cast<uint8_t>(_selectedButton)];

    _gl.setForeground(draw ? ColourNames::ORANGE : ColourNames::BLACK);
    _gl.drawRectangle(
        Rectangle(button.X-5,button.Y-5,button.Width+10,button.Height+10)
      );
  }
}
