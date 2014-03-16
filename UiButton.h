/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#pragma once


namespace awreflow {


  /**
   * Structure of a UI button. Declarations should be const to ensure they get
   * compiled into flash
   */

  struct UiButton {

    enum {
      NO_GRAPHIC = 0xFFFFFFFF           // for flash icons & text this means there isn't one
    };

    uint16_t X,Y,Width,Height;          // total surrounding box

    Panel::tCOLOUR AccentColour;        // top horizontal 1px line accent colour
    Panel::tCOLOUR BackgroundColour;    // background colour

    uint32_t IconFlashAddress;          // address in flash of the central icon
    uint16_t IconWidth;                 // width of icon
    uint16_t IconHeight;                // height of icon
    uint32_t IconSize;                  // size in bytes of the icon

    uint32_t PromptFlashAddress;        // address in flash of the lower right icon
    uint16_t PromptWidth;               // width of the prompt
    uint16_t PromptHeight;              // height of the prompt
    uint16_t PromptSize;                // size in bytes of the prompt
  };
}
