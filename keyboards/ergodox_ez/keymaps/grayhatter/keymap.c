#include "config.h"
#include QMK_KEYBOARD_H
#include "ergodox_ez.h"

#include "rgblight.h"
#include "action_layer.h"
#include "version.h"

#include "process_leader.h"


enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE, // can always be here
    EPRM,
    RGB_SLD,

};

typedef enum {
    L_DFLT = 0,
    // L_TRANS,
    L_NAV,
    L_NAV_S,
    L_KEYS,
    L_GAME_SC,
    // L_GAME_SC2,
    L_GAME_2,
    L_QWERTY,
    // L_DFLT = 1,
} LAYER_T;


/*  ---------- LEFT HAND -----------   ---------- RIGHT HAND ---------- */
#define LAYOUT_ergodox_pretty(                                           \
    L00,L01,L02,L03,L04,L05,L06,           R00,R01,R02,R03,R04,R05,R06,  \
    L10,L11,L12,L13,L14,L15,L16,           R10,R11,R12,R13,R14,R15,R16,  \
    L20,L21,L22,L23,L24,L25,                   R21,R22,R23,R24,R25,R26,  \
    L30,L31,L32,L33,L34,L35,L36,           R30,R31,R32,R33,R34,R35,R36,  \
    L40,L41,L42,L43,L44,                           R42,R43,R44,R45,R46,  \
                            L55,L56,   R50,R51,                          \
                                L54,   R52,                              \
                        L53,L52,L51,   R55,R54,R53 )                     \
                                          \
   /* matrix positions */                 \
    {                                     \
    { L00, L10, L20, L30, L40, KC_NO },   \
    { L01, L11, L21, L31, L41, L51 },     \
    { L02, L12, L22, L32, L42, L52 },     \
    { L03, L13, L23, L33, L43, L53 },     \
    { L04, L14, L24, L34, L44, L54 },     \
    { L05, L15, L25, L35, KC_NO, L55 },   \
    { L06, L16, KC_NO, L36, KC_NO, L56 }, \
                                          \
    { R00, R10, KC_NO, R30,KC_NO, R50 },  \
    { R01, R11, R21, R31,KC_NO, R51 },    \
    { R02, R12, R22, R32, R42, R52 },     \
    { R03, R13, R23, R33, R43, R53 },     \
    { R04, R14, R24, R34, R44, R54 },     \
    { R05, R15, R25, R35, R45, R55 },     \
    { R06, R16, R26, R36, R46, KC_NO }    \
    }


#define LG LGUI
#define LC LCTL
#define KC_LG KC_LGUI
#define KC_RG KC_RGUI

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_DFLT] = LAYOUT_ergodox_pretty(
        KC_ESCAPE,  KC_1,       KC_2,       KC_3,       KC_4,       KC_5,   KC_MINUS,                                   KC_BSLASH,  KC_6,   KC_7,       KC_8,       KC_9,       KC_0,       KC_DEL,
        KC_TAB,     KC_QUOTE,   KC_COMMA,   KC_DOT,     KC_P,       KC_Y,   KC_F23,                                     KC_SLASH,   KC_F,   KC_G,       KC_C,       KC_R,       KC_L,       KC_BSPC,
        KC_LEAD,    KC_A,       KC_O,       KC_E,       KC_U,       KC_I,                                                           KC_D,   KC_H,       KC_T,       KC_N,       KC_S,       KC_ENTER,
        KC_LSHIFT,  KC_SCOLON,  KC_Q,       KC_J,       KC_K,       KC_X,   XXXXXXX,                                    KC_EQUAL,   KC_B,   KC_M,       KC_W,       KC_V,       KC_Z,       KC_RSHIFT,
          KC_LCTRL,  KC_LALT,   KC_GRAVE,   KC_SPACE,   KC_LG,                                                                              XXXXXXX,    KC_MINUS,   KC_DEL,     KC_LEFT,    KC_RIGHT,
                                                                            TG(L_GAME_SC), TG(L_KEYS),      KC_LBRC,    KC_RBRC,
                                                                                           OSL(L_KEYS),     KC_UP,
                                                                KC_SPACE,   MO(L_NAV),     MO(L_KEYS),      KC_DOWN,    KC_ENTER,   MO(L_NAV)
    ),

    [L_NAV] = LAYOUT_ergodox_pretty(
        TG(L_NAV),  KC_F1,      KC_F2,          KC_F3,      KC_F4,          KC_F5,      KC_F6,                              KC_F7,          KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     _______,
        KC_VOLU,    _______,    KC_HOME,        KC_UP,      KC_END,         KC_PGUP,    KC_F24,                             LSFT(KC_INS),   _______,    KC_HOME,    KC_UP,      KC_END,     _______,    _______,
        KC_VOLD,    _______,    KC_LEFT,        KC_DOWN,    KC_RIGHT,       KC_PGDOWN,                                                      _______,    KC_LEFT,    KC_DOWN,    KC_RIGHT,   _______,    _______,
        _______,    _______,    LC(KC_LEFT),    KC_DOWN,    LC(KC_RIGHT),   KC_PGDOWN,  _______,                            LC(KC_INS),     _______,    KC_DEL,     KC_PGDOWN,  _______,    _______,    TG(L_QWERTY),
          _______,  _______,    _______,        _______,    _______,                                                                                    RGB_RMOD,   RGB_MOD,    RGB_HUI,    RGB_HUD,    RGB_TOG,
                                                                                            _______,    _______,    KC_HOME,    KC_END,
                                                                                                        _______,    _______,
                                                                                KC_SPC,     _______,    _______,    _______,    _______,    _______
    ),

    [L_NAV_S] = LAYOUT_ergodox_pretty(
        _______,    KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,     KC_F18,                                 KC_F19,     KC_F20,     KC_F21,     KC_F22,     KC_F23,     KC_F24,     _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,                                _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,                                                        _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,                                _______,    _______,    _______,    _______,    _______,    _______,    _______,
          _______,  _______,    _______,    _______,    _______,                                                                                RGB_RMOD,   RGB_MOD,    RGB_HUI,    RGB_HUD,    RGB_TOG,
                                                                                _______,    _______,        _______,    _______,
                                                                                            _______,        _______,
                                                                    _______,    _______,    _______,        _______,    _______,    _______
    ),

    [L_KEYS] = LAYOUT_ergodox_pretty(
        KC_GRAVE,   KC_F1,      KC_F2,      KC_F3,          KC_F4,      KC_F5,      KC_F6,                              KC_F7,          KC_F8,          KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_F12,         _______,
        _______,    _______,    LG(KC_1),   LG(KC_2),       LG(KC_3),   _______,    KC_F24,                             LSFT(KC_INS),   KC_KP_SLASH,    KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_KP_MINUS,    KC_NUMLOCK,
        _______,    _______,    LG(KC_4),   LG(KC_5),       LG(KC_6),   _______,                                                        KC_PAST,        KC_KP_1,    KC_KP_2,    KC_KP_3,    KC_KP_PLUS,     KC_KP_MINUS,
        _______,    _______,    LG(KC_0),   LG(S(KC_0)),    LG(KC_3),   _______,    _______,                            LC(KC_INS),     KC_KP_EQUAL,    KC_KP_0,    KC_KP_0,    KC_KP_DOT,  _______,        TG(L_QWERTY),
          _______,  _______,    _______,    _______,        _______,                                                                                    _______,    _______,    _______,    LG(S(KC_LEFT)), LG(S(KC_RIGHT)),
                                                                                    XXXXXXX,    _______,    KC_HOME,    KC_END,
                                                                                                _______,    KC_PGUP,
                                                                        _______,    _______,    _______,    KC_PGDOWN,  KC_SPACE,   _______
    ),

    [L_GAME_SC] = LAYOUT_ergodox_pretty(
        KC_2,           KC_4,       KC_5,       KC_6,       XXXXXXX,    XXXXXXX,    KC_LBRC,                            KC_LBRC,    KC_F1,      KC_F2,      KC_F4,      KC_F11,     KC_F12,     KC_BSPC,
        KC_1,           KC_HOME,    KC_Q,       KC_W,       KC_E,       KC_SPACE,   _______,                            KC_TAB,     XXXXXXX,    XXXXXXX,    XXXXXXX,    RSFT(KC_Y), RSFT(KC_U), KC_BTN5,
        KC_LEAD,        KC_END,     KC_A,       KC_S,       KC_D,       KC_LCTRL,                                                   KC_KP_4,    XXXXXXX,    XXXXXXX,    KC_Y,       KC_U,       XXXXXXX,
        KC_LSHIFT,      KC_INS,     KC_C,       KC_N,       XXXXXXX,    KC_X,       KC_KP_PLUS,                         XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_V,
          KC_LCTRL,     KC_LALT,    KC_F6,      KC_F7,      KC_F8,                                                                              KC_BTN3,    KC_BTN2,    XXXXXXX,    KC_U,       KC_Y,
                                                                                    _______,    _______,    KC_LEFT,    KC_RIGHT,
                                                                                                _______,    KC_I,
                                                                        KC_G,       KC_ENTER,   KC_H,       KC_O,       KC_P,       KC_T
    ),

    // [L_GAME_SC2] = LAYOUT_ergodox_pretty(
    //     KC_Y,       _______,    _______,    _______,    _______,    _______,    _______,                                KC_RBRC,    KC_F1,      KC_F2,      KC_F4,      KC_F11,     KC_F12,     KC_BSPC,
    //     KC_U,       _______,    _______,    _______,    _______,    _______,    _______,                                KC_TAB,     XXXXXXX,    XXXXXXX,    XXXXXXX,    RSFT(KC_Y), RSFT(KC_U), KC_BTN5,
    //     _______,    _______,    _______,    _______,    _______,    _______,                                                        KC_KP_4,    XXXXXXX,    XXXXXXX,    KC_Y,       KC_U,       XXXXXXX,
    //     _______,    _______,    _______,    _______,    _______,    _______,    _______,                                XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_V,
    //       _______,   _______,    _______,    _______,    _______,                                                                                KC_BTN3,    KC_BTN2,    XXXXXXX,    KC_U,       KC_Y,
    //                                                                             XXXXXXX,    _______,        KC_LEFT,    KC_RIGHT,
    //                                                                                         _______,        KC_I,
    //                                                                 KC_T,       _______,    _______,        KC_O,       KC_P,       KC_T
    // ),

    [L_GAME_2] = LAYOUT_ergodox_pretty(
        _______,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_LBRC,                                KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     _______,
        _______,    _______,    KC_Q,       KC_W,       KC_E,       KC_SPACE,   KC_G,                                   _______,    _______,    KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_PAST,    KC_PSLS,
        _______,    _______,    KC_A,       KC_S,       KC_D,       KC_F,                                                           _______,    KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_EQUAL,   KC_KP_MINUS,
        _______,    _______,    _______,    _______,    _______,    KC_LCTRL,   _______,                                _______,    _______,    KC_KP_1,    KC_KP_2,    KC_KP_3,    _______,    KC_RSHIFT,
          _______,  _______,    _______,    _______,    _______,                                                                                _______,    KC_KP_0,    KC_KP_DOT,  _______,    _______,
                                                                                TG(L_KEYS), _______,        _______,    _______,
                                                                                            _______,        _______,
                                                                    _______,    _______,    _______,        _______,    _______,    _______
    ),

    [L_QWERTY] = LAYOUT_ergodox_pretty(
        KC_EQL,     KC_1,           KC_2,           KC_3,       KC_4,       KC_5,   KC_LEFT,                                    KC_RGHT,        KC_6,   KC_7,   KC_8,       KC_9,       KC_0,               KC_BSPC,
        KC_DELT,    KC_Q,           KC_W,           KC_E,       KC_R,       KC_T,   XXXXXXX,                                    TG(L_QWERTY),   KC_Y,   KC_U,   KC_I,       KC_O,       KC_P,               KC_BSLS,
        KC_BSPC,    KC_A,           KC_S,           KC_D,       KC_F,       KC_G,                                                               KC_H,   KC_J,   KC_K,       KC_L,       KC_SCLN,            KC_ENTER,
        KC_LSFT,    CTL_T(KC_Z),    KC_X,           KC_C,       KC_V,       KC_B,   ALL_T(KC_NO),                               MEH_T(KC_NO),   KC_N,   KC_M,   KC_COMM,    KC_DOT,     CTL_T(KC_SLSH),     KC_RSFT,
          KC_GRV,   KC_QUOT,        LALT(KC_LSFT),  KC_LEFT,    KC_RGHT,                                                                                KC_UP,  KC_DOWN,    KC_LBRC,    KC_RBRC,            KC_FN1,
                                                                                    ALL_T(KC_APP),  KC_LGUI,        KC_LALT,    CTL_T(KC_ESC),
                                                                                                    _______,        KC_PGUP,
                                                                        KC_SPC,     KC_BSPC,        _______,        KC_PGDN,    KC_TAB,         KC_ENT
    ),
};



// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     // dynamically generate these.
//     case EPRM:
//       if (record->event.pressed) {
//         eeconfig_init();
//       }
//       return false;
//       break;
//     case RGB_SLD:
//       if (record->event.pressed) {
//         rgblight_mode(1);
//       }
//       return false;
//       break;
//   }
//   return true;
// }

extern bool leading;
extern uint16_t leader_time;
extern uint16_t leader_sequence[5];
extern uint8_t leader_sequence_size;


void matrix_scan_user(void) {
    if (leading && timer_elapsed(leader_time) > LEADER_TIMEOUT) {
        leading = false;

        switch (leader_sequence[0]) {
        case KC_M: {
            register_code(KC_LGUI);
            register_code(KC_LCTRL);
            switch (leader_sequence[1]) {
                case KC_L: {
                    register_code(KC_KP_0);
                    unregister_code(KC_KP_0);
                    break;
                }
                default: {
                    unregister_code(KC_LCTRL);
                    unregister_code(KC_LGUI);
                    SEND_STRING("Move Missing Direction!");
                    break;
                }
            }
            unregister_code(KC_LCTRL);
            unregister_code(KC_LGUI);
            break;
        }
        case KC_L: {
            switch (leader_sequence[1]) {
                case KC_BSPC: {
                    layer_move(L_DFLT);
                    break;
                }
                case KC_G: {
                    layer_invert(L_GAME_SC);
                    break;
                }
            }
        }
        }

        leader_end();
    }
}

void matrix_init_user(void) { // Runs boot tasks for keyboard
    //set the layer color at initalization, because it won't set otherwise
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_BREATHING);
    rgblight_sethsv(HSV_RED);
}

// void oneshot_layer_changed_user(uint8_t layer) {
//     SEND_STRING("OSL CALLED!");

// }

uint32_t layer_state_set_user(uint32_t state) {
    LAYER_T layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case L_DFLT: {
            rgblight_mode(RGBLIGHT_MODE_BREATHING);
            rgblight_sethsv_noeeprom(HSV_RED);
            // rgblight_setrgb(0xFF, 0x00, 0x00);
            break;
        }

        case L_NAV: {
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(HSV_GREEN);
            // ergodox_right_led_3_on();
            break;
        }
        case L_NAV_S: {
            break;
        }

        case L_KEYS: {
            rgblight_mode(RGBLIGHT_MODE_BREATHING);
            rgblight_sethsv_noeeprom(HSV_MAGENTA);
            // ergodox_right_led_3_on();
            break;
        }

        case L_GAME_SC: {
            rgblight_mode(RGBLIGHT_MODE_SNAKE + 2);
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            // ergodox_right_led_2_on();
            break;
        }

        // case L_GAME_SC2: {
        //     rgblight_mode(RGBLIGHT_MODE_SNAKE + 2);
        //     rgblight_sethsv_noeeprom(HSV_BLUE_LIGHT);
        //     // ergodox_right_led_2_on();
        //     break;
        // }

        case L_GAME_2: {
            rgblight_mode(RGBLIGHT_MODE_BREATHING + 2);
            rgblight_sethsv_noeeprom(HSV_BLUE);
            // ergodox_right_led_2_on();
            break;
        }

        case L_QWERTY: {
            rgblight_mode(RGBLIGHT_MODE_KNIGHT + 2);
            rgblight_sethsv_noeeprom(0xFF, 0xC0, 0xFF);
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        }

        default: {
            break;
        }
    }
    return state;
};
