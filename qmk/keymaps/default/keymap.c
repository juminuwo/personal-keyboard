// Copyright 2024
// SPDX-License-Identifier: GPL-2.0-or-later
// Personal 33-key split keyboard - based on Sofle keymap

#include QMK_KEYBOARD_H

// Combos
enum combos {
    UI_DELETE,
    WE_BSPC,
    NM_ESC,
    CV_TAB,
    COMBO_COUNT
};

const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [UI_DELETE] = COMBO(ui_combo, KC_DELETE),
    [WE_BSPC] = COMBO(we_combo, KC_BSPC),
    [NM_ESC] = COMBO(nm_combo, KC_ESC),
    [CV_TAB] = COMBO(cv_combo, KC_TAB),
};

// Layers
enum layers {
    _QWERTY,
    _QWERTY_PLAIN,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// Custom keycodes
enum custom_keycodes {
    KC_PRVWD = QK_USER,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND
};

#define KC_QWERTY PDF(_QWERTY)
#define KC_QWERTY_PLAIN PDF(_QWERTY_PLAIN)

/*
 * 33-Key Layout
 *
 * Left Hand (17 keys)                    Right Hand (16 keys)
 *
 *      Q     W     E     R     T              Y     U     I     O
 *      A   ALT_S CTL_D SFT_F   G            SFT_H CTL_J ALT_K   L     P
 *    GUI_Z   X     C     V     B              N     M     ,   GUI_.   /
 *                    [LOWER] [ENTER]      [SPACE] [RAISE]
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * QWERTY - Base layer with home row mods
     */
    [_QWERTY] = LAYOUT(
        // Left hand (17 keys)
        KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,
        KC_A,         LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,
        LGUI_T(KC_Z), KC_X,         KC_C,         KC_V,         KC_B,
                                                  MO(_LOWER),   KC_ENT,
        // Right hand (16 keys)
        KC_Y,         KC_U,         KC_I,         KC_O,
        RSFT_T(KC_H), RCTL_T(KC_J), RALT_T(KC_K), KC_L,         KC_P,
        KC_N,         KC_M,         KC_COMM,      RGUI_T(KC_DOT), KC_SLSH,
        KC_SPC,       MO(_RAISE)
    ),

    /*
     * QWERTY_PLAIN - No home row mods
     */
    [_QWERTY_PLAIN] = LAYOUT(
        // Left hand
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                                   TL_LOWR, KC_ENT,
        // Right hand
        KC_Y,    KC_U,    KC_I,    KC_O,
        KC_H,    KC_J,    KC_K,    KC_L,    KC_P,
        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        KC_SPC,  TL_UPPR
    ),

    /*
     * LOWER - Numbers and symbols
     */
    [_LOWER] = LAYOUT(
        // Left hand
        KC_EXLM,      KC_AT,        KC_HASH,      KC_DLR,       KC_PERC,
        KC_1,         LALT_T(KC_2), LCTL_T(KC_3), LSFT_T(KC_4), KC_5,
        KC_EQL,       KC_MINS,      KC_PLUS,      KC_LCBR,      KC_RCBR,
                                                  _______,      _______,
        // Right hand
        KC_CIRC,      KC_AMPR,      KC_ASTR,      KC_LPRN,
        RSFT_T(KC_6), RCTL_T(KC_7), RALT_T(KC_8), KC_9,         KC_0,
        KC_LBRC,      KC_RBRC,      KC_SCLN,      KC_COLN,      KC_BSLS,
        _______,      _______
    ),

    /*
     * RAISE - Navigation and editing
     */
    [_RAISE] = LAYOUT(
        // Left hand
        KC_INS,  KC_PSCR, KC_APP,  XXXXXXX, XXXXXXX,
        KC_LALT, KC_LCTL, KC_BSPC, KC_DEL,  KC_CAPS,
        C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX,
                                   _______, _______,
        // Right hand
        XXXXXXX, XXXXXXX, XXXXXXX, KC_RPRN,
        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_GRV,
        XXXXXXX, KC_LSTRT,XXXXXXX, KC_LEND, KC_QUOT,
        _______, _______
    ),

    /*
     * ADJUST - Function keys and settings (LOWER + RAISE)
     */
    [_ADJUST] = LAYOUT(
        // Left hand
        KC_F1,      KC_F2,      KC_F3,   KC_F4,   KC_F5,
        KC_F11,     KC_F12,     XXXXXXX, XXXXXXX, XXXXXXX,
        KC_QWERTY,  KC_QWERTY_PLAIN, XXXXXXX, XXXXXXX, XXXXXXX,
                                         _______, _______,
        // Right hand
        KC_F6,   KC_F7,   KC_F8,   KC_F9,
        MS_WHLD, MS_WHLU, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_F10,  KC_F11,  XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______
    )
};

// Tri-layer: LOWER + RAISE = ADJUST
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// Custom keycode handling
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_PRVWD:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_LEFT);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_LEFT);
            }
            break;
        case KC_NXTWD:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_RIGHT);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_RIGHT);
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                register_code(KC_HOME);
            } else {
                unregister_code(KC_HOME);
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                register_code(KC_END);
            } else {
                unregister_code(KC_END);
            }
            break;
    }
    return true;
}
