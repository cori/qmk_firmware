/* Copyright 2020 elijahblake81
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

#include QMK_KEYBOARD_H

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
};

#include "keymap.h"
#include "print.h"

uint32_t base_mode = 1; // Unlocked animation (solid)
uint32_t lock_mode = 15; // Locked animation (knight)
uint16_t hue = 150; // Color of the leds, but it doesn't seem to match HSV pickers like https://alloyui.com/examples/color-picker/hsv.html
uint16_t sat = 255;
uint16_t val = 255;

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

#define _QWERTY 0
#define _FUNC 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, _______, KC_END, \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          KC_MPLY, KC_VOLU, \
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, _______, _______, _______, _______,          KC_PGUP, KC_VOLD, \
        _______, _______, _______,                            _______,                            _______, MO(1), KC_HOME, KC_PGDN, KC_END  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

#ifdef _______
#undef _______
#define _______ {0, 0, 0}

// const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
//     [_QWERTY] = {
//         SPRING, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, SPRING, SPRING,
//         SPRING, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, SPRING,
//         SPRING, _______,   _______,   _______,   _______, _______, _______, _______, _______, _______, _______, _______,          SPRING, SPRING,
//         SPRING, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, SPRING,          SPRING,   SPRING,
//         SPRING, SPRING, SPRING,                            SPRING,                            SPRING, SPRING,   SPRING,   SPRING, SPRING
//         //UnderGlow
//         // CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,
//         // CHART,                                                                                                                        CHART,
//         // CHART,                                                                                                                        CHART,
//         // CHART,                                                                                                                        CHART,
//         // CHART,                                                                                                                        CHART,
//         // CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART
//         },
//     [_FUNC] = {
//         CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,    CHART,   CHART,   CHART,   CHART,     CHART,    BLUE,
//         GOLD,    PINK,    AZURE,   PINK,    TURQ,    TEAL,    _______, RED,     _______,  _______, GREEN,   BLUE,    GOLD,      _______,  BLUE,
//         TEAL,    MAGENT,  AZURE,   MAGENT,  TURQ,    TEAL,    _______, _______, _______,  _______, _______, _______,                GOLD, BLUE,
//         _______, _______, _______, _______, _______, RED,     RED,     RED,     _______,  _______, _______, _______,                GOLD, BLUE,
//         _______, _______, _______,                            GOLD,                                _______, _______,       PURPLE,  GOLD, PURPLE
//         //UnderGlow
//         // CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,
//         // CYAN,                                                                                                                        CYAN,
//         // CYAN,                                                                                                                        CYAN,
//         // CYAN,                                                                                                                        CYAN,
//         // CYAN,                                                                                                                        CYAN,
//         // CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN,   CYAN
//     },
// };

#undef _______
#define _______ KC_TRNS
#endif

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    // Enable or disable debugging
    debug_enable=false;
    debug_matrix=false;
    debug_keyboard=false;
};

void keyboard_post_init_user(void) {
  // Call the post init code.
//   rgblight_enable_noeeprom(); // enables Rgb, without saving settings
//   rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
//   rgblight_mode(); // sets mode to Fast breathing without saving
  rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
  rgb_matrix_sethsv(HSV_PURPLE);
    //rgb_enabled_flag = true;          // Initially, keyboard RGB is enabled. Change to false config.h initializes RGB disabled.
    // rgblight_mode(lock_mode);
    // rgblight_enable();
    // rgblight_sethsv(hue, sat, val);
    dprintf("Initializing in matrix_init_user");
    // rgblight_enable();
    // rgblight_mode(RGBLIGHT_MODE_BREATHE + 1);
    // rgblight_sethsv(HSV_ORANGE);
//     rgblight_sethsv_at(HSV_BLUE, 17);
}

// void keyboard_post_init_user(void) {
//     rgb_matrix_enable();
// // #ifdef RGBLIGHT_ENABLE
//     // rgblight_enable_noeeprom();
//     // rgblight_sethsv_noeeprom(HSV_PURPLE);
//     // rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
// // #endif
// }


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

uint32_t layer_state_set_user(uint32_t state) {
//   uint8_t layer = biton32(state);
//   led_t led_state = host_keyboard_led_state();
//   switch (layer) {
    switch (get_highest_layer(state)) {
        case _QWERTY: // Name of my 0-th layer (includes alphas and caps-lock)
            // matrix_init_user();
            // rgblight_sethsv(0, 255, 255); // sets the color to teal/cyan without saving
            rgb_matrix_sethsv(HSV_MAGENTA); // sets the color to teal/cyan without saving
// rgb_matrix_set_color_all(RGB_PURPLE);
            // rgblight_sethsv(HSV_PURPLE);
            // rgblight_sethsv_at(HSV_BLUE, 0, 2);
            // rgb_matrix_sethsv(192, 112, 255);
            // rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
            // rgb_matrix_set_color_all(130, 255, 255);
            break;
        case _FUNC:
            dprintf("Switching to L_FUNC");
            // rgblight_mode(42);
            // rgblight_sethsv(HSV_BLUE); // 
            rgb_matrix_sethsv(HSV_BLUE); // sets the color to teal/cyan without saving
// rgb_matrix_set_color_all(RGB_BLUE);            // rgblight_mode(7);
            // rgblight_sethsv_at(36, 255, 255, 3);
            // rgblight_sethsv_coral_at(3);
            break;
    }
  return state;
}

// led_instruction_t led_instructions[] = {
//     //LEDs are normally inactive, no processing is performed on them
//     //Flags are used in matching criteria for an LED to be active and indicate how to color it
//     //Flags can be found in tmk_core/protocol/arm_atsam/md_rgb_matrix.h (prefixed with LED_FLAG_)
//     //LED IDs can be found in config_led.h in the keyboard's directory
//     //Examples are below

//     //All LEDs use the user's selected pattern (this is the factory default)
//     //  { .flags = LED_FLAG_USE_ROTATE_PATTERN },

//     //Specific LEDs use the user's selected pattern while all others are off
//     // { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN, .id0 = 0xFFFFFFFF, .id1 = 0xAAAAAAAA, .id2 = 0x55555555, .id3 = 0x11111111 },

//     //Specific LEDs use specified RGB values while all others are off
//     // { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 0xFF, .id1 = 0x00FF, .id2 = 0x0000FF00, .id3 = 0xFF000000, .r = 75, .g = 150, .b = 225 },

//     //All LEDs use the user's selected pattern
//     //On layer 1, all key LEDs (except the top row which keeps active pattern) are red while all edge LEDs are green
//     //When layer 1 is active, key LEDs use red    (id0  32 -  16: 1111 1111 1111 1111 1000 0000 0000 0000 = 0xFFFF8000) (except top row 15 - 1)
//     //When layer 1 is active, key LEDs use red    (id1  64 -  33: 1111 1111 1111 1111 1111 1111 1111 1111 = 0xFFFFFFFF)
//     //When layer 1 is active, key LEDs use red    (id2  67 -  65: 0000 0000 0000 0000 0000 0000 0000 0111 = 0x00000007)
//     //When layer 1 is active, edge LEDs use green (id2  95 -  68: 1111 1111 1111 1111 1111 1111 1111 1000 = 0xFFFFFFF8)
//     //When layer 1 is active, edge LEDs use green (id3 105 -  96: 0000 0000 0000 0000 0000 0011 1111 1111 = 0x000003FF)
//     // { .flags = LED_FLAG_USE_ROTATE_PATTERN },
//     // { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, .id0 = 0xFFFF8000, .id1 = 0xFFFFFFFF, .id2 = 0x00000007, .r = 255, .layer = 1 },
//     // { .flags = LED_FLAG_MATCH_ID | LED_FLAG_MATCH_LAYER | LED_FLAG_USE_RGB, .id2 = 0xFFFFFFF8, .id3 = 0x000003FF, .g = 127, .layer = 1 },

//     //All key LEDs use red while edge LEDs use the active pattern
//     //All key LEDs use red     (id0  32 -   1: 1111 1111 1111 1111 1111 1111 1111 1111 = 0xFFFFFFFF)
//     //All key LEDs use red     (id1  64 -  33: 1111 1111 1111 1111 1111 1111 1111 1111 = 0xFFFFFFFF)
//     //All key LEDs use red     (id2  67 -  65: 0000 0000 0000 0000 0000 0000 0000 0111 = 0x00000007)
//     //Edge uses active pattern (id2  95 -  68: 1111 1111 1111 1111 1111 1111 1111 1000 = 0xFFFFFFF8)
//     //Edge uses active pattern (id3 105 -  96: 0000 0000 0000 0000 0000 0011 1111 1111 = 0x000003FF)
//     // { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 0xFFFFFFFF, .id1 = 0xFFFFFFFF, .id2 = 0x00000007, .r = 255 },
//     // { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN , .id2 = 0xFFFFFFF8, .id3 = 0x000003FF },

//     // mods
//     { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB, .id0 = 1610670081,.id1 = 4286585856,.id2 = 7,.id3 = 0, .r = 255, .g = 0, .b = 255 },
//     // underglow
//     { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_PATTERN, .id0 = 0,.id1 = 0,.id2 = 4294967288,.id3 = 511, .r = 25, .g = 200, .b = 255, .pattern_id = 3 },
//     //  alphakeys
//     { .flags = LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB | LED_FLAG_USE_ROTATE_PATTERN, .id0 = 2684297214,.id1 = 8381439,.id2 = 0,.id3 = 0, .r = 255, .g = 255, .b = 255},

//     //end must be set to 1 to indicate end of instruction set
//      { .end = 1 }
// };

