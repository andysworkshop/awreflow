#!/usr/bin/perl -w

use strict;
use warnings;


my($index_file,$output_file,$line,$binfile,$offset,$filesize,$name,$output,$width,$height);


open $index_file, "<", "ux/spiflash/index.txt" or die $!;
open $output_file, ">", "FlashInfo.h" or die $!;

print $output_file qq[/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */
  
namespace awreflow {
  namespace FlashInfo {
];

while(<$index_file>) {

  $line=$_;
  $line =~ m/spiflash\/(.*)\.bin=(.*)/;

  ($binfile,$offset)=($1,$2);

  $filesize = -s "ux/spiflash/${binfile}.bin";

  $name = uc $binfile;
  if($name =~ m/^\d/) {
    $name="N${name}";
  }

  $output=`file ux/${binfile}.png`;
  $output =~ m/PNG image data, (\d+) x (\d+)/;

  ($width,$height)=($1,$2);

  print $output_file "\n    namespace ${name} { enum { OFFSET=${offset}, LENGTH=${filesize}, WIDTH=${width}, HEIGHT=${height} }; }";
}

print $output_file qq[
  }
}
];
