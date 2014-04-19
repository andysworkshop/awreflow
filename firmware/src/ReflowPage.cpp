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

  static const UiButton GuiButtons[4]= {
    { 555,10,75,116, 0xad63ac, 0x9f489e,
        UiButton::NO_GRAPHIC, 0,0,0,
        UiButton::NO_GRAPHIC, 0,0,0 },

    { 555,136,75,55, 0x4d77ba, 0x2e5fae,
        FlashInfo::START::OFFSET,FlashInfo::START::WIDTH,FlashInfo::START::HEIGHT,FlashInfo::START::LENGTH,
        UiButton::NO_GRAPHIC, 0,0,0 },

    { 555,201,75,55, 0x4d77ba, 0x2e5fae,
        FlashInfo::STOP_DISABLED::OFFSET,FlashInfo::STOP_DISABLED::WIDTH,FlashInfo::STOP_DISABLED::HEIGHT,FlashInfo::STOP_DISABLED::LENGTH,
        UiButton::NO_GRAPHIC, 0,0,0 },

    { 555,266,75,55, 0x4d77ba, 0x2e5fae,
        FlashInfo::EXIT::OFFSET,FlashInfo::EXIT::WIDTH,FlashInfo::EXIT::HEIGHT,FlashInfo::EXIT::LENGTH,
        UiButton::NO_GRAPHIC, 0,0,0 }
  };


  /*
   * Constructor
   */

  ReflowPage::ReflowPage(Panel& panel,Buttons& buttons,const ReflowParameters& params)
    : PageBase(panel,buttons),
      _selectedButton(START_PAUSE),
      _mode(WAITING),
      _params(params),
      _currentTemperatureWriter(0x9f489e,PurpleDigits,15,Size(10,15)),
      _desiredTemperatureWriter(0x9f489e,OrangePurpleDigits,15,Size(0,0)) {

    if(params.Leaded)
      _reflowProfile.reset(new LeadedReflowProfile);
    else
      _reflowProfile.reset(new LeadFreeReflowProfile);

    // create the reflow object

    _reflow.reset(new Reflow(*_reflowProfile,params));
  }


  /*
   * Run the reflow page
   */

  void ReflowPage::run() {

    uint32_t start;

    // start off with a full page redraw

    redrawAll();

    // go into a keypress/timeout event loop

    start=MillisecondTimer::millis();

    for(;;) {

      // if we're cooking then the reflow object needs to get updated

      if(_mode==COOKING) {

        // update the reflow controller and stop the process when it's finished or aborted

        switch(_reflow->update()) {

          case Reflow::STOP:
            stopReflow();
            break;

          case Reflow::UPDATED:
            plotProgress();
            break;

          default:
            break;
        }
      }

      // each second, sample the temperature and display it
      // if we're cooking, show the power output

      if(MillisecondTimer::hasTimedOut(start,1000)) {
        drawTemperatureButton();

        if(_mode==COOKING)
          drawPowerRectangle();

        start=MillisecondTimer::millis();
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

      case START_PAUSE:           // mode must be WAITING or COOKING
        _selectedButton=_mode==WAITING ? EXIT : STOP;
        break;

      case STOP:                  // mode must be COOKING
        _selectedButton=START_PAUSE;
        break;

      case EXIT:                  // mode must be WAITING or FINISHED
        if(_mode==WAITING)
          _selectedButton=START_PAUSE;
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

      case START_PAUSE:
        if(_mode==WAITING)
          startReflow();
        else
          pauseOrRestartReflow();
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

    // enable the "pause" button in place of "start"

    drawButtonCenteredGraphic(flash,GuiButtons[START_PAUSE],FlashInfo::PAUSE::OFFSET);

    // enable the "stop" button

    drawButtonCenteredGraphic(flash,GuiButtons[STOP],FlashInfo::STOP::OFFSET);

    // disable the exit button

    drawButtonCenteredGraphic(flash,GuiButtons[EXIT],FlashInfo::EXIT_DISABLED::OFFSET);

    // reset point plotting

    _lastPlottedPoint=Point::Origin;

    // start the process handler

    _reflow->start();

    // the state is now started

    _mode=COOKING;
  }


  /*
   * Pause or restart the reflow (freeze time advancing)
   */

  void ReflowPage::pauseOrRestartReflow() {

    FlashGraphics flash(_panel);

    if(_reflow->getCurrentSeconds()>0) {

      if(_reflow->isPaused()) {
        _reflow->restart();
        drawButtonCenteredGraphic(flash,GuiButtons[START_PAUSE],FlashInfo::PAUSE::OFFSET);
      }
      else {
        _reflow->pause();
        drawButtonCenteredGraphic(flash,GuiButtons[START_PAUSE]);
      }
    }
  }


  /*
   * Stop the reflow process
   */

  void ReflowPage::stopReflow() {

    FlashGraphics flash(_panel);

    // stop the process

    _reflow->stop();

    // disable the "pause" and "stop" buttons

    drawButtonCenteredGraphic(flash,GuiButtons[START_PAUSE],FlashInfo::PAUSE_DISABLED::OFFSET);
    drawButtonCenteredGraphic(flash,GuiButtons[STOP]);

    // enable the exit button

    drawButtonCenteredGraphic(flash,GuiButtons[EXIT]);

    // move the selected button to "exit"

    drawSelection(false);
    _selectedButton=EXIT;
    drawSelection(true);

    // erase the power rectangle

    Panel::LcdPanel& gl(flash.getGraphicsLibrary());
    gl.setBackground(0x9f489e);
    gl.clearRectangle(Rectangle(POWER_RECT_X,POWER_RECT_Y,POWER_RECT_WIDTH,POWER_RECT_HEIGHT));

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

    _panel.setBacklight(FULL_BRIGHTNESS);
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
            Panel::HEIGHT-BOTTOM_MARGIN-1,
            X_AXIS_WIDTH,
            2
        )
      );

    // Y-axis

    gl.fillRectangle(
        Rectangle(
            LEFT_MARGIN,
            TOP_MARGIN,
            2,
            Y_AXIS_HEIGHT
        )
      );

  }


  /*
   * Draw the reflow profile
   */

  void ReflowPage::drawProfile(FlashGraphics& flash) const {

    uint8_t i;
    Point p1,p2,p;
    Panel::LcdPanel& gl(_panel.getGraphicsLibrary());
    AxisNumberWriter writer;

    // constants used later

    const uint32_t width=X_AXIS_WIDTH-1;
    const uint32_t height=Y_AXIS_HEIGHT;

    // starting point (all the reflow profiles have a desired start of 25C)

    p1.X=LEFT_MARGIN;
    p1.Y=Panel::HEIGHT-BOTTOM_MARGIN-1-((height*25)/_reflowProfile->getMaxTemperature());;

    // the segments describe the ending condition, loop for each one

    for(i=0;i<_reflowProfile->getSegmentCount();i++) {

      const ReflowProfile::Segment& s((*_reflowProfile)[i]);

      // calculate the end point and plot the line

      p2.X=LEFT_MARGIN+((width*s.EndingTime)/_reflowProfile->getTotalDuration());
      p2.Y=Panel::HEIGHT-BOTTOM_MARGIN-1-((height*s.Temperature)/_reflowProfile->getMaxTemperature());

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
      while(p.Y<Panel::HEIGHT-BOTTOM_MARGIN-1) {
        gl.plotPoint(p);
        p.Y+=2;
      }

      // draw the temperature on the Y axis

      p.X=10;
      p.Y=p2.Y;
      writer.write(flash,p,s.Temperature);

      // draw the time on the X axis

      p.X=p2.X;
      p.Y=Panel::HEIGHT-BOTTOM_MARGIN+4;
      writer.write(flash,p,s.EndingTime);

      // starting point is now the ending point

      p1=p2;
    }
  }


  /*
   * Plot the progress of the reflow on the chart
   */

  void ReflowPage::plotProgress() {

    Point p2;

    // get the current seconds and temperature

    uint32_t seconds(_reflow->getCurrentSeconds());
    Pid::variable_t temperature(_reflow->getCurrentTemperature());

    // clip the max temperature in case we run off the top

    if(temperature>_reflowProfile->getMaxTemperature())
      temperature=_reflowProfile->getMaxTemperature();

    // calculate the point on the chart

    p2.X=LEFT_MARGIN+((seconds*X_AXIS_WIDTH)/_reflowProfile->getTotalDuration());
    p2.Y=Panel::HEIGHT-BOTTOM_MARGIN-((temperature*Y_AXIS_HEIGHT)/_reflowProfile->getMaxTemperature());

    if(_lastPlottedPoint!=Point::Origin) {

      Panel::LcdPanel& gl(_panel.getGraphicsLibrary());
      wideLine(gl,_lastPlottedPoint,p2,ColourNames::RED);
    }

    _lastPlottedPoint=p2;
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


  /*
   * Redraw the temperature indicator button to reflect current state. When not cooking
   * we'll show the current oven temperature. When cooking we'll show both the current
   * oven temperature and the target temperature.
   */

  void ReflowPage::drawTemperatureButton() {

    DefaultTemperatureReader::Result result;

    // always display the current oven temperature

    if(_mode==COOKING) {

      // temperature should reflect last used for PID - in any case we can only have one of
      // the per-second updates sampling the temperature because of the speed limitations of
      // the AD converter

      result.Temperature=_reflow->getCurrentTemperature();
      result.Status=DefaultTemperatureReader::Result::NO_ERROR;
    }
    else {

      // get a new temperature reading

      DefaultTemperatureReader dtr;
      result=dtr.readTemperature();
    }

    // display the current temperature

    FlashGraphics flash(_panel);
    _currentTemperatureWriter.redraw(flash,Point(570,56),result);

    // either display the desired temperature or blank out that part of the button

    if(_mode==COOKING) {

      result.Temperature=_reflow->getDesiredTemperature();
      result.Status=DefaultTemperatureReader::Result::NO_ERROR;

      _desiredTemperatureWriter.redraw(flash,Point(570,82),result);
    }
    else if(result.Status==DefaultTemperatureReader::Result::NO_ERROR) {

      // not cooking, blank out that part of the purple button if we have a connection

      Panel::LcdPanel gl(_panel.getGraphicsLibrary());

      gl.setForeground(0x9f489e);
      gl.fillRectangle(Rectangle(565,76,62,22));
    }
  }


  /*
   * Draw the power output display rectangle
   */

  void ReflowPage::drawPowerRectangle() const {

    Panel::LcdPanel& gl(_panel.getGraphicsLibrary());
    uint16_t green;

    gl.setBackground(0x9f489e);

    // draw the outline

    gl.setForeground(0xad63ac);
    Rectangle rcPower(POWER_RECT_X,POWER_RECT_Y,POWER_RECT_WIDTH,POWER_RECT_HEIGHT);
    gl.drawRectangle(rcPower);

    // erase the content

    rcPower.X++;
    rcPower.Y++;
    rcPower.Width-=2;
    rcPower.Height-=2;

    gl.clearRectangle(rcPower);

    // calculate the bar size

    rcPower.Width=((POWER_RECT_WIDTH-2)*static_cast<uint16_t>(_reflow->getRelayPercentage()))/100;

    // set the colour to vary from yellow (0%) to red (100%)

    green=(255*static_cast<uint16_t>(_reflow->getRelayPercentage()))/100;

    gl.setForeground(0xFF0000 | ((255-green) << 8));

    // fill the bar

    gl.fillRectangle(rcPower);
  }
}
