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
        STATUS    = 0,
        STARTSTOP = 1,
        DOWNLOAD  = 2,
        EXIT      = 3,
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
        X_AXIS_WIDTH = 640-LEFT_MARGIN-RIGHT_MARGIN
      };

      const ReflowParameters& _params;
      ReflowProfile *_reflowProfile;
      Reflow *_reflow;
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
      void stopReflow();
      void plotProgress();
      void transmitResults() const;
      void drawTemperatureButton();

    public:
      ReflowPage(Panel& panel,Buttons& buttons,const ReflowParameters& params);
      ~ReflowPage();

      void run();
  };
}
