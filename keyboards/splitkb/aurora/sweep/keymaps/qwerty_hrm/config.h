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

#define TAPPING_TERM 300

// https://docs.qmk.fm/tap_hold#permissive-hold
// If you press a dual-role key, tap another key (press and release) and then release the
// dual-role key, all within the tapping term, by default the dual-role key will perform its tap
// action. If the PERMISSIVE_HOLD option is enabled, the dual-role key will perform its hold
// action instead. This becomes very powerful together with a longer TAPPING_TERM.
#define PERMISSIVE_HOLD

// https://docs.qmk.fm/tap_hold#flow-tap
// Flow Tap modifies mod-tap MT and layer-tap LT keys such that when pressed within a short
// timeout of the preceding key, the tapping behavior is triggered. This is particularly
// useful for home row mods to avoid accidental mod triggers. It basically disables the hold
// behavior during fast typing, creating a "flow of taps." This also helps to reduce the input
// lag of tap-hold keys during fast typing, since the tapped behavior is sent immediately.
#define FLOW_TAP_TERM 150

// https://docs.qmk.fm/tap_hold#speculative-hold
// Speculative Hold makes mod-tap keys more responsive by applying the modifier instantly
// on keydown, before the tap-hold decision is made. This is especially useful for actions
// like Shift+Click with a mouse, which can feel laggy with standard mod-taps.
#define SPECULATIVE_HOLD

// https://docs.qmk.fm/tap_hold#quick-tap-term
// When the user holds a key after tapping it, the tapping function is repeated by default,
// rather than activating the hold function. This allows keeping the ability to auto-repeat
// the tapping function of a dual-role key. QUICK_TAP_TERM enables fine tuning of that ability.
// If set to 0, it will remove the auto-repeat ability and activate the hold function instead.
#define QUICK_TAP_TERM 150

// https://docs.qmk.fm/tap_hold#retro-tapping
// #define RETRO_TAPPING

// Active CAPS_WORD when left and right shift is pressed at the same time
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Auto shift settings
#define AUTO_SHIFT_TIMEOUT 130

// Do not Auto Shift special keys, which include -_, =+, [{, ]}, ;:, '", ,<, .>, /?, and the KC_TAB.
#define NO_AUTO_SHIFT_SPECIAL

// Do not Auto Shift numeric keys, zero through nine.
#define NO_AUTO_SHIFT_NUMERIC

// Do not Auto Shift alpha characters, which include A through Z.
#define NO_AUTO_SHIFT_ALPHA

// Tapping this number of times holds the key until tapped once again.
#define ONESHOT_TAP_TOGGLE 2

// Time (in ms) before the one shot key is released
#define ONESHOT_TIMEOUT 5000

#define TAPPING_TOGGLE 2

// Turn off after 60 seconds.
#define LAYER_LOCK_IDLE_TIMEOUT 60000

// Set the number of combos present
// #define COMBO_COUNT 3
