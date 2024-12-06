#include QMK_KEYBOARD_H

#define ALPHA 0
#define EDITOR 1
#define NAVIGATION 2
#define NUM 3

enum custom_keycodes {
    // Window management
    QUIT = SAFE_RANGE,  // close current window
    ALT_TAB,
    WKSP_LEFT,          // go left 1 workspace
    WKSP_RGHT,          // go right 1 workspace
    WKSP_MLFT,          // move window left 1 worksapce
    WKSP_MRGT,          // move window right 1 worksapce

    // Firefox shortcuts
    FF_LEFT,
    FF_RGHT,
    FF_NTAB,
    FF_CTAB,

    // Launchers
    NEOVIM,
    TERMINAL,
    BROWSER,
    NOTES,

    // Custom functionalities
    PASSWD,
    FLAG,

    // System
    SWITCH_KB
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[ALPHA] = LAYOUT( // alpha layer
                   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
                   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,
     MT(MOD_LSFT, KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, MT(MOD_RSFT, KC_SLSH),
                  LT(EDITOR, KC_ESC),  MT(MOD_LALT, KC_SPC), MT(MOD_RCTL, KC_ENT), LT(NAVIGATION, KC_BSPC)
    ),
    [EDITOR] = LAYOUT(
     KC_TAB, QK_BOOT,  PASSWD,    FLAG, _______,  KC_DEL, _______, _______, KC_LPRN, KC_RPRN,
     KC_ESC, KC_BSLS,  KC_GRV, KC_QUOT, _______, KC_BSPC, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC,
    KC_LSFT, _______, _______, MO(NUM), _______,  KC_ENT,  KC_ESC,  KC_DEL, KC_BSPC,  KC_ENT,
                               _______, _______,  KC_ENT, KC_BSPC
    ),
    [NUM] = LAYOUT(
     KC_NUM,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,    KC_7,   KC_8,   KC_9, _______,
    _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,    KC_4,   KC_5,   KC_6, _______,
    _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,    KC_1,   KC_2,   KC_3, _______,
                               _______, _______, _______,    KC_0
    ),
    [NAVIGATION] = LAYOUT(
         QUIT,   KC_LWIN,   KC_MPRV,   KC_MNXT,           KC_MPLY, FF_NTAB, FF_LEFT, MS_WHLD, MS_WHLU, FF_RGHT,
    WKSP_MLFT, WKSP_MRGT, WKSP_LEFT, WKSP_RGHT,   KC_KB_VOLUME_UP, ALT_TAB, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,
        NOTES,   BROWSER,  TERMINAL,    NEOVIM, KC_KB_VOLUME_DOWN, FF_CTAB, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
                                     SWITCH_KB,  _______, _______, _______
    )
};
// clang-format on

// Send alt-shift-keycode
void alt_shift(uint16_t keycode, bool pressed) {
    if (pressed) {
        register_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT));
        tap_code(keycode);
        unregister_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT));
    }
}

// Send win-shift-keycode
void win_shift(uint16_t keycode, bool pressed) {
    if (pressed) {
        register_mods(MOD_BIT(KC_LWIN) | MOD_BIT(KC_LSFT));
        tap_code(keycode);
        unregister_mods(MOD_BIT(KC_LWIN) | MOD_BIT(KC_LSFT));
    }
}

// Send alt-keycode
void alt(uint16_t keycode, bool pressed) {
    if (pressed) {
        register_mods(MOD_BIT(KC_LALT));
        tap_code(keycode);
        unregister_mods(MOD_BIT(KC_LALT));
    }
}

// Send shift-keycode
void shift(uint16_t keycode, bool pressed) {
    if (pressed) {
        register_mods(MOD_BIT(KC_LSFT));
        tap_code(keycode);
        unregister_mods(MOD_BIT(KC_LSFT));
    }
}

// Send control-keycode
void ctrl(uint16_t keycode, bool pressed) {
    if (pressed) {
        register_mods(MOD_BIT(KC_LCTL));
        tap_code(keycode);
        unregister_mods(MOD_BIT(KC_LCTL));
    }
}

// Send control-shift-keycode
void ctrl_shift(uint16_t keycode, bool pressed) {
    if (pressed) {
        register_mods(MOD_BIT(KC_LCTL));
        register_mods(MOD_BIT(KC_LSFT));
        tap_code(keycode);
        unregister_mods(MOD_BIT(KC_LSFT));
        unregister_mods(MOD_BIT(KC_LCTL));
    }
}

bool is_alt_tabbing = false;

bool is_recording = false;
char recorded_text[256] = "";
uint8_t recorded_length = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool p = record->event.pressed;
    if (is_alt_tabbing && p) {
        if (keycode != ALT_TAB && keycode != KC_I && keycode != KC_O) {
            unregister_mods(MOD_BIT(KC_LALT));
            is_alt_tabbing = false;
            return false;
        }
        else {
            if (keycode == KC_O)
                shift(KC_ESC, p);
            else
                tap_code(KC_ESC);
            return false;
        }
    }
    switch (keycode) {
        // System-level shortcuts
        case QUIT:
            alt_shift(KC_Q, p);
            return false;
        case ALT_TAB:
            if (p) {
                if (is_alt_tabbing) {
                    tap_code(KC_ESC);
                } else {
                    register_mods(MOD_BIT(KC_LALT));
                    is_alt_tabbing = true;
                    tap_code(KC_ESC);
                }
            }
            return false;
        case KC_SPC:
            if (is_alt_tabbing) {
                if (p) {
                    tap_code(KC_ESC);
                }
                return false;
            }
            return true;
        case WKSP_RGHT:
            alt_shift(KC_RGHT, p);
            return false;
        case WKSP_LEFT:
            alt_shift(KC_LEFT, p);
            return false;
        case WKSP_MRGT:
            win_shift(KC_RGHT, p);
            return false;
        case WKSP_MLFT:
            win_shift(KC_LEFT, p);
            return false;

        // Firefox shortcuts
        case FF_RGHT:
            ctrl(KC_TAB, p);
            return false;
        case FF_LEFT:
            ctrl_shift(KC_TAB, p);
            return false;
        case FF_NTAB:
            ctrl(KC_T, p);
            return false;
        case FF_CTAB:
            ctrl(KC_W, p);
            return false;

        // Launchers
        case NEOVIM:
            alt(KC_N, p);
            return false;
        case TERMINAL:
            alt(KC_ENT, p);
            return false;
        case BROWSER:
            alt(KC_B, p);
            return false;
        case NOTES:
            alt(KC_K, p);
            return false;

        // System Controls
        case PASSWD:
            if (p) {
                SEND_STRING("Uplink@Deploy2023\n");
                // if (is_recording) {
                //     is_recording = false;
                // }
                // else {
                //     strcpy(recorded_text, "");
                //     recorded_length = 0;
                //     is_recording = true;
                // }
                // return false;
            }
            return false;
        case FLAG:
            if (p) {
                SEND_STRING("inst.ks=http://192.168.1.250:8000/ks.cfg");
                // is_recording = false;
                // for (int i = 0; i < recorded_length; i++) {
                //     tap_code(recorded_text[i]);
                // }
            }
            return false;


    }
    if (is_recording && p) {
        recorded_text[recorded_length] = keycode;
        recorded_length++;
    }
    return true; // Process other keys normally
}

/*
    [x] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______
    )
*/

/*
// All QMK Keycodes (Aliases Only)
const uint16_t PROGMEM keycodes[] = {
    // Letters and Numbers
    KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T, KC_U, KC_V, KC_W, KC_X, KC_Y, KC_Z,
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,

    // Function Keys
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,

    // Punctuation
    KC_ENT, KC_ESC, KC_BSPC, KC_TAB, KC_SPC, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_NUHS, KC_SCLN, KC_QUOT, KC_GRV, KC_COMM, KC_DOT, KC_SLSH, KC_NUBS,

    // Lock Keys
    KC_CAPS, KC_SCRL, KC_NUM, KC_LCAP, KC_LNUM, KC_LSCR,

    // Modifiers
    KC_LCTL, KC_LSFT, KC_LALT, KC_LOPT, KC_LGUI, KC_LCMD, KC_LWIN, KC_RCTL, KC_RSFT, KC_RALT, KC_ROPT, KC_ALGR, KC_RGUI, KC_RCMD, KC_RWIN,

    // International
    KC_INT1, KC_INT2, KC_INT3, KC_INT4, KC_INT5, KC_INT6, KC_INT7, KC_INT8, KC_INT9,
    KC_LNG1, KC_LNG2, KC_LNG3, KC_LNG4, KC_LNG5, KC_LNG6, KC_LNG7, KC_LNG8, KC_LNG9,

    // Commands
    KC_PSCR, KC_PAUS, KC_INS, KC_HOME, KC_PGUP, KC_DEL, KC_END, KC_PGDN, KC_RGHT, KC_LEFT, KC_DOWN, KC_UP, KC_APP, KC_PWR, KC_EXEC, KC_HELP, KC_MENU, KC_SLCT, KC_STOP, KC_AGIN, KC_UNDO, KC_CUT, KC_COPY, KC_PSTE, KC_FIND,
    KC_MUTE, KC_VOLU, KC_VOLD, KC_ERAS, KC_SYRQ, KC_CNCL, KC_CLR, KC_PRIR, KC_RETN, KC_SEPR, KC_OUT, KC_OPER, KC_CLAG, KC_CRSL, KC_EXSL,

    // Media Keys
    KC_PWR, KC_SLEP, KC_WAKE, KC_MUTE, KC_VOLU, KC_VOLD, KC_MNXT, KC_MPRV, KC_MSTP, KC_MPLY, KC_MSEL, KC_EJCT, KC_WSCH, KC_WHOM, KC_WBAK, KC_WFWD, KC_WSTP, KC_WREF, KC_WFAV, KC_MFFD, KC_MRWD, KC_BRIU, KC_BRID, KC_CPNL, KC_ASST, KC_MCTL, KC_LPAD,

    // Number Pad
    KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, KC_PENT, KC_P1, KC_P2, KC_P3, KC_P4, KC_P5, KC_P6, KC_P7, KC_P8, KC_P9, KC_P0, KC_PDOT, KC_PEQL, KC_PCMM,

    // Special Keys
    XXXXXXX, KC_TRNS, _______
};
*/
