/* Copyright 2022 splitkb.com <support@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_EFFECT_BREATHING
#endif

// Set the mouse settings to a comfortable speed/accuracy trade-off,
// assuming a screen refresh rate of 60 Htz or higher
// The default is 50. This makes the mouse ~3 times faster and more accurate
#define MOUSEKEY_INTERVAL 16
// The default is 20. Since we made the mouse about 3 times faster with the previous setting,
// give it more time to accelerate to max speed to retain precise control over short distances.
#define MOUSEKEY_TIME_TO_MAX 40
// The default is 300. Let's try and make this as low as possible while keeping the cursor responsive
#define MOUSEKEY_DELAY 100
// It makes sense to use the same delay for the mouseweel
#define MOUSEKEY_WHEEL_DELAY 100
// The default is 100
#define MOUSEKEY_WHEEL_INTERVAL 50
// The default is 40
#define MOUSEKEY_WHEEL_TIME_TO_MAX 100

// Always connect the USB cable to the left side of the two keyboard halves
#define MASTER_LEFT
#define DETECT_USB_SPLIT
#define SPLIT_USB_DETECT

// Pick good defaults for enabling homerow modifiers
#define TAPPING_TERM 180

// Disable PERMISSIVE_HOLD since it does not quite suite my style of typings, see
// https://docs.qmk.fm/tap_hold#permissive-hold
//#define PERMISSIVE_HOLD

// https://docs.qmk.fm/tap_hold#quick-tap-term
#define QUICK_TAP_TERM 150

// https://docs.qmk.fm/tap_hold#retro-tapping
// #define RETRO_TAPPING

// Active CAPS_WORD when left and right shift is pressed at the same time
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Tapping this number of times holds the key until tapped once again.
#define ONESHOT_TAP_TOGGLE 5

// Time (in ms) before the one shot key is released
#define ONESHOT_TIMEOUT 5000

#define TAPPING_TOGGLE 5

// Turn off after 60 seconds.
#define LAYER_LOCK_IDLE_TIMEOUT 60000

// Set the number of combos present
// #define COMBO_COUNT 3
