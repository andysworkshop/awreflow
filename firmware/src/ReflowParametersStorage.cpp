/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */

#include "Application.h"


namespace awreflow {


  /*
   * Write the parameters to flash
   */

  bool ReflowParametersStorage::write(const ReflowParameters& params) {

    // the flash device deals in pages even though we require far less
    // than that.

    uint8_t page[256];

    // copy in the magic number

    *reinterpret_cast<uint32_t *>(page)=0xDEADBEEF;

    // bit-copy in the ReflowParameters structure

    memcpy(page+4,&params,sizeof(params));

    // declare the flash device

    Flash flash;

    // erase the last page

    if(!flash.eraseLastSector())
      return false;

    // write the last page

    return flash.writeLastPage(page);
  }


  /*
   * Read the parameters from flash
   */

  bool ReflowParametersStorage::read(ReflowParameters& params) {

    // the flash device deals in pages even though we require far less
    // than that.

    uint8_t page[256];

    // declare the flash device

    Flash flash;

    // read the last page

    memset(page,0,sizeof(page));

    if(!flash.readLastPage(page))
      return false;

    // check the magic number

    if(*reinterpret_cast<uint32_t *>(page)!=0xDEADBEEF)
      return false;

    // bit-copy out the parameters

    memcpy(&params,page+4,sizeof(params));

    // completed OK

    return true;
  }
}
