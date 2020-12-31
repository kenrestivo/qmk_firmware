#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE, // default layer
    SYMB, // symbols
    MDIA,  // me/* dia keys */
};

enum custom_keycodes {
#ifdef ORYX_CONFIGURATOR
  VRSN = EZ_SAFE_RANGE,
#else
  VRSN = SAFE_RANGE,
#endif
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL,   KC_1,    KC_2,    KC_3,     KC_4,     KC_5,  TG(MDIA),
        KC_DEL,   KC_Q,    KC_W,    KC_E,     KC_R,     KC_T,  LALT(KC_X), //  emacs meta
        KC_COPY,  KC_A,    KC_S,    KC_D,     KC_F,     KC_G,
        KC_LSHIFT,  KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,  KC_KP_1, //save
        KC_ESC,   KC_GRAVE, TG(SYMB),  KC_LEFT,  KC_RGHT,
                                               KC_LCTL, KC_LALT,
                                                       KC_HOME,
                                      	KC_SPC, KC_TAB, KC_END,
        // right hand
	KC_CUT,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,     KC_MINS,
	KC_PASTE,    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_BSLS,
                          KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,  KC_QUOT,
	KC_ENT, KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT,
	KC_UP,  KC_DOWN, KC_LBRC, KC_RBRC,  KC_CAPSLOCK, // this fucking thing keeps changing to lctrl and it is pissing me off
             KC_RALT, KC_RCTL,
             KC_PGUP,
	     KC_PGDN, KC_BSPC, KC_SPC
    ),
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_PGUP, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,
       KC_PGDN, _______, KC_MS_WH_UP,  _______, _______, _______, _______,
       _______, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_RIGHT, _______, _______,
       KC_TRNS, _______, _______, _______, _______, _______, LSFT(KC_INS), // x insert/paste
       _______, _______, KC_TRNS, _______, _______,
                                       _______, _______,
                                               _______,
                               _______, _______, _______,
       // right hand
       KC_WWW_HOME, KC_F6,     KC_F7,     KC_F8,      KC_F9,    KC_F10,  KC_F11,
       KC_MS_BTN1, _______, _______,   LALT(KC_UP),    _______,   _______, KC_F12,

                 LALT(KC_LEFT), LSA(KC_LEFT),   LALT(KC_DOWN),    LSA(KC_RIGHT),    LALT(KC_RIGHT), LCTL(KC_TAB),
       KC_TRNS, KC_MS_BTN2, LSA(KC_1),   LSA(KC_2), LSA(KC_3),    LSA(KC_3), KC_TRNS,
                         _______, _______,  _______,    _______,  KC_WWW_BACK,
       _______, _______,
       _______,
       _______, _______, _______
	),
[MDIA] = LAYOUT_ergodox(
       _______, _______, _______, _______, _______, _______, KC_TRNS,
       _______, _______, _______, _______, _______, _______, RESET,
       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, KC_MEDIA_NEXT_TRACK,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  _______, _______, _______, _______, _______, _______,
       _______,  _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, _______,
       _______,  _______, _______, _______, _______, _______, _______,
                          KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, KC_MEDIA_STOP, KC_MEDIA_PLAY_PAUSE, _______,
       _______, _______,
       _______,
       _______, _______, _______
),

	
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
   rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = get_highest_layer(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};

