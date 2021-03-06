/*
 * Andy's Workshop Reflow Oven Controller.
 * Copyright (c) 2014 Andy Brown. All rights reserved.
 * Please see website (http://www.andybrown.me.uk) for full details.
 */
  
namespace awreflow {
  namespace FlashInfo {

    namespace N0_BLACK { enum { OFFSET=0, LENGTH=234, WIDTH=9, HEIGHT=13 }; }
    namespace N0_BLUE { enum { OFFSET=256, LENGTH=630, WIDTH=15, HEIGHT=21 }; }
    namespace N0_GREY { enum { OFFSET=1024, LENGTH=384, WIDTH=12, HEIGHT=16 }; }
    namespace N0_ORANGE_PURPLE { enum { OFFSET=1536, LENGTH=280, WIDTH=10, HEIGHT=14 }; }
    namespace N0_PURPLE { enum { OFFSET=2048, LENGTH=300, WIDTH=10, HEIGHT=15 }; }
    namespace N1_BLACK { enum { OFFSET=2560, LENGTH=130, WIDTH=5, HEIGHT=13 }; }
    namespace N1_BLUE { enum { OFFSET=2816, LENGTH=420, WIDTH=10, HEIGHT=21 }; }
    namespace N1_GREY { enum { OFFSET=3328, LENGTH=224, WIDTH=7, HEIGHT=16 }; }
    namespace N1_ORANGE_PURPLE { enum { OFFSET=3584, LENGTH=168, WIDTH=6, HEIGHT=14 }; }
    namespace N1_PURPLE { enum { OFFSET=3840, LENGTH=210, WIDTH=7, HEIGHT=15 }; }
    namespace N2_BLACK { enum { OFFSET=4096, LENGTH=208, WIDTH=8, HEIGHT=13 }; }
    namespace N2_BLUE { enum { OFFSET=4352, LENGTH=630, WIDTH=15, HEIGHT=21 }; }
    namespace N2_GREY { enum { OFFSET=5120, LENGTH=320, WIDTH=10, HEIGHT=16 }; }
    namespace N2_ORANGE_PURPLE { enum { OFFSET=5632, LENGTH=252, WIDTH=9, HEIGHT=14 }; }
    namespace N2_PURPLE { enum { OFFSET=5888, LENGTH=300, WIDTH=10, HEIGHT=15 }; }
    namespace N3_BLACK { enum { OFFSET=6400, LENGTH=234, WIDTH=9, HEIGHT=13 }; }
    namespace N3_BLUE { enum { OFFSET=6656, LENGTH=588, WIDTH=14, HEIGHT=21 }; }
    namespace N3_GREY { enum { OFFSET=7424, LENGTH=320, WIDTH=10, HEIGHT=16 }; }
    namespace N3_ORANGE_PURPLE { enum { OFFSET=7936, LENGTH=252, WIDTH=9, HEIGHT=14 }; }
    namespace N3_PURPLE { enum { OFFSET=8192, LENGTH=330, WIDTH=11, HEIGHT=15 }; }
    namespace N4_BLACK { enum { OFFSET=8704, LENGTH=234, WIDTH=9, HEIGHT=13 }; }
    namespace N4_BLUE { enum { OFFSET=8960, LENGTH=672, WIDTH=16, HEIGHT=21 }; }
    namespace N4_GREY { enum { OFFSET=9728, LENGTH=352, WIDTH=11, HEIGHT=16 }; }
    namespace N4_ORANGE_PURPLE { enum { OFFSET=10240, LENGTH=280, WIDTH=10, HEIGHT=14 }; }
    namespace N4_PURPLE { enum { OFFSET=10752, LENGTH=360, WIDTH=12, HEIGHT=15 }; }
    namespace N5_BLACK { enum { OFFSET=11264, LENGTH=234, WIDTH=9, HEIGHT=13 }; }
    namespace N5_BLUE { enum { OFFSET=11520, LENGTH=588, WIDTH=14, HEIGHT=21 }; }
    namespace N5_GREY { enum { OFFSET=12288, LENGTH=352, WIDTH=11, HEIGHT=16 }; }
    namespace N5_ORANGE_PURPLE { enum { OFFSET=12800, LENGTH=280, WIDTH=10, HEIGHT=14 }; }
    namespace N5_PURPLE { enum { OFFSET=13312, LENGTH=330, WIDTH=11, HEIGHT=15 }; }
    namespace N6_BLACK { enum { OFFSET=13824, LENGTH=234, WIDTH=9, HEIGHT=13 }; }
    namespace N6_BLUE { enum { OFFSET=14080, LENGTH=630, WIDTH=15, HEIGHT=21 }; }
    namespace N6_GREY { enum { OFFSET=14848, LENGTH=384, WIDTH=12, HEIGHT=16 }; }
    namespace N6_ORANGE_PURPLE { enum { OFFSET=15360, LENGTH=252, WIDTH=9, HEIGHT=14 }; }
    namespace N6_PURPLE { enum { OFFSET=15616, LENGTH=360, WIDTH=12, HEIGHT=15 }; }
    namespace N7_BLACK { enum { OFFSET=16128, LENGTH=208, WIDTH=8, HEIGHT=13 }; }
    namespace N7_BLUE { enum { OFFSET=16384, LENGTH=588, WIDTH=14, HEIGHT=21 }; }
    namespace N7_GREY { enum { OFFSET=17152, LENGTH=352, WIDTH=11, HEIGHT=16 }; }
    namespace N7_ORANGE_PURPLE { enum { OFFSET=17664, LENGTH=280, WIDTH=10, HEIGHT=14 }; }
    namespace N7_PURPLE { enum { OFFSET=18176, LENGTH=330, WIDTH=11, HEIGHT=15 }; }
    namespace N8_BLACK { enum { OFFSET=18688, LENGTH=234, WIDTH=9, HEIGHT=13 }; }
    namespace N8_BLUE { enum { OFFSET=18944, LENGTH=672, WIDTH=16, HEIGHT=21 }; }
    namespace N8_GREY { enum { OFFSET=19712, LENGTH=384, WIDTH=12, HEIGHT=16 }; }
    namespace N8_ORANGE_PURPLE { enum { OFFSET=20224, LENGTH=280, WIDTH=10, HEIGHT=14 }; }
    namespace N8_PURPLE { enum { OFFSET=20736, LENGTH=360, WIDTH=12, HEIGHT=15 }; }
    namespace N9_BLACK { enum { OFFSET=21248, LENGTH=234, WIDTH=9, HEIGHT=13 }; }
    namespace N9_BLUE { enum { OFFSET=21504, LENGTH=630, WIDTH=15, HEIGHT=21 }; }
    namespace N9_GREY { enum { OFFSET=22272, LENGTH=384, WIDTH=12, HEIGHT=16 }; }
    namespace N9_ORANGE_PURPLE { enum { OFFSET=22784, LENGTH=280, WIDTH=10, HEIGHT=14 }; }
    namespace N9_PURPLE { enum { OFFSET=23296, LENGTH=360, WIDTH=12, HEIGHT=15 }; }
    namespace BROKEN_GREY { enum { OFFSET=23808, LENGTH=1352, WIDTH=26, HEIGHT=26 }; }
    namespace BROKEN_PURPLE { enum { OFFSET=25344, LENGTH=1352, WIDTH=26, HEIGHT=26 }; }
    namespace CONTROL { enum { OFFSET=26880, LENGTH=4368, WIDTH=91, HEIGHT=24 }; }
    namespace DEGREESC { enum { OFFSET=31488, LENGTH=640, WIDTH=20, HEIGHT=16 }; }
    namespace DEGREESC_BLACK { enum { OFFSET=32256, LENGTH=360, WIDTH=15, HEIGHT=12 }; }
    namespace DEGREESC_ORANGE_PURPLE { enum { OFFSET=32768, LENGTH=532, WIDTH=19, HEIGHT=14 }; }
    namespace DEGREESC_PURPLE { enum { OFFSET=33536, LENGTH=608, WIDTH=19, HEIGHT=16 }; }
    namespace DERIVATIVE { enum { OFFSET=34304, LENGTH=1960, WIDTH=70, HEIGHT=14 }; }
    namespace EXIT { enum { OFFSET=36352, LENGTH=1250, WIDTH=25, HEIGHT=25 }; }
    namespace EXIT_DISABLED { enum { OFFSET=37632, LENGTH=1250, WIDTH=25, HEIGHT=25 }; }
    namespace FLAME { enum { OFFSET=38912, LENGTH=5796, WIDTH=46, HEIGHT=63 }; }
    namespace INTEGER { enum { OFFSET=44800, LENGTH=1800, WIDTH=50, HEIGHT=18 }; }
    namespace LEAD { enum { OFFSET=46848, LENGTH=1184, WIDTH=37, HEIGHT=16 }; }
    namespace LEADCHECKED { enum { OFFSET=48128, LENGTH=1352, WIDTH=26, HEIGHT=26 }; }
    namespace LEADFREE { enum { OFFSET=49664, LENGTH=2336, WIDTH=73, HEIGHT=16 }; }
    namespace LEADFREECHECKED { enum { OFFSET=52224, LENGTH=1352, WIDTH=26, HEIGHT=26 }; }
    namespace LOGO640X360 { enum { OFFSET=53760, LENGTH=460800, WIDTH=640, HEIGHT=360 }; }
    namespace OVEN { enum { OFFSET=514816, LENGTH=5760, WIDTH=64, HEIGHT=45 }; }
    namespace PAUSE { enum { OFFSET=520704, LENGTH=1352, WIDTH=26, HEIGHT=26 }; }
    namespace PAUSE_DISABLED { enum { OFFSET=522240, LENGTH=1352, WIDTH=26, HEIGHT=26 }; }
    namespace POINT_BLUE { enum { OFFSET=523776, LENGTH=48, WIDTH=4, HEIGHT=6 }; }
    namespace PROPORTIONAL { enum { OFFSET=524032, LENGTH=3096, WIDTH=86, HEIGHT=18 }; }
    namespace REFLOW { enum { OFFSET=527360, LENGTH=1470, WIDTH=49, HEIGHT=15 }; }
    namespace SNAGCU { enum { OFFSET=528896, LENGTH=7360, WIDTH=115, HEIGHT=32 }; }
    namespace SNPB { enum { OFFSET=536320, LENGTH=3900, WIDTH=75, HEIGHT=26 }; }
    namespace START { enum { OFFSET=540416, LENGTH=1352, WIDTH=26, HEIGHT=26 }; }
    namespace START_DISABLED { enum { OFFSET=541952, LENGTH=1352, WIDTH=26, HEIGHT=26 }; }
    namespace STOP { enum { OFFSET=543488, LENGTH=1352, WIDTH=26, HEIGHT=26 }; }
    namespace STOP_DISABLED { enum { OFFSET=545024, LENGTH=1352, WIDTH=26, HEIGHT=26 }; }
    namespace THERMOMETER { enum { OFFSET=546560, LENGTH=650, WIDTH=13, HEIGHT=25 }; }
  }
}
