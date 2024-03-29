#include QMK_KEYBOARD_H
#include "wheredoesyourmindgo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_grid(
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ENT),
        MUTE_LP_HIDE, KC_LCTL, KC_LALT, KC_LGUI, MO(NUMNAV), LT(AUX,KC_SPC), LT(HRDWR,KC_SPC), MO(SYMBL), RGUI_T(KC_LEFT), RALT_T(KC_DOWN), RCTL_T(KC_UP), KC_RIGHT
    ),
	[NUMNAV] = LAYOUT_grid(
        KC_TAB , KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8 , KC_9, KC_0, KC_BSPC,
        KC_ESC, XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, LLOCK, DOT_LP, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_QUOT,
        KC_LSFT, UNDO, CUT, COPY, PASTE, REDO, KC_CAPS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_ENT,
        MUTE_LP_HIDE, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_SPC, KC_SPC, MO(SYMBL), KC_NO, XOSM_RALT, KC_NO, KC_NO
    ),
	[SYMBL] = LAYOUT_grid(
        KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_ESC, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL, KC_GRV, LLOCK, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_QUOT,
        KC_LSFT, KC_LCBR, KC_RCBR, KC_UNDS, KC_PLUS, KC_TILDE, KC_NO, KC_PIPE, KC_BSLS, KC_NO, KC_NO, KC_ENT,
        MUTE_LP_HIDE, KC_NO, XOSM_RALT, KC_NO, MO(NUMNAV), KC_SPC, KC_SPC, KC_NO, KC_RGUI, KC_RALT, KC_RCTL, KC_NO
    ),
	[AUX] = LAYOUT_grid(
        KC_TAB, KC_PSCR, KC_SLCK, KC_PAUS, KC_INS, TGL_SELECT_LP, KC_APP, OS_PRV_TAB, OS_PRV_APP_WNDW, OS_NXT_APP_WNDW, OS_NXT_TAB, KC_BSPC,
        KC_ESC, XOSM_LCTL, XOSM_LALT, XOSM_LGUI, XOSM_LSFT, LLOCK, WNDW_LP_MAX, WNDW_LP_CNTR, WNDW_LP_SMLR, WNDW_LP_LGR, WNDW_LP_RST, KC_QUOT,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ENT,
        MUTE_LP_HIDE, KC_LCTL, KC_LALT, KC_LGUI, MO(NUMNAV), KC_SPC, LT(HRDWR,KC_SPC), MO(SYMBL), KC_NO, XOSM_RALT, KC_NO, KC_NO
    ),
    [HRDWR] = LAYOUT_grid(
        KC_TAB, KC_NO, DISP_DIM, DISP_BRI, OS_DRKMD_TGL, KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_BSPC,
        KC_ESC, KC_NO, KC_VOLD, KC_VOLU, KC_MUTE, KC_NO, LLOCK, XOSM_LSFT, XOSM_LGUI, XOSM_LALT, XOSM_LCTL, KC_QUOT,
        KC_LSFT, KC_NO, KC_MRWD, KC_MFFD, KC_MPLY, KC_NO, KC_NO, KC_NO, KC_NO, DEBUG, RESET, KC_ENT,
        MUTE_LP_HIDE, KC_NO, XOSM_RALT, KC_NO, MO(NUMNAV), LT(AUX,KC_SPC), KC_SPC, MO(SYMBL), KC_RGUI, KC_RALT, KC_RCTL, KC_NO

    ),
	[FUNC] = LAYOUT_grid(
        KC_TAB, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, OS_BSPC,
        KC_ESC, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_ENT,
        KC_LSFT, KC_F21, KC_F22, KC_F23, KC_F24, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RSFT_T(KC_ENT),
        KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_RGUI, KC_RALT, KC_RCTL, KC_NO
    ),
    // [NUMPAD] = LAYOUT_grid(
    //     KC_TAB, KC_ASTR, KC_7, KC_8, KC_9, KC_SLSH,  KC_NO,      KC_NO,      KC_NO,      KC_LPRN, KC_RPRN, KC_BSPC,
    //     KC_ESC, KC_PLUS, KC_4, KC_5, KC_6, KC_MINS,  LLOCK,      XOSM_LSFT,  XOSM_LGUI,  XOSM_LALT, XOSM_LCTL, KC_QUOT,
    //     KC_NO, KC_0,    KC_1, KC_2, KC_3, KC_EQL,   KC_CIRC,    KC_DLR,     KC_PERC,    KC_COMM, KC_DOT, RSFT_T(KC_ENT),
    //     MUTE_LP_HIDE, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_SPC, KC_SPC, KC_NO, KC_RGUI, KC_RALT, KC_RCTL, LLOCK
    // ),
	[OS] = LAYOUT_grid(
        KC_TAB, KC_NO, KC_NO, OS_TRM_VSR, OS_LNCHR, KC_NO, OS_SPTLGHT_FNDR, OS_SPTLGHT, OS_LNCHPD, OS_SIRI, OS_SDBR, OS_BSPC,
        KC_ESC, PRV_APP, CMD_TAB_PRV, CMD_TAB_NXT, OS_EXPOSE, OS_DOCK, OS_FLLSCRN, OS_MSN_CNTRL, OS_PRV_SPC, OS_NXT_SPC, OS_DSKTP, KC_NO,
        KC_LSFT, KC_NO, LGUI(KC_Q), LGUI(KC_H), KC_NO, KC_NO, OS_SCRN_SHT_OPT, OS_SCRN_SHT_SLCT, OS_SCRN_SHT, OS_SCRN_SHT_CLP_SLCT, OS_SCRN_SHT_CLP, RSFT_T(KC_ENT),
        KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_RGUI, KC_RALT, KC_RCTL, KC_NO
    )
};

