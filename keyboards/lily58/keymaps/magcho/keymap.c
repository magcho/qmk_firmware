#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef SSD1306OLED
#include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _NUMBER 4

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    SUSHI,
    ADOBE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    /* QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BSPACE|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |BSPACE|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------|CSLOCK |    |NUMBER |------+------+------+------+------+------|
     * | LAlt |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   |Lshift| LGUI |LOWER | /Space  /       \Enter \  |RAISE | RGUI | RAlt |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */

    [_QWERTY] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, SUSHI,\
											 KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,\
											 KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,\
											 KC_LALT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_CAPS, TG(_NUMBER), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, \
											 KC_LSFT, KC_LGUI, LOWER, KC_SPC, KC_ENT, RAISE, KC_RGUI, KC_RALT),
    /* LOWER
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | ESC  |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
     * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE | RGUI | RAlt |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */
    [_LOWER] = LAYOUT(KC_ESC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
											_______,KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, \
											KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,\
											_______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,\
											_______, _______, _______, _______, _______, _______, _______, _______),
    /* RAISE
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | ESC  |      |      |      |      |      |                    |      |      |      |      |      | F19  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |   `  |      |      |      |      |      |                    |      |      |  Up  |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |Right |      |      |
     * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
     * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE | RGUI | RAlt |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------s'
     */
  	[_RAISE] = LAYOUT(KC_ESC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F19, \
											KC_GRV, _______, _______, _______, _______, _______, _______, _______, KC_UP, _______, _______, _______,\
											KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, _______, XXXXXXX,	\
											KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, KC_PLUS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,\
											_______, _______, _______, _______, _______, _______, _______, _______),
    /* ADJUST
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |ADOBE |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */
    [_ADJUST] = LAYOUT(XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
					   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
					   XXXXXXX, ADOBE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
					   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, \
					   _______, _______, _______, _______, _______, _______, _______, _______),

		/* NUMBER
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |      |   7  |   8  |   9  |BSPACE|      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------.    ,-------|   =  |   4  |   5  |   6  |   +  |      |
     * |------+------+------+------+------+------|       |    |NUMBER |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|   0  |   1  |   2  |   3  |   -  |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
		 */
		[_NUMBER] = LAYOUT(_______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,\
											 _______, _______, _______, _______, _______, _______,                   KC_PDOT, KC_P7,   KC_P8,   KC_P9,   KC_BSPC, _______,\
											 _______, _______, _______, _______, _______, _______,                   KC_PEQL, KC_P4,   KC_P5,    KC_P6,  KC_PPLS, _______,\
											 _______, _______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PMNS, _______,\
											 KC_LSFT, KC_LGUI, LOWER, KC_SPC, KC_ENT, RAISE, KC_RGUI, KC_RALT)
};

// clang-format on
int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
        layer_on(layer3);
    } else {
        layer_off(layer3);
    }
}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
}

// SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master())
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
    if (is_keyboard_master()) {
        // If you want to change the display of OLED, you need to change here
        oled_write_ln(read_layer_state(), false);
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
        // oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
        // oled_write_ln(read_host_led_state(), false);
        // oled_write_ln(read_timelog(), false);
    } else {
        oled_write(read_logo(), false);
    }
}
#endif // OLED_DRIVER_ENABLE

// 英 かな用設定
static bool lower_pressed = false;
static bool raise_pressed = false;

// exceptionaly ctrl layer用設定
static bool ctrl_pressed = false;
static bool exceptionaly_ctrl_layer_pressed = false;

// 親指super meta用設定
static bool left_thumb_pressed = false;
static bool right_thumb_pressed = false;

// Number layerでupper/lowerした時の復帰用
static bool is_prelayer_numberlayer = false;

// プログラマブルな機能をすべてオフにするADOBE
static bool is_adobe_mode = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        set_keylog(keycode, record);
#endif
        // set_timelog();
    }

    if (keycode == ADOBE && record->event.pressed) {
        is_adobe_mode = !is_adobe_mode;
    }

    switch (keycode) {
    case KC_LCTRL:
        // exceptionaly ctrl layer用設定
        lower_pressed = raise_pressed = false;
        if (record->event.pressed) {
            ctrl_pressed = true;
        } else {
            ctrl_pressed = false;
        }
        break;

    case KC_SPC:
        if (is_adobe_mode) {
            return true;
        }
        // 親指super meta用設定
        if (record->event.pressed) {
            left_thumb_pressed = true;
            right_thumb_pressed = false;
            register_code(KC_LALT);
        } else {
            unregister_code(KC_LALT);
            if (left_thumb_pressed) {
                tap_code(KC_SPC);
            }
            left_thumb_pressed = false;
        }
        return false;

    case KC_ENT:
        if (is_adobe_mode) {
            return true;
        }
        // 親指super meta用設定
        if (record->event.pressed) {
            left_thumb_pressed = false;
            right_thumb_pressed = true;
            register_code(KC_LCTRL);
        } else {
            unregister_code(KC_LCTRL);
            if (right_thumb_pressed) {
                tap_code(KC_ENT);
            }
            right_thumb_pressed = false;
        }
        return false;

    case QWERTY:
        if (record->event.pressed) {
            // 英 かな用設定
            lower_pressed = raise_pressed = false;
            set_single_persistent_default_layer(_QWERTY);
        }
        return false;

    case LOWER:
        if (record->event.pressed) {
            lower_pressed = true;
            raise_pressed = false;

            is_prelayer_numberlayer = layer_state_is(_NUMBER);
            layer_off(_NUMBER);

            layer_on(_LOWER);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_LOWER);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);

            // 英 かな用設定
            if (lower_pressed) {
                tap_code(KC_LANG2);
            }
            lower_pressed = false;

            if (is_prelayer_numberlayer) {
                layer_on(_NUMBER);
            }
        }
        return false;

    case RAISE:
        if (record->event.pressed) {
            lower_pressed = false;
            raise_pressed = true;

            is_prelayer_numberlayer = layer_state_is(_NUMBER);
            layer_off(_NUMBER);

            layer_on(_RAISE);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_RAISE);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);

            // 英 かな用設定
            if (raise_pressed) {
                tap_code(KC_LANG1);
            }
            raise_pressed = false;

            if (is_prelayer_numberlayer) {
                layer_on(_NUMBER);
            }
        }
        return false;

    case ADJUST:
        if (record->event.pressed) {
            layer_on(_ADJUST);

            // 英 かな用設定
            lower_pressed = raise_pressed = false;

        } else {
            layer_off(_ADJUST);
        }
        return false;

    case SUSHI:
        if (record->event.pressed) {
            send_string(":sushi:");
        }
        return false;

    default:
        // 英 かな用設定
        lower_pressed = raise_pressed = false;

        // 親指super meta用設定
        left_thumb_pressed = right_thumb_pressed = false;

        // exceptionaly ctrl layer用設定
        if (ctrl_pressed || exceptionaly_ctrl_layer_pressed) {
            switch (keycode) {
            case KC_J:
                if (record->event.pressed) {
                    unregister_code(KC_LCTRL);
                    register_code(KC_BSPACE);
                    exceptionaly_ctrl_layer_pressed = true;
                } else {
                    unregister_code(KC_BSPACE);
                    if (ctrl_pressed) {
                        register_code(KC_LCTRL);
                    }
                    exceptionaly_ctrl_layer_pressed = false;
                }
                return false;

            case KC_N:
                if (record->event.pressed) {
                    unregister_code(KC_LCTRL);
                    register_code(KC_MINUS);
                    exceptionaly_ctrl_layer_pressed = true;
                } else {
                    unregister_code(KC_MINUS);
                    if (ctrl_pressed) {
                        register_code(KC_LCTRL);
                    }
                    exceptionaly_ctrl_layer_pressed = false;
                }
                return false;
            }
        }
    }
    return true;
}
