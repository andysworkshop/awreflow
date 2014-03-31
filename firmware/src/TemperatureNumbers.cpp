/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */


#include "Application.h"


namespace awreflow {

  /*
   * White numbers on a grey background
   */

  const NumberWriter::Digit GreyDigits[12]=
  {
    { FlashInfo::N0_GREY::OFFSET,FlashInfo::N0_GREY::LENGTH,FlashInfo::N0_GREY::WIDTH },
    { FlashInfo::N1_GREY::OFFSET,FlashInfo::N1_GREY::LENGTH,FlashInfo::N1_GREY::WIDTH },
    { FlashInfo::N2_GREY::OFFSET,FlashInfo::N2_GREY::LENGTH,FlashInfo::N2_GREY::WIDTH },
    { FlashInfo::N3_GREY::OFFSET,FlashInfo::N3_GREY::LENGTH,FlashInfo::N3_GREY::WIDTH },
    { FlashInfo::N4_GREY::OFFSET,FlashInfo::N4_GREY::LENGTH,FlashInfo::N4_GREY::WIDTH },
    { FlashInfo::N5_GREY::OFFSET,FlashInfo::N5_GREY::LENGTH,FlashInfo::N5_GREY::WIDTH },
    { FlashInfo::N6_GREY::OFFSET,FlashInfo::N6_GREY::LENGTH,FlashInfo::N6_GREY::WIDTH },
    { FlashInfo::N7_GREY::OFFSET,FlashInfo::N7_GREY::LENGTH,FlashInfo::N7_GREY::WIDTH },
    { FlashInfo::N8_GREY::OFFSET,FlashInfo::N8_GREY::LENGTH,FlashInfo::N8_GREY::WIDTH },
    { FlashInfo::N9_GREY::OFFSET,FlashInfo::N9_GREY::LENGTH,FlashInfo::N9_GREY::WIDTH },
    { FlashInfo::DEGREESC::OFFSET,FlashInfo::DEGREESC::LENGTH,FlashInfo::DEGREESC::WIDTH },
    { FlashInfo::BROKEN_GREY::OFFSET,FlashInfo::BROKEN_GREY::LENGTH,FlashInfo::BROKEN_GREY::WIDTH }
  };


  /*
   * Orange numbers on a purple background
   */

  const NumberWriter::Digit OrangePurpleDigits[11]=
  {
    { FlashInfo::N0_ORANGE_PURPLE::OFFSET,FlashInfo::N0_ORANGE_PURPLE::LENGTH,FlashInfo::N0_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N1_ORANGE_PURPLE::OFFSET,FlashInfo::N1_ORANGE_PURPLE::LENGTH,FlashInfo::N1_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N2_ORANGE_PURPLE::OFFSET,FlashInfo::N2_ORANGE_PURPLE::LENGTH,FlashInfo::N2_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N3_ORANGE_PURPLE::OFFSET,FlashInfo::N3_ORANGE_PURPLE::LENGTH,FlashInfo::N3_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N4_ORANGE_PURPLE::OFFSET,FlashInfo::N4_ORANGE_PURPLE::LENGTH,FlashInfo::N4_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N5_ORANGE_PURPLE::OFFSET,FlashInfo::N5_ORANGE_PURPLE::LENGTH,FlashInfo::N5_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N6_ORANGE_PURPLE::OFFSET,FlashInfo::N6_ORANGE_PURPLE::LENGTH,FlashInfo::N6_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N7_ORANGE_PURPLE::OFFSET,FlashInfo::N7_ORANGE_PURPLE::LENGTH,FlashInfo::N7_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N8_ORANGE_PURPLE::OFFSET,FlashInfo::N8_ORANGE_PURPLE::LENGTH,FlashInfo::N8_ORANGE_PURPLE::WIDTH },
    { FlashInfo::N9_ORANGE_PURPLE::OFFSET,FlashInfo::N9_ORANGE_PURPLE::LENGTH,FlashInfo::N9_ORANGE_PURPLE::WIDTH },
    { FlashInfo::DEGREESC_ORANGE_PURPLE::OFFSET,FlashInfo::DEGREESC_ORANGE_PURPLE::LENGTH,FlashInfo::DEGREESC_ORANGE_PURPLE::WIDTH }
  };


  /*
   * White numbers on a purple background
   */

  const NumberWriter::Digit PurpleDigits[12]=
  {
    { FlashInfo::N0_PURPLE::OFFSET,FlashInfo::N0_PURPLE::LENGTH,FlashInfo::N0_PURPLE::WIDTH },
    { FlashInfo::N1_PURPLE::OFFSET,FlashInfo::N1_PURPLE::LENGTH,FlashInfo::N1_PURPLE::WIDTH },
    { FlashInfo::N2_PURPLE::OFFSET,FlashInfo::N2_PURPLE::LENGTH,FlashInfo::N2_PURPLE::WIDTH },
    { FlashInfo::N3_PURPLE::OFFSET,FlashInfo::N3_PURPLE::LENGTH,FlashInfo::N3_PURPLE::WIDTH },
    { FlashInfo::N4_PURPLE::OFFSET,FlashInfo::N4_PURPLE::LENGTH,FlashInfo::N4_PURPLE::WIDTH },
    { FlashInfo::N5_PURPLE::OFFSET,FlashInfo::N5_PURPLE::LENGTH,FlashInfo::N5_PURPLE::WIDTH },
    { FlashInfo::N6_PURPLE::OFFSET,FlashInfo::N6_PURPLE::LENGTH,FlashInfo::N6_PURPLE::WIDTH },
    { FlashInfo::N7_PURPLE::OFFSET,FlashInfo::N7_PURPLE::LENGTH,FlashInfo::N7_PURPLE::WIDTH },
    { FlashInfo::N8_PURPLE::OFFSET,FlashInfo::N8_PURPLE::LENGTH,FlashInfo::N8_PURPLE::WIDTH },
    { FlashInfo::N9_PURPLE::OFFSET,FlashInfo::N9_PURPLE::LENGTH,FlashInfo::N9_PURPLE::WIDTH },
    { FlashInfo::DEGREESC_PURPLE::OFFSET,FlashInfo::DEGREESC_PURPLE::LENGTH,FlashInfo::DEGREESC_PURPLE::WIDTH },
    { FlashInfo::BROKEN_PURPLE::OFFSET,FlashInfo::BROKEN_PURPLE::LENGTH,FlashInfo::BROKEN_PURPLE::WIDTH }
  };
}
