/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// place overrides here

// If you need more program area, try select and reduce rgblight modes to use.

// Selection of RGBLIGHT MODE to use.
// #if defined(LED_ANIMATIONS)
//    #define RGBLIGHT_EFFECT_BREATHING
//    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//    #define RGBLIGHT_EFFECT_SNAKE
//    #define RGBLIGHT_EFFECT_KNIGHT
//    #define RGBLIGHT_EFFECT_CHRISTMAS
//    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//    #define RGBLIGHT_EFFECT_RGB_TEST
//    #define RGBLIGHT_EFFECT_ALTERNATING
// #endif
/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REV2_CONFIG_H
#define REV2_CONFIG_H

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0001
#define MANUFACTURER    GrayHatter
#define PRODUCT         Helix_r2
#define DESCRIPTION     Did you know you could just write anything here?


#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

/* Use I2C or Serial */
#define USE_I2C
#define USE_SERIAL
//#define USE_MATRIX_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// Helix keyboard OLED support
//      see ./rules.mk: OLED_ENABLE=yes or no
#ifdef OLED_ENABLE
  #define SSD1306OLED
#endif

/* Select rows configuration */
// Rows are 4 or 5
// #define HELIX_ROWS 5 see ./rules.mk

/* key matrix size */
// Rows are doubled-up
#if  HELIX_ROWS == 4
  #define MATRIX_ROWS 8
  #define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#else
  #define MATRIX_ROWS 10
  #define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#endif

// wiring of each half
#define MATRIX_COLS 7
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }
// #define MATRIX_COL_PINS { B2, B3, B1, F7, F6, F5, F4 } //uncomment this line and comment line above if you need to reverse left-to-right key order

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN D3

//#define RGBLED_NUM 12    // Number of LEDs. see ./keymaps/default/config.h

// Helix keyboard RGB LED support
//#define RGBLIGHT_ANIMATIONS : see ./rules.mk: LED_ANIMATIONS = yes or no
//    see ./rules.mk: LED_BACK_ENABLE or LED_UNDERGLOW_ENABLE set yes
#if HELIX_ROWS == 4
  #define RGBLED_NUM 25
#else
  #define RGBLED_NUM 32
#endif

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 32
#define DRIVER_2_LED_TOTAL 32
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)


// #if RGBLED_NUM <= 6
//   #define RGBLIGHT_LIMIT_VAL 255
// #else
//   #if HELIX_ROWS == 4
//     #define RGBLIGHT_LIMIT_VAL 130
//   #else
//     #define RGBLIGHT_LIMIT_VAL 120
//   #endif
// #endif
// #define RGBLIGHT_VAL_STEP 17

// #define RGBLIGHT_HUE_STEP 10
// #define RGBLIGHT_SAT_STEP 17

// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 210

// USB_MAX_POWER_CONSUMPTION value for Helix keyboard
//  120  RGBoff, OLEDoff
//  120  OLED
//  330  RGB 6
//  300  RGB 32
//  310  OLED & RGB 32
// #define USB_MAX_POWER_CONSUMPTION 400

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION



#define DISABLE_RGB_MATRIX_ALPHAS_MODS
#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #define DISABLE_RGB_MATRIX_BREATHING
#define DISABLE_RGB_MATRIX_BAND_SAT
#define DISABLE_RGB_MATRIX_BAND_VAL
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define DISABLE_RGB_MATRIX_CYCLE_ALL
#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define DISABLE_RGB_MATRIX_DUAL_BEACON
#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
#define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
// #define DISABLE_RGB_MATRIX_RAINDROPS
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define DISABLE_RGB_MATRIX_TYPING_HEATMAP
// #define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_MULTISPLASH
// #define DISABLE_RGB_MATRIX_SOLID_SPLASH
// #define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH


#define RGB_MATRIX_LED_FLUSH_LIMIT 32


#endif // REV2_CONFIG_H

