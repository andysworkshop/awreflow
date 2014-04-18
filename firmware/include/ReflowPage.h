/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#pragma once


namespace awreflow {


  /*
   * The reflow page takes the parameters gathered by the options page and
   * uses them to manage the actual reflow
   */

  class ReflowPage : public PageBase {

    protected:

      /*
       * The buttons on this page as indexes into the UiButton array
       */

      enum {
        STATUS      = 0,
        START_PAUSE = 1,
        STOP        = 2,
        EXIT        = 3,
      } _selectedButton;

      /*
       * The states that this page can be operating in
       */

      enum {
        WAITING,
        COOKING,
        FINISHED
      } _mode;

      /*
       * Graphical constants
       */

      enum {
        TOP_MARGIN    = 10,
        LEFT_MARGIN   = 45,
        RIGHT_MARGIN  = 10+75+20,
        BOTTOM_MARGIN = 30,

        Y_AXIS_HEIGHT = 360-TOP_MARGIN-BOTTOM_MARGIN,
        X_AXIS_WIDTH = 640-LEFT_MARGIN-RIGHT_MARGIN,

        POWER_RECT_X      = 565,
        POWER_RECT_Y      = 111,
        POWER_RECT_WIDTH  = 55,
        POWER_RECT_HEIGHT = 10,
      };

      const ReflowParameters& _params;
      scoped_ptr<ReflowProfile> _reflowProfile;
      scoped_ptr<Reflow> _reflow;
      TemperatureWriter _currentTemperatureWriter;
      TemperatureWriter _desiredTemperatureWriter;
      Point _lastPlottedPoint;

    protected:
      void redrawAll();
      void drawSelection(bool draw) const;
      void drawTemperatureIcon(FlashGraphics& flash);
      void handleDirection();
      bool handleOk();
      void drawAxes(FlashGraphics& flash) const;
      void drawProfile(FlashGraphics& flash) const;
      void wideLine(Panel::LcdPanel& gl,const Point& p1,const Point& p2,Panel::tCOLOUR cr) const;
      void startReflow();
      void pauseOrRestartReflow();
      void stopReflow();
      void plotProgress();
      void drawTemperatureButton();
      void drawPowerRectangle() const;

    public:
      ReflowPage(Panel& panel,Buttons& buttons,const ReflowParameters& params);

      void run();
  };
}
