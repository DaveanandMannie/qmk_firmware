// Copyright 2022 Cole Smith <cole@boadsource.xyz>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
enum layers {
    _BASE,
    _FIRST,
    _SECOND,
    _THIRD
};

#define SPD_BASE 25
#define SPD_FIRST 76
#define SPD_SECOND 120
#define SPD_THIRD 160
#define SPD_SHFT 40

// change mod row colours based on active layer
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);

    switch (layer) {
        case _BASE:
            rgb_matrix_set_speed(SPD_BASE);
            break;
        case _FIRST:
            rgb_matrix_set_speed(SPD_FIRST);

            break;
        case _SECOND:
            rgb_matrix_set_speed(SPD_SECOND);
            break;
        case _THIRD:
            rgb_matrix_set_speed(SPD_THIRD);
            break;
        default:
            rgb_matrix_set_speed(SPD_BASE);
            break;
    }

    return state;
}

// change mod row when osm shf is on
void oneshot_mods_changed_user(uint8_t mods) {
    // Check if Shift is active
    if (mods & MOD_MASK_SHIFT) {
        rgb_matrix_set_speed(SPD_SHFT);
    } else {
        rgb_matrix_set_speed(SPD_BASE);
    }
}

// change mod row when osm toggle shf is on
void oneshot_locked_mods_changed_user(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) {
        rgb_matrix_set_speed(SPD_SHFT);
    } else {
        rgb_matrix_set_speed(SPD_BASE);
    }
}



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | BackSP|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Escape|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  mo 3 |    | tg l2 |------+------+------+------+------+------|
 * |OSM-sft|   Z |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |OSM-sft|
 * `-----------------------------------------/ osl   /     \      \-----------------------------------------'
 *                   |  Win | Lctrl| L-alt| / first /       \space \  |Enter |R-ctrl| Ralt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_BASE] = LAYOUT(
  KC_BSPC,       KC_1, KC_2, KC_3, KC_4, KC_5,                         KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS,
  KC_TAB,        KC_Q, KC_W, KC_E, KC_R, KC_T,                         KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_EQL,
  KC_ESC,        KC_A, KC_S, KC_D, KC_F, KC_G,                         KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B, MO(_THIRD),      TG(_SECOND),  KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,OSM(MOD_RSFT),
                KC_LWIN, KC_LCTL, KC_LALT, OSL(_FIRST),       KC_SPC,   KC_ENT, KC_RCTL, KC_RALT
),
/* FIRST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   \  |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |  +   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |  del |-------.    ,-------| left | down |  up  | right|   `  |   _  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_FIRST] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3, KC_F4,   KC_F5,  KC_F6,                             KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_BSLS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
  _______, _______, _______, _______, _______,  KC_DEL,                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_GRV,  KC_UNDS,
  _______, _______, _______, _______, _______, _______, _______,      _______, KC_PIPE, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______,
                             _______, _______, _______, _______,      _______,  _______, _______, _______
),
/* SECOND
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |  S+  |  S-  |  B+  |  B-  |                    |nkrotg|      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | prvs | msup | next | mwup |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | mslt | msdn |msrght| mwdn |-------.    ,-------| wback| copy | paste| wfwd |      |      |
 * |------+------+------+------+------+------|RGB_TOG|    |       |------+------+------+------+------+------|
 * |      |      | vold | mute | volu | play |-------|    |-------|      |      |      | acl2 | acl0 |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \Enter \  |mbtn1 |mbtn2 |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_SECOND] = LAYOUT(
  KC_NO,  KC_NO, RGB_SAI, RGB_SAD, RGB_VAI,  RGB_VAD,                       NK_TOGG, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_NO,  KC_NO, KC_MPRV, MS_UP,   KC_MNXT,  MS_WHLU,                       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______,
  KC_NO,  KC_NO, MS_LEFT, MS_DOWN, MS_RGHT,  MS_WHLD,                       KC_WBAK, KC_COPY, KC_PSTE, KC_WFWD, KC_NO,   XXXXXXX,
  _______, KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_MPLY, RGB_TOG,     _______, KC_NO,   KC_NO,   KC_NO,   MS_ACL2, MS_ACL0, _______,
                       _______, _______, _______,  _______,        _______, MS_BTN1, MS_BTN2, _______
),
/* THIRD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |   7  |  8   |  9   |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|  4   |  5   |  6   |      |      |      |
 * |------+------+------+------+------+------|       |    |   0   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   1  |  2   |   3  |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_THIRD] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_7, KC_8, KC_9, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_4, KC_5, KC_6, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_0, KC_1, KC_2, KC_3, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

