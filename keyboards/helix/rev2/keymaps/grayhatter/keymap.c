#include "helix.h"
#include "bootloader.h"

#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum layer_number {
    L_DEFAULT,
    L_SYMS,
    L_I3KEYS,
};

#define LG LGUI
#define LGS( x ) LG(S( x ))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_DEFAULT] = LAYOUT( \
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                KC_6,    KC_7,     KC_8,    KC_9,    KC_0,   KC_DEL,
        KC_TAB,   KC_QUOT,  KC_COMM,  KC_DOT,   KC_P,     KC_Y,                                KC_F,    KC_G,     KC_C,    KC_R,    KC_L,   KC_BSPC,
        KC_LEAD,  KC_A,     KC_O,     KC_E,     KC_U,     KC_I,                                KC_D,    KC_H,     KC_T,    KC_N,    KC_S,   KC_ENT,
        KC_LSFT,  KC_SCLN,  KC_Q,     KC_J,     KC_K,     KC_X,     TG(L_I3KEYS),    KC_RBRC,  KC_B,    KC_M,     KC_W,    KC_V,    KC_Z,   KC_RSFT,
        KC_LCTL,  KC_LALT,  KC_GRV,   KC_LGUI,  _______,  KC_SPC,   KC_SPC,          KC_SPC,   KC_SPC,  _______,  KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT
    ),

    [L_SYMS] = LAYOUT( \
        _______, _______, _______, _______, RGB_TOG,  RGB_MOD,                        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, KC_HOME, KC_UP,   KC_END,   KC_PGUP,                        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,  KC_PGDN,                        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______, _______,  _______,  _______,    _______,  _______,  _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______, _______,  _______,  _______,    _______,  _______,  _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [L_I3KEYS] = LAYOUT( \
        _______,      _______,       _______,   _______,   RGB_TOG,  RGB_MOD,                        RGB_VAI,  RGB_VAD,  _______,  _______,  _______,   EEP_RST,
        LG(KC_1),     LG(KC_2),      LG(KC_3),  _______,   _______,  _______,                        RGB_SPI,  RGB_SPD,  _______,  _______,  _______,   _______,
        LG(KC_4),     LG(KC_5),      LG(KC_6),  _______,   _______,  _______,                        RGB_HUI,  RGB_HUD,  _______,  _______,  _______,   _______,
        LG(KC_0),     LGS(KC_0),     LG(KC_3),  _______,   _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,
        LG(KC_LEFT),  LG(KC_RIGHT),  _______,   _______,   _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______
    ),
};


#define LEDS_KEYPOS_L \
        {   5,  4,  3,  2,  1,  0, NO_LED, },   \
        {   6,  7,  8,  9, 10, 11, NO_LED, },   \
        {  17, 16, 15, 14, 13, 12, NO_LED, },   \
        {  18, 19, 20, 21, 22, 23,     24, },   \
        {  31, 30, 29, 28, 27, 26,     25, },   \
        {  37, 36, 35, 34, 33, 32, NO_LED, },   \
        {  38, 39, 40, 41, 42, 43, NO_LED, },   \
        {  49, 48, 47, 46, 45, 44, NO_LED, },   \
        {  50, 51, 52, 53, 54, 55,     56, },   \
        {  63, 62, 61, 60, 59, 58,     57, },

#define LEDS_KEYPOS_R \
        {     37, 36, 35, 34, 33, 32, NO_LED, },   \
        {     38, 39, 40, 41, 42, 43, NO_LED, },   \
        {     49, 48, 47, 46, 45, 44, NO_LED, },   \
        {     50, 51, 52, 53, 54, 55,     56, },   \
        {     63, 62, 61, 60, 59, 58,     57, },   \
        {      5,  4,  3,  2,  1,  0, NO_LED, },   \
        {      6,  7,  8,  9, 10, 11, NO_LED, },   \
        {     17, 16, 15, 14, 13, 12, NO_LED, },   \
        {     18, 19, 20, 21, 22, 23,     24, },   \
        {     31, 30, 29, 28, 27, 26,     25, },


#define LEDS_LEDPOS_L \
        {  86,   0 }, {  69,   0 }, {  52,   0 }, {  34,   0 }, {  17,   0 }, {   0,   0 },                 \
        {   0,  16 }, {  17,  16 }, {  34,  16 }, {  52,  16 }, {  69,  16 }, {  86,  16 },                 \
        {  86,  32 }, {  69,  32 }, {  52,  32 }, {  34,  32 }, {  17,  32 }, {   0,  32 },                 \
        {   0,  48 }, {  37,  48 }, {  34,  48 }, {  52,  48 }, {  69,  48 }, {  86,  48 }, { 103,  48 },   \
        { 103,  64 }, {  86,  64 }, {  69,  64 }, {  52,  64 }, {  34,  64 }, {  17,  64 }, {   0,  64 },   \
                      { 138,   0 }, { 155,   0 }, { 172,   0 }, { 190,   0 }, { 207,   0 }, { 224,   0 },   \
                      { 224,  16 }, { 207,  16 }, { 190,  16 }, { 172,  16 }, { 155,  16 }, { 138,  16 },   \
                      { 138,  32 }, { 155,  32 }, { 172,  32 }, { 190,  32 }, { 207,  32 }, { 224,  32 },   \
        { 224,  48 }, { 207,  48 }, { 190,  48 }, { 172,  48 }, { 155,  48 }, { 138,  48 }, { 121,  48 },   \
        { 121,  64 }, { 138,  64 }, { 155,  64 }, { 172,  64 }, { 190,  64 }, { 207,  64 }, { 224,  64 },

#define LEDS_LEDPOS_R \
                      { 138,   0 }, { 155,   0 }, { 172,   0 }, { 190,   0 }, { 207,   0 }, { 224,   0 },   \
                      { 224,  16 }, { 207,  16 }, { 190,  16 }, { 172,  16 }, { 155,  16 }, { 138,  16 },   \
                      { 138,  32 }, { 155,  32 }, { 172,  32 }, { 190,  32 }, { 207,  32 }, { 224,  32 },   \
        { 224,  48 }, { 207,  48 }, { 190,  48 }, { 172,  48 }, { 155,  48 }, { 138,  48 }, { 121,  48 },   \
        { 121,  64 }, { 138,  64 }, { 155,  64 }, { 172,  64 }, { 190,  64 }, { 207,  64 }, { 224,  64 },   \
        {  86,   0 }, {  69,   0 }, {  52,   0 }, {  34,   0 }, {  17,   0 }, {   0,   0 },                 \
        {   0,  16 }, {  17,  16 }, {  34,  16 }, {  52,  16 }, {  69,  16 }, {  86,  16 },                 \
        {  86,  32 }, {  69,  32 }, {  52,  32 }, {  34,  32 }, {  17,  32 }, {   0,  32 },                 \
        {   0,  48 }, {  37,  48 }, {  34,  48 }, {  52,  48 }, {  69,  48 }, {  86,  48 }, { 103,  48 },   \
        { 103,  64 }, {  86,  64 }, {  69,  64 }, {  52,  64 }, {  34,  64 }, {  17,  64 }, {   0,  64 },


led_config_t g_led_config = {
    { // Key Matrix to LED Index
      #ifdef HELIX_RIGHTBOARD
        LEDS_KEYPOS_L
      #else
        LEDS_KEYPOS_R
      #endif
    }, { // LED Index to Physical Position
      #ifdef HELIX_RIGHTBOARD
        LEDS_LEDPOS_R
      #else
        LEDS_LEDPOS_L
      #endif
    }, { // LED Index to Flag
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4,

           4, 4, 4, 4, 4, 4,
           4, 4, 4, 4, 4, 4,
           4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4,
    }
};


// define variables for reactive RGB
bool TOG_STATUS = false;

// typedef enum {
//     def = 0

// } RGB_MODE_T;


static void _kb_rgb_set(int mode)
{
    // rgb_matrix_enable();

    // rgb_matrix_set_color_all(0x00, 0xFF, 0x00);

    // rgb_matrix_disable();
    // rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
    // rgblight_setrgb(0xFF, 0x00, 0x00);
}

void rgb_matrix_indicators_user()
{
    rgb_matrix_set_color_all(0x04, 0x00, 0x00);

    rgb_matrix_set_color( 0, 0x00, 0x00, 0x04);
    rgb_matrix_set_color( 1, 0x00, 0x00, 0x04);
    rgb_matrix_set_color( 2, 0x00, 0x00, 0x04);
    rgb_matrix_set_color( 3, 0x00, 0x00, 0x04);
    rgb_matrix_set_color( 4, 0x00, 0x00, 0x04);

    rgb_matrix_set_color(16, 0xFF, 0x02, 0x02);
    rgb_matrix_set_color(15, 0xFF, 0x02, 0x02);
    rgb_matrix_set_color(14, 0xFF, 0x02, 0x02);
    rgb_matrix_set_color(13, 0xFF, 0x02, 0x02);

    rgb_matrix_set_color(40, 0x00, 0xFF, 0x00);
    rgb_matrix_set_color(41, 0x00, 0xFF, 0x00);
    rgb_matrix_set_color(42, 0x00, 0xFF, 0x00);

}

void matrix_init_user(void) { // Runs boot tasks for keyboard
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
    //set the layer color at initalization, because it won't set otherwise


    rgb_matrix_mode(0);
    _kb_rgb_set(0);
    // rgb_matrix_enable();
    // rgb_matrix_mode(RGB_MATRIX_SOLID_MULTISPLASH);
    // rgb_matrix_sethsv(HSV_RED);
}


uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
        case L_DEFAULT: {
            _kb_rgb_set(0);
            break;
        }

        case L_I3KEYS: {
            // rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR)u;
            // rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        }

        default: {
            break;
        }
    }
    return state;
};



//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif

