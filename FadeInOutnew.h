  /* FadeInOut.h */

#include <FastLED.h>

typedef enum
 {
 LED_ConfigColor,
 LED_ConfigFade,
 LED_ConfigHalfOn,
 LED_ConfigTrace,
 LED_ConfigSz
 } LED_Config;

typedef enum
{
  InputChan0,
  InputChan1,
  InputChan2,
  InputChan3,
  InputChanSz
} InputChan;

typedef enum
{
  LED_Color_Red,
  LED_Color_Blue,
  LED_Color_Green,
  LED_Color_White,
  LED_Color_Purple,
  LED_Color_Yellow,
  LED_Color_Pink,
  LED_Color_Orange,
  LED_Color_OrangeRed,
  LED_Color_Aqua,
  LED_Color_Sand,
  LED_Color_SandstormB,
  LED_Color_SandstormR,
  LED_Color_Ping,
  LED_Color_Duo,     // Alternate Red and Blue
  LED_Color_Raider,   // Alt Orange and White
  LED_Color_BlinkR,  // Right Blinker
  LED_Color_BlinkL,  // Left Blinker
  LED_Color_Rainbow, // This is meant to indicate when a random mixture of colors are desired
  LED_Color_Multi,   // This is meant to indicate when it is desired to have the colors cycle through all of the avaiable colors above rainbow
  LED_Color_Black    // This is more of an "off mode", must remain at end of enum
} LED_Color;

typedef enum
 {
 LED_Mode0,
 LED_Mode1,
 LED_Mode2,
 LED_Mode3,
 LED_Mode4,
 LED_Mode5,
 LED_Mode6,
 LED_Mode7,
 LED_Mode8,
 LED_Mode9,
 LED_Mode10,
 LED_Mode11,
 LED_Mode12,
 LED_Mode13,
 LED_Mode14,
 LED_Mode15,
 LED_ModeSz
 } LED_Mode;
 
const int   C_LED_PIN =           13;      // This is data pin that is being used on the Arduino
#define     C_COLOR_ORDER         GBR      // This is color order in the LED strip RBG - radioshack
#define     C_CHIPSET             WS2812   // This is chipset in the led light strip TM1803 for Radioshack strip WS2812
const int   C_NUM_LEDS =          73;     // This is the number of LEDs in the light strip
const int   C_Chan0 =             5;       // This is channel 0 input, pin on the Arduino
const int   C_Chan1 =             6;       // This is channel 1 input, pin on the Arduino
const int   C_Chan2 =             7;       // This is channel 2 input, pin on the Arduino
const int   C_Chan3 =             8;      //This is channel 3 input, pin on the Arduino

const bool C_InputConfig[LED_ModeSz][InputChanSz] = 
  {
  /* InputChan0 InputChan1 InputChan2 InputChan3 */
   { false,     false,     false,     false }, /* Mode0 */
   { false,     false,     false,     true  }, /* Mode1 */
   { false,     false,     true,      false }, /* Mode2 */
   { false,     false,     true,      true  }, /* Mode3 */
   { false,     true,      false,     false }, /* Mode4 */
   { false,     true,      false,     true  }, /* Mode5 */
   { false,     true,      true,      false }, /* Mode6 */
   { false,     true,      true,      true  },  /* Mode7 */
   { true,      false,     false,     false }, /* Mode 8*/
   { true,      false,     false,     true  }, /* Mode 9*/
   { true,      false,     true,      false }, /* Mode 10*/
   { true,      false,     true,      true  }, /*Mode 11*/
   { true,      true,      false,     false }, /*Mode 12*/
   { true,      true,      false,     true  }, /*Mode13*/
   { true,      true,      true,      false }, /*Mode 14*/
   { true,      true,      true,      true  } /*Mode 15*/
  };

const float K_PitLight            = 2500;    // delay btwn pit light change
const float K_DelayBetweenUpdate  = 5;       // This is the delay between brightness updates, in milliseconds
const float K_RB_Delay            = 10;       // Delay between update for Rainbow Light Change
const int   K_LED_MaxBrightness   = 255;     // This is the highest brightness of the leds, should not be higher than 255
const int   K_LED_MinBrightness   = 1;       // This is the lowest brightness of the leds, should not be less than 0
const float K_Debounce            = 50;      // This is the amount of time the input signal has to be high in order to determine that the input actually changed (milliseconds)
const int   K_PulseCounts         = 1;       // This is the number of pulse counts befoe switching to the next color (really only useful for multi color mode...)
const float K_ShiftTime[LED_ModeSz] =       // This is the delay between color shifts for the trace mode (milliseconds)
  {
  25, /* Mode0 */
  25, /* Mode1 */
  25, /* Mode2 */
  15, /* Mode3 */
  15, /* Mode4 */
  15, /* Mode5 */
  15, /* Mode6 */
  15, /* Mode7 */
  15, /* Mode8 */
  15, /* Mode9 */
  15, /* Mode10 */
  25, /* Mode11 */
  25, /* Mode12 */
  25, /* Mode13 */
  25, /* Mode14 */
  25  /* Mode15 */
  };
  
const int   K_LightSpacing[LED_ModeSz] =    // This is the spacing between lights in the half on mode
  {
  3, /* Mode0 */
  3, /* Mode1 */
  3, /* Mode2 */
  3, /* Mode3 */
  3, /* Mode4 */
  3, /* Mode5 */
  3, /* Mode6 */
  3, /* Mode7 */
  3, /*Mode 8*/
  3, /*Mode 9*/
  3, /*Mode 10*/
  3, /*Mode 11*/
  3, /*Mode 12*/
  3, /*Mode 13*/
  3, /*Mode 14*/
  3 /*Mode 15*/
  };

const int K_LightSettings[LED_ModeSz][LED_ConfigSz] =
  {
  /* Color                        Fade   HalfOn   Trace */
   { int(LED_Color_Orange),       0,      1,       0}, /* Mode0 - This should remain the default/off condition - Not connected to anything */
   { int(LED_Color_Red),          3,      0,       0 }, /* Mode1 - Connect to Rio */
   { int(LED_Color_Duo),          0,      0,       0 }, /* Mode2 - Connet to Rio and Pi*/
   { int(LED_Color_SandstormR),   3,      0,       1 }, /* Mode3 - Sandstorm Red Alliance*/
   { int(LED_Color_SandstormB),   3,      0,       1 }, /* Mode4 - Sandstrom Blue Alliance*/
   { int(LED_Color_Raider),       5,      0,       0 },  /* Mode5 - Raider Pride*/
   { int(LED_Color_Blue),         3,      0,       0 }, /* Mode6 - Teleop Blue Alliance*/
   { int(LED_Color_Green),        3,      0,       0 }, /* Mode7 - Override Green*/
   { int(LED_Color_Ping),         3,      0,       0 }, /* Mode8 - Endgame Raise*/
   { int(LED_Color_Rainbow),      0,      0,       0 }, /* Mode9 - Endgame Drive*/
   { int(LED_Color_Rainbow),      6,      0,       1 }, /* Mode10 - Endgame Done*/
   { int(LED_Color_Rainbow),      6,      0,       1 }, /* Mode11 - Unused*/
   { int(LED_Color_Ping),         10,     0,       0 }, /* Mode13 - Unused*/
   { int(LED_Color_BlinkL),       10,     0,       0 }, /* Mode12 - Unused*/
   { int(LED_Color_Aqua),         0,      0,       0 }, /* Mode14 - Unused*/
   { int(LED_Color_White),        0,      1,       1 }  /* Mode15 - Unused*/
  };
