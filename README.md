# Andy's Workshop Graphics Coprocessor

This project contains the Arduino library and STM32 firmware for my graphics coprocessor project.

![Graphics Coprocessor](http://i0.wp.com/andybrown.me.uk/wk/wp-content/images/awcopper/test_image_small.jpg)

### Project documentation
[Click here](http://andybrown.me.uk/wk/2015/02/02/awcopper) to go to my website to read the full project documentation.

## Arduino library

It's in the `arduino` folder in the `awcopper.zip` file. [Here's a guide](http://arduino.cc/en/Guide/Libraries) to installing Arduino libraries. Personally I just extract the zip file into the Arduino IDE's `libraries` folder.

If you should make any modifications to the library or the examples then you can run the `build.sh` script to rebuild the `awcopper.zip` archive. `build.sh` is a shell script so you'll need to be running Linux or Cygwin on Windows.

## STM32 firmware

It's in the `stm32` folder. If you're just looking for something to flash then take a look in the `hex` folder. You'll find both the standard and overclocked versions of the firmware ready and waiting for you to flash to the STM32.

If you make any changes to the library then you'll need to rebuild it using the `scons` build system. The project documentation over at my website goes into this in a little more detail. Note that there is a dependency on my [stm32plus](https://github.com/andysworkshop/stm32plus) library so make sure you've cloned and installed stm32plus before you attempt to build the awcopper firmware.

## PC software

It's in the `pc` folder. There's just one utility included with this library, `UploadToFlash` is the C# application that allows you to send graphics files to the SPI flash IC on the board. If you're just looking for the executable program then you'll find it in the `bin\Debug` or `bin\Release` folder.

## Other software

If you're looking for the `bm2rgbi` image converter that was mentioned in the main project writeup then you'll find it in the [stm32plus](https://github.com/andysworkshop/stm32plus) library project.

## API documentation

If you're going to use the Arduino library then you'll need the API documentation. It's right here on github, take a look at the `api.md` markdown file.
