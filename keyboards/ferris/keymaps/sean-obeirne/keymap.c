#include QMK_KEYBOARD_H

#define ALPHA 0
#define NUM 1
#define EDITOR 2
#define NAVIGATION 3
#define APPS 4
#define MOVEMENT 5
#define RS 6
#define SYS 7

enum custom_keycodes {
    // Window management
    QUIT = SAFE_RANGE,
    ALT_TAB,
    WKSP_1,
    WKSP_2,
    WKSP_3,
    WKSP_4,
    WKSP_5,
    WKSP_6,
    WKSP_7,
    WKSP_8,
    WKSP_9,
    WKSP_10,
    MWKSP_1,
    MWKSP_2,
    MWKSP_3,
    MWKSP_4,
    MWKSP_5,
    MWKSP_6,
    MWKSP_7,
    MWKSP_8,
    MWKSP_9,
    MWKSP_10,

    // Firefox shortcuts
    FF_LEFT,
    FF_RGHT,
    FF_NTAB,
    FF_CTAB,
    FF_RFSH,

    // Neovim shortcuts
    NVAUTOD,
    NVAUTOU,
    COPY,
    CUT,
    PASTE,

    // Launchers
    DMENU,
    NEOVIM,
    TERMINAL,
    BROWSER,
    NOTES,
    SPOTIFY,
    YTMUSIC,
    PAVUCTRL,
    EVINCE,
    OSRS,

    // Custom functionalities
    PASSWD,
    FLAG
};

/*** KEYMAPS ***/

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[ALPHA] = LAYOUT( // alpha layer
         LT(SYS, KC_Q),               KC_W,                 KC_E,             KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,                  KC_P,
        LT(APPS, KC_A), MT(MOD_LALT, KC_S),   MT(MOD_RCTL, KC_D),    LT(NUM, KC_F),    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,               KC_SCLN,
    MT(MOD_LSFT, KC_Z),               KC_X, LT(NAVIGATION, KC_C), LT(EDITOR, KC_V),    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, MT(MOD_RSFT, KC_SLSH),
                    LT(NAVIGATION, KC_ESC),               KC_SPC,           KC_ENT, KC_BSPC
    ),
    [EDITOR] = LAYOUT(
    KC_LSFT, QK_BOOT, _______, _______, _______, _______, NVAUTOD, NVAUTOU, KC_LPRN, KC_RPRN,
    KC_RSFT, KC_PSCR,    COPY, _______, _______, KC_QUOT, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC,
    KC_LSFT,     CUT,   PASTE, _______, _______, _______,  KC_TAB, KC_QUOT,  KC_GRV, KC_BSLS,
                               _______, _______, _______, KC_BSPC
    ),
    [NUM] = LAYOUT(
     KC_NUM,   KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_PAST,    KC_7,   KC_8,   KC_9, KC_PMNS,
    _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_PSLS,    KC_4,   KC_5,   KC_6, KC_PPLS,
    _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_PEQL,    KC_1,   KC_2,   KC_3,  KC_DOT,
                               _______, _______,  KC_ENT,    KC_0
    ),
    [APPS] = LAYOUT(
    _______, PAVUCTRL,  SPOTIFY, YTMUSIC,  EVINCE, _______, _______, _______, _______, _______,
    _______,  BROWSER, TERMINAL,  NEOVIM,    QUIT, _______, _______, _______, _______, _______,
    _______,     OSRS,  _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______
    ),
    [NAVIGATION] = LAYOUT(
           WKSP_5,  WKSP_6,   WKSP_7,  WKSP_8,  WKSP_9, FF_NTAB, FF_LEFT, MS_WHLD, MS_WHLU, FF_RGHT,
           WKSP_1,  WKSP_2,   WKSP_3,  WKSP_4, WKSP_10, FF_RFSH, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
    OSL(MOVEMENT), _______, _______, _______,  _______, FF_CTAB, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,
                                     _______,   TO(RS), _______, _______
    ),
    [MOVEMENT] = LAYOUT(
    MWKSP_5, MWKSP_6, MWKSP_7, MWKSP_8,  MWKSP_9, _______, _______, _______, _______, _______,
    MWKSP_1, MWKSP_2, MWKSP_3, MWKSP_4, MWKSP_10, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
                               _______,  _______, _______, _______
    ),
    [RS] = LAYOUT(
       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
      KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_LSFT, TO(ALPHA),    KC_4,    KC_5,    KC_6, _______,
      KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_F10,   _______,    KC_1,    KC_2,    KC_3, _______,
                                KC_ESC,  KC_SPC,   _______,    KC_0
    ),
    [SYS] = LAYOUT(
    _______, _______,  _______, _______, _______, FF_NTAB, FF_LEFT, MS_WHLD, MS_WHLU, FF_RGHT,
    _______, _______,  _______, _______, _______, KC_MPLY, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
       QUIT, BROWSER, TERMINAL,  NEOVIM,   DMENU, KC_MUTE, SPOTIFY, KC_BRIU, KC_BRID, YTMUSIC,
                                _______, TO(ALPHA), _______, _______
    )
};
// clang-format on

/*** END KEYMAPS ***/

/*
    [x] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______
    )
*/


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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool p = record->event.pressed;
    switch (keycode) {
        // System-level shortcuts
        case QUIT:
            alt_shift(KC_Q, p);
            return false;

        // Swirch Workspaces
        case WKSP_1: if (p) alt(KC_1, p); return false;
        case WKSP_2: if (p) alt(KC_2, p); return false;
        case WKSP_3: if (p) alt(KC_3, p); return false;
        case WKSP_4: if (p) alt(KC_4, p); return false;
        case WKSP_5: if (p) alt(KC_5, p); return false;
        case WKSP_6: if (p) alt(KC_6, p); return false;
        case WKSP_7: if (p) alt(KC_7, p); return false;
        case WKSP_8: if (p) alt(KC_8, p); return false;
        case WKSP_9: if (p) alt(KC_9, p); return false;
        case WKSP_10: if (p) alt(KC_0, p); return false;

        // Move Workspaces
        case MWKSP_1: if (p) alt_shift(KC_1, p); return false;
        case MWKSP_2: if (p) alt_shift(KC_2, p); return false;
        case MWKSP_3: if (p) alt_shift(KC_3, p); return false;
        case MWKSP_4: if (p) alt_shift(KC_4, p); return false;
        case MWKSP_5: if (p) alt_shift(KC_5, p); return false;
        case MWKSP_6: if (p) alt_shift(KC_6, p); return false;
        case MWKSP_7: if (p) alt_shift(KC_7, p); return false;
        case MWKSP_8: if (p) alt_shift(KC_8, p); return false;
        case MWKSP_9: if (p) alt_shift(KC_9, p); return false;
        case MWKSP_10: if (p) alt_shift(KC_0, p); return false;

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
        case FF_RFSH:
            ctrl(KC_R, p);
            return false;

        // Neovim shortcuts
        case NVAUTOD:
            alt(KC_DOWN, p);
            return false;
        case NVAUTOU:
            alt(KC_UP, p);
            return false;
        case COPY:
            ctrl(KC_C, p);
            return false;
        case CUT:
            ctrl(KC_X, p);
            return false;
        case PASTE:
            ctrl(KC_V, p);
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
        case DMENU:
            alt(KC_D, p);
            return false;
        case SPOTIFY:
            alt(KC_S, p);
            return false;
        case YTMUSIC:
            alt(KC_Y, p);
            return false;
        case PAVUCTRL:
            alt(KC_P, p);
            return false;
        case EVINCE:
            alt(KC_E, p);
            return false;
        case OSRS:
            alt_shift(KC_R, p);
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
    return true; // Process other keys normally
}

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
