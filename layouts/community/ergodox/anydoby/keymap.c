#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define NAVI  3 // navigation and cursor keys
#define QWERTY 4  // standard QWERTY layout for Russian input
#define CMD_C 123 // dvorak location of the C character on a QWERTY keyboard
#define CMD_V 124 // dvorak location of the V character on a QWERTY keyboard
#define CMD_LEFT 125
#define CMD_RIGHT 126

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  ALT_SCRN,
  MAC_SCREENSHOT,
  MAC_HOME,
  MAC_END,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   F2 |   F3 |   F4 |  F5  |   F6 | F8   |           | 1    |   F7 |  F8  |  F9  |  F10 |  F11 |  F12   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | APScr|           |PrScn |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Del    | Alt/A|Ctrl/S|LSft/D|Cmd/F |   G  |------|           |------|   H  |   J  | K/L3 | L/L2 |   ;  |' / Cmd |
 * |--------+------+------+------+------+------| PrMac|           | L3   |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |Cmd/B |      |           |      | Alt/N| Cmd/M| ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |~L1|PgDown|PgUp| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_F2,         KC_F3,        KC_F4,       KC_F5,        KC_F6,        KC_F8,
        KC_TAB,         KC_Q,          KC_W,         KC_E,        KC_R,         KC_T,         ALT_SCRN,
        KC_DELT,        ALT_T(KC_A),   CTL_T(KC_S),  SFT_T(KC_D), GUI_T(KC_F),  KC_G,
        KC_LSFT,        CTL_T(KC_Z),   KC_X,         KC_C,        KC_V,         GUI_T(KC_B),  MAC_SCREENSHOT,
		MO(SYMB),       KC_PGDN,       KC_PGUP,      KC_LEFT,     KC_RGHT,
                                              ALT_T(KC_APP),  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_BSPC,KC_END,
        // right hand
             KC_1,     KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,             KC_F12,
             KC_PSCREEN,    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSLS,
                          KC_H,   KC_J,  LT(NAVI,KC_K),   LT(MDIA,KC_L),   KC_SCLN,GUI_T(KC_QUOT),
             KC_TILD,ALT_T(KC_N),   GUI_T(KC_M),  KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
                                  KC_UP, KC_DOWN,KC_LBRC,KC_RBRC,          MO(SYMB),
             KC_LALT,        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,KC_TAB, KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |   1  |   2  |  3   |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |    0 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  | { dv | } dv |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  | [ dv | ] dv |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *     |      |      |      |      |                                       | . dv |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Backsp|      |       |      |Hue-  |Hue+  |
 *                                 |ness- | ace  |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,   KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT, /* KC_LCBR */KC_UNDS ,/*KC_RCBR*/KC_PLUS,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,/*KC_LBRC*/KC_MINS,/*KC_RBRC*/KC_EQL,KC_TILD,KC_TRNS,
          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       RGB_MOD,KC_TRNS,
                                               KC_TRNS,
                               RGB_VAD,KC_BSPC,KC_TRNS,
       // right hand
       KC_TRNS, KC_6,   KC_7,  KC_8,   KC_9,   KC_0,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_E,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       RGB_TOG, RGB_SLD,
       KC_TRNS,
       KC_TRNS, RGB_HUD, RGB_HUI
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | WhL  | MsUp | WhR  |      |      |           |      |      |      | WhU  | WhU  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |Accel2|Accel1|      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      | Lclk |      |           |      |      |      | Prev | Next | WhD  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Rclk | Lclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WH_L, KC_MS_U, KC_WH_R, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN2, KC_BTN1,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_WH_U, KC_WH_U, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_ACL2, KC_ACL1, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_WH_D, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
/* Keymap 3: Cursor navigation and copy/paste
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Home |   Up |  End |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | PgUp |  Left|  Down|  Rght|      |------|           |------|      | RCtl |      | RShft|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | PgDn |Cmd+Lf|      |Cmd+Rg| Copy |      |           |      | Cmd+C| Cmd+V|      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      | Cut  |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Enter |
 *                                 |Paste |BckSpc|------|       |------| Tab  |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// CURSOR NAVIGATION
[NAVI] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_HOME, KC_UP, KC_END, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_PGUP, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS,
       KC_TRNS, KC_PGDOWN, MAC_HOME, KC_TRNS, MAC_END, LCTL(KC_INS), KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_DEL),
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  LSFT(KC_INS), KC_BSPACE, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_RCTRL, KC_TRNS, KC_RSHIFT, KC_TRNS, KC_TRNS,
       KC_TRNS,  M(CMD_C), M(CMD_V), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TAB,KC_ENTER
),
/* Keymap 5: QWERTY layer for cyrillic input
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   Ъ    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L0  |           |  L0  |   Y  |   U  |   I  |   O  |   P  |   Х    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |    L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[QWERTY] = LAYOUT_ergodox(  // layer 5 : default qwerty
        // left hand
        KC_RBRACKET,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_DELT,        KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_TRNS,
        KC_BSPC,        ALT_T(KC_A),         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   ALL_T(KC_NO),
        MO(SYMB),KC_QUOT,      LALT(KC_LSFT),  KC_LEFT,KC_RGHT,
                                              ALT_T(KC_APP),  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_BSPC,KC_END,
        // right hand
             KC_RGHT,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_MINS,
             KC_TRNS,    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_LBRACKET,
                          KC_H,   KC_J,  KC_K,  LT(NAVI, KC_L),   LT(MDIA, KC_SCLN),GUI_T(KC_QUOT),
             MEH_T(KC_NO),KC_N,   KC_M,  KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
                                  KC_UP, KC_DOWN,KC_LBRC,KC_RBRC,          MO(SYMB),
             KC_LALT,        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,KC_TAB, KC_ENT
    ),

};

//const uint16_t PROGMEM fn_actions[] = {
//    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
//};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
        case CMD_C:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_I);
          unregister_code(KC_I);
          unregister_code(KC_LGUI);
        }
        break;
        case CMD_V:
        if (record->event.pressed) {
            register_code(KC_LGUI);
            register_code(KC_DOT);
            unregister_code(KC_DOT);
            unregister_code(KC_LGUI);
        }
        break;
        case CMD_LEFT:
        if (record->event.pressed) {
          register_code(KC_LGUI);
          register_code(KC_LEFT);
          unregister_code(KC_LEFT);
          unregister_code(KC_LGUI);
        }
        break;
        case CMD_RIGHT:
        if (record->event.pressed) {
            register_code(KC_LGUI);
            register_code(KC_RIGHT);
            unregister_code(KC_RIGHT);
            unregister_code(KC_LGUI);
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
    case ALT_SCRN:
      if (record->event.pressed) {
         SEND_STRING(SS_TAP(X_PSCREEN));
      }
      break;
    case MAC_SCREENSHOT:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_4))));
      }
      break;
    case MAC_HOME:
      if (record->event.pressed) {
          SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
      }
      break;
    case MAC_END:
      if (record->event.pressed) {
          SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT)));
      }
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case SYMB:
            ergodox_right_led_1_on();
            break;
        case MDIA:
            ergodox_right_led_2_on();
            break;
        case NAVI:
        	ergodox_right_led_3_on();
        	break;
        case QWERTY:
        	ergodox_right_led_1_on();
        	ergodox_right_led_3_on();
        	break;
        default:
            // none
            break;
    }

};
