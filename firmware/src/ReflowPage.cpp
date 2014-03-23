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
   * Constructor
   */

  ReflowPage::ReflowPage(Panel& panel,Buttons& buttons,const ReflowParameters& params)
    : PageBase(panel,buttons),
      _selectedButton(START),
      _mode(WAITING),
      _params(params) {

    if(params.Leaded)
      _reflowProfile=new LeadedReflowProfile;
    else
      _reflowProfile=new LeadFreeReflowProfile;

    // create the reflow object

    _reflow=new Reflow(*_reflowProfile,params);
  }


  /*
   * Destructor
   */

  ReflowPage::~ReflowPage() {
    delete _reflow;
    delete _reflowProfile;
  }


  /*
   * Run the reflow page
   */

  void ReflowPage::run() {

    redrawAll();

    for(;;) {

      // if we're cooking then the reflow object needs to get updated

      if(_mode==COOKING) {

        // update the reflow controller and stop the process when it's finished or aborted

        if(!_reflow->update())
          stopReflow();
      }

      // check if any of the buttons has been pressed

      if(_buttonPressed) {

        // take action depending on which button it was

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

      case START:
        startReflow();
        return false;

      case STOP:
        stopReflow();
        return false;

      case EXIT:
        return true;

      default:
        return false;
    }
  }


  /*
   * Start the reflow and update the UI
   */

  void ReflowPage::startReflow() {

    FlashGraphics flash(_panel);

    // enable the "stop" button

    drawButtonCenteredGraphic(flash,GuiButtons[STOP],FlashInfo::STOP::OFFSET);

    // move the selected button to "stop"

    drawSelection(false);
    _selectedButton=STOP;
    drawSelection(true);

    // disable the exit and start buttons

    drawButtonCenteredGraphic(flash,GuiButtons[START],FlashInfo::PLAY_DISABLED::OFFSET);
    drawButtonCenteredGraphic(flash,GuiButtons[EXIT],FlashInfo::EXIT_DISABLED::OFFSET);

    // start the process handler

    _reflow->start();

    // the state is now started

    _mode=COOKING;
  }


  /*
   * Stop the reflow process
   */

  void ReflowPage::stopReflow() {

    FlashGraphics flash(_panel);

    // stop the process

    _reflow->stop();

    // enable the "exit" button

    drawButtonCenteredGraphic(flash,GuiButtons[EXIT]);

    // move the selected button to "exit"

    drawSelection(false);
    _selectedButton=EXIT;
    drawSelection(true);

    // disable the stop button

    drawButtonCenteredGraphic(flash,GuiButtons[STOP],FlashInfo::STOP_DISABLED::OFFSET);

    // the state is now finished

    _mode=FINISHED;
  }


  /*
   * Redraw all the controls on the page at startup
   */

  void ReflowPage::redrawAll() {

    FlashGraphics flash(_panel);

    // fade out (it's asynchronous and takes about a second)

    fadeAndClear();

    // draw the lot

    drawButtons(flash,GuiButtons,sizeof(GuiButtons)/sizeof(GuiButtons[0]));
    drawTemperatureIcon(flash);
    drawSelection(true);
    drawProfile(flash);
    drawAxes(flash);

    // lights back on

    _panel.setBacklight(95);
  }


  /*
   * Draw both axes
   */

  void ReflowPage::drawAxes(FlashGraphics& flash) const {

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

    gl.setForeground(ColourNames::GREY70);

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
   * Draw the reflow profile
   */

  void ReflowPage::drawProfile(FlashGraphics& flash) const {

    uint8_t i;
    uint32_t height,width;
    Point p1,p2,p;
    Panel::LcdPanel& gl(_panel.getGraphicsLibrary());
    AxisNumberWriter writer;

    // starting point

    p1.X=LEFT_MARGIN;
    p1.Y=360-BOTTOM_MARGIN-1;

    // constants used later

    width=640-LEFT_MARGIN-RIGHT_MARGIN-1;
    height=360-10-BOTTOM_MARGIN;

    // the segments describe the ending condition, loop for each one

    for(i=0;i<_reflowProfile->getSegmentCount();i++) {

      const ReflowProfile::Segment& s((*_reflowProfile)[i]);

      // calculate the end point and plot the line

      p2.X=LEFT_MARGIN+((width*s.EndingTime)/_reflowProfile->getTotalDuration());
      p2.Y=360-BOTTOM_MARGIN-1-((height*(s.Temperature-25))/(_reflowProfile->getMaxTemperature()-25));

      wideLine(gl,p1,p2,0x00cd99);

      // plot a horizontal dotted grey line to the Y axis. these plotters are far from optimal
      // for plotting a straight dotted line but they're sufficient for this light load.

      p=p2;
      gl.setForeground(ColourNames::GREY40);
      while(p.X>LEFT_MARGIN) {
        gl.plotPoint(p);
        p.X-=2;
      }

      // plot a vertical line down to the X axis

      p=p2;
      gl.setForeground(ColourNames::GREY40);
      while(p.Y<360-BOTTOM_MARGIN-1) {
        gl.plotPoint(p);
        p.Y+=2;
      }

      // draw the temperature on the Y axis

      p.X=10;
      p.Y=p2.Y;
      writer.write(flash,p,s.Temperature);

      // draw the time on the X axis

      p.X=p2.X;
      p.Y=360-BOTTOM_MARGIN+4;
      writer.write(flash,p,s.EndingTime);

      // starting point is now the ending point

      p1=p2;
    }
  }


  /*
   * Plot a fat line (2px wide)
   */

  void ReflowPage::wideLine(Panel::LcdPanel& gl,const Point& p1,const Point& p2,Panel::tCOLOUR cr) const {

    // set the line colour

    gl.setForeground(cr);

    // draw the first line

    gl.drawLine(p1,p2);

    // draw an adjacent line that's offset by 1px in the X direction if the line is steeper than
    // it is flat or in the Y direction if it's flatter than it is tall.

    Point np1(p1),np2(p2);

    if(Abs(p2.X-p1.X)>Abs(p2.Y-p1.Y)) {
      np1.Y++;
      np2.Y++;
    }
    else {
      np1.X++;
      np2.X++;
    }
    gl.drawLine(np1,np2);
  }


  /*
   * Draw the temperature icon
   */

  void ReflowPage::drawTemperatureIcon(FlashGraphics& flash) {

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
