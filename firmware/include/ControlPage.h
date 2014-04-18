/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#pragma once


namespace awreflow {


  /*
   * The options page manages the selection of the profile and the
   * customisation of the PID parameters.
   */

  class ControlPage : public PageBase {

    protected:
      enum {
        LEADED       = 0,
        LEAD_FREE    = 1,
        REFLOW       = 2,
        PROPORTIONAL = 4,
        INTEGER      = 5,
        DERIVATIVE   = 6
      } _selectedButton;

      bool _leadedChecked;
      bool _captive;
      bool _broken;
      TemperatureWriter _temperatureWriter;
      BlueIntegerWriter _p;
      BlueIntegerWriter _i;
      BlueIntegerWriter _d;

    protected:
      void redrawAll();
      void drawSelectionAndCheck(FlashGraphics& flash,bool draw);
      void drawSelection(bool draw) const;
      void drawCheck(FlashGraphics& flash) const;
      void drawCheck(FlashGraphics& flash,uint8_t selbtn,uint32_t offset,uint32_t length,Panel::tCOLOUR colour,uint8_t deselbtn) const;
      void drawTemperature();
      void handleRight();
      void handleLeft();
      bool handleOk();
      void handleBroken();

    public:
      ControlPage(Panel& panel,Buttons& buttons,const ReflowParameters& params);

      ReflowParameters run();
  };


  /*
   * Constructor
   */

  inline ControlPage::ControlPage(Panel& panel,Buttons& buttons,const ReflowParameters& params)
    : PageBase(panel,buttons),
      _selectedButton(REFLOW),
      _leadedChecked(params.Leaded),
      _captive(false),
      _broken(false),
      _temperatureWriter(0x7a828c,GreyDigits,16,Size(22,-2)),
      _p(params.P,0,999,Point(500,85)),
      _i(params.I,0,999,Point(500,182)),
      _d(params.D,0,999,Point(500,280)) {
  }
}
