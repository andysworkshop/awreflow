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

    // draw the full GUI

    for(;;) {
      redrawAll();
      MillisecondTimer::delay(5000);
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
    drawSelection(flash,true);

    // lights back on

    _panel.setBacklight(95);
  }


  /*
   * Draw the selection and check boxes
   */

  void ControlPage::drawSelection(Flash& flash,bool draw) {

    const UiButton& button=GuiButtons[static_cast<uint8_t>(_selectedButton)];
    Panel::LcdPanel& gl(_panel.getGraphicsLibrary());

    // selection box

    gl.setForeground(draw ? ColourNames::ORANGE : ColourNames::BLACK);
    gl.drawRectangle(
        Rectangle(button.X-5,button.Y-5,button.Width+10,button.Height+10)
      );

    // check box

    if(_leadedChecked)
      drawSelection(gl,flash,LEADED,FlashInfo::LEADCHECKED::OFFSET,FlashInfo::LEADCHECKED::LENGTH,0x00cd99,LEAD_FREE);
    else
      drawSelection(gl,flash,LEAD_FREE,FlashInfo::LEADFREECHECKED::OFFSET,FlashInfo::LEADFREECHECKED::LENGTH,0x00c3d2,LEADED);

  }


  /*
   * Draw the checkbox and erase the area of the other check box
   */

  void ControlPage::drawSelection(
      Panel::LcdPanel& gl,
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

    gl.setForeground(colour);
    gl.fillRectangle(
        Rectangle(GuiButtons[deselbtn].X+GuiButtons[deselbtn].Width-26-7,
                  GuiButtons[deselbtn].Y+7,
                  26,
                  26));
  }
}
