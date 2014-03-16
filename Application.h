/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#pragma once

// list all the includes in one place. This application is small enough to do that without
// a significant compile speed penalty and we gain through not having #include hell scattered
// throughout the code.

// stm32plus includes that we require

#include "config/stm32plus.h"
#include "config/spi.h"
#include "config/button.h"
#include "config/timer.h"
#include "config/display/tft.h"

// make the declarations less verbose

using namespace stm32plus;
using namespace stm32plus::display;

// our application headers

#include "FlashInfo.h"
#include "ProfileType.h"
#include "Buttons.h"
#include "Panel.h"
#include "UiButton.h"
#include "Flash.h"
#include "PageBase.h"
#include "TemperatureReader.h"
#include "Max6675TemperatureReader.h"
#include "ControlPage.h"
#include "Reflow.h"
#include "SplashScreen.h"
#include "TemperatureReader.h"
