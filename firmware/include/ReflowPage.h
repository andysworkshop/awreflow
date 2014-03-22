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

      enum {
        STATUS = 0,
        START  = 1,
        STOP   = 2,
        EXIT   = 3,
      } _selectedButton;

      enum {
        WAITING,
        COOKING,
        FINISHED
      } _mode;

      enum {
        TOP_MARGIN    = 10,
        LEFT_MARGIN   = 45,
        RIGHT_MARGIN  = 10+75+20,
        BOTTOM_MARGIN = 30
      };

      const ReflowParameters& _params;

    protected:
      void redrawAll();
      void drawSelection(bool draw) const;
      void drawTemperatureIcon(Flash& flash);
      void handleDirection();
      bool handleOk();
      void drawAxes(Flash& flash) const;
      void wideLine(const Point& p1,const Point& p2,Panel::tCOLOUR cr);

    public:
      ReflowPage(Panel& panel,Buttons& buttons,const ReflowParameters& params);

      void run();
  };


  /*
   * Constructor
   */

  inline ReflowPage::ReflowPage(Panel& panel,Buttons& buttons,const ReflowParameters& params)
    : PageBase(panel,buttons),
      _selectedButton(START),
      _mode(WAITING),
      _params(params) {
  }
}
