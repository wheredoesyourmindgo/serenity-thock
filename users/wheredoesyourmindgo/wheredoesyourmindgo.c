#include "wheredoesyourmindgo.h"
#include "features/oneshot_mods.h"
#include "features/custom_shift_keys.h"
#include "features/custom_gui_keys.h"
#include "features/magic_shift.h"
#include "features/cmd_tab_switcher.h"
#include "features/symbol_rolls.h"
#include "features/layer_lock.h"

#ifdef CONSOLE_ENABLE
#  include "print.h"
#endif

// extern int retro_tapping_counter;

void tap_code16_no_mod(uint16_t code) {
  // Initialize variable holding the binary representation of active modifiers.
  uint8_t mod_state;
  uint8_t w_mod_state;
  uint8_t o_mod_state;
  // Store the current modifier state in the variable for later reference
  mod_state   = get_mods();
  w_mod_state = get_weak_mods();
  o_mod_state = get_oneshot_mods();
  // clear_oneshot_mods();
  if (mod_state || w_mod_state || o_mod_state) {
    // First temporarily canceling both shifts so that shift isn't applied to the keycode/shortcut
    del_mods(mod_state);
    del_weak_mods(w_mod_state);
    del_oneshot_mods(o_mod_state);
    send_keyboard_report();
    tap_code16(code);
    // Reapplying modifier state so that the held shift key(s) still work even after having sent the tap code.
    add_mods(mod_state);
    add_weak_mods(w_mod_state);
    set_oneshot_mods(o_mod_state);
    send_keyboard_report();
  } else {
    tap_code16(code);
  }
}

void tap_code_no_mod(uint8_t code) {
  // Initialize variable holding the binary representation of active modifiers.
  uint8_t mod_state;
  uint8_t w_mod_state;
  uint8_t o_mod_state;
  // Store the current modifier state in the variable for later reference
  mod_state   = get_mods();
  w_mod_state = get_weak_mods();
  o_mod_state = get_oneshot_mods();
  // clear_oneshot_mods();
  if (mod_state || w_mod_state || o_mod_state) {
    // First temporarily canceling both shifts so that shift isn't applied to the keycode/shortcut
    del_mods(mod_state);
    del_weak_mods(w_mod_state);
    del_oneshot_mods(o_mod_state);
    send_keyboard_report();
    tap_code16(code);
    // Reapplying modifier state so that the held shift key(s) still work even after having sent the tap code.
    add_mods(mod_state);
    add_weak_mods(w_mod_state);
    set_oneshot_mods(o_mod_state);
    send_keyboard_report();
  } else {
    tap_code(code);
  }
}

// void oopsy_finished(qk_tap_dance_state_t *state, void *user_data) {
//     if (!state->pressed && !state->interrupted && state->count == 1) {
//         // KC_MUTE will toggle, instead, lower volume
//         int i;
//         for (i = 1; i <= 20; ++i) {
//             // tap_code(KC_VOLD); // Mute audio (works w/ Boardwalk)
//             tap_code(KC__VOLDOWN);  // Mute audio (needed for Planck, not sure why)
//         }
//     } else if (!state->pressed && !state->interrupted && state->count >= 2) {
//         // hide window first, then mute
//         tap_code16(LGUI(KC_H));  // Hide Active Window
//         // KC_MUTE will toggle, instead, lower volume
//         int i;
//         for (i = 1; i <= 20; ++i) {
//             // tap_code(KC_VOLD); // Mute audio (works w/ Boardwalk)
//             tap_code(KC__VOLDOWN);  // Mute audio (needed for Planck, not sure why)
//         }
//     } else {
//         layer_on(MOUSE);
//     }
// }

void oops_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (!state->pressed && !state->interrupted && state->count == 1) {
    // if (MODS_SFT && !(IS_LAYER_ON(HRDWR)) && !(IS_LAYER_ON(AUX))) {
    //     tap_code16_no_mod(OS_DRKMD_TGL);
    // } else if (MODS_GUI) {
    //     // hide works well during command-tab switching (hide & un-hide) and independently (hide)
    //     tap_code(KC_H);
    // } else if (MODS_CTRL) {
    //     tap_code16_no_mod(ZOOM_RESET);
    // } else if (MODS_ALT) {
    //     tap_code16_no_mod(ZOOM_RESET_APP);
    // } else if (IS_LAYER_ON(AUX)) {
    //     if (MODS_SFT) {
    //         tap_code16_no_mod(LGUI(KC_S));
    //     } else {
    //         tap_code16(LGUI(KC_W));
    //     }
    // } else if (IS_LAYER_ON(HRDWR)) {
    //     if (MODS_SFT) {
    //         tap_code_no_mod(KC_END);
    //     } else {
    //         tap_code(KC_HOME);
    //     }
    // } else if (IS_LAYER_ON(FUNCXTR)) {
    //     tap_code(KC_BTN1);
    // } else {
    tap_code(KC_MUTE);
    // }
  } else if (!state->pressed && !state->interrupted && state->count >= 2) {
    // if (MODS_SFT) {
    //     // nothing
    // } else if (MODS_GUI) {
    //     // if native cmd tab is not open this will close the app behind the focused app which is wonky since the first app will get hidden, so only run if cmd+tab is open
    //     if (is_cmd_tab_active) {
    //         tap_code(KC_Q);
    //     }
    // } else if (MODS_CTRL) {
    //     // nothing
    // } else if (MODS_ALT) {
    //     // nothing
    // } else if (IS_LAYER_ON(AUX)) {
    //     // nothing
    // } else if (IS_LAYER_ON(HRDWR)) {
    //     // nothing
    // } else if (IS_LAYER_ON(FUNCXTR)) {
    //     // nothing
    // } else {
    // hide window first, then mute
    tap_code16(LGUI(KC_H));  // Hide Active Window
    // KC_MUTE will toggle, instead, lower volume
    int i;
    for (i = 1; i <= 20; ++i) {
      // tap_code(KC_VOLD); // Mute audio (works w/ Boardwalk)
      tap_code(KC__VOLDOWN);  // Mute audio (needed for Planck, not sure why)
    }
    // }
  } else {
#if defined EXECUTE_ON_FUNC
    register_code(KC_EXEC);
#endif
    layer_on(FUNC);
  }
}

void oops_reset(qk_tap_dance_state_t *state, void *user_data) {
  // if (state->pressed || state->interrupted) {
  if (IS_LAYER_ON(FUNC) && !is_layer_locked(FUNC)) {
    layer_off(FUNC);
  }
#if defined EXECUTE_ON_FUNC
  unregister_code(KC_EXEC);
#endif
  // }
}

void pemdas_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_code16(KC_ASTERISK);
      break;
    case 2:
      tap_code(KC_SLASH);
      break;
    case 3:
    case 4:
    case 5:
      tap_code16(KC_PLUS);
      break;
  }
}

void doteql_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_code(KC_DOT);
      break;
    case 2:
      tap_code(KC_EQL);
      break;
    case 3:
    case 4:
    case 5:
      tap_code16(KC_PERC);
      break;
  }
}

void tgl_select(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      // right once fixes toggle select on word/line beginnings
      tap_code(KC_RIGHT);
      tap_code16(LALT(KC_LEFT));
      tap_code16(LALT(LSFT(KC_RGHT)));
      break;
    case 2:
      tap_code(KC_RIGHT);
      tap_code16(LGUI(KC_LEFT));
      tap_code16(LGUI(LSFT(KC_RGHT)));
      break;
    case 3:
      tap_code(KC_RIGHT);
      tap_code16(LGUI(KC_UP));
      tap_code16(LGUI(LSFT(KC_DOWN)));
      reset_tap_dance(state);
      break;
  }
}

void multi_rst_each(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_code16_no_mod(WNDW_CNTR);
      break;
    case 2:
      tap_code16_no_mod(WNDW_RSTR);
      break;
  }
}

void multi_max_each(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      tap_code16_no_mod(WNDW_VRT_MAX);
      break;
    case 2:
      tap_code16_no_mod(WNDW_MAX);
      break;
  }
}

// Tap once for Word Select, twice for Line Select, three times for all
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_TGL_SEL] = ACTION_TAP_DANCE_FN_ADVANCED(tgl_select, NULL, NULL), [TD_MULTI_MAX] = ACTION_TAP_DANCE_FN_ADVANCED(multi_max_each, NULL, NULL), [TD_MULTI_RSTR] = ACTION_TAP_DANCE_FN_ADVANCED(multi_rst_each, NULL, NULL), [TD_OOPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, oops_finished, oops_reset), [TD_PEMDAS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pemdas_finished, NULL), [TD_DOTEQL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, doteql_finished, NULL),
};
// end of Tap Dance config

// Custom Shift Keys
const custom_shift_key_t custom_shift_keys[] = {
    //   {KC_COMMA, KC_SEMICOLON}, // Shift . is
    //   {KC_DOT, KC_COLON}, // Shift . is :
    //   {KC_8, KC_LEFT_PAREN}, // Shift 8 is (
    //   {KC_9, KC_RIGHT_PAREN}, // Shift 9 is )
    //   {KC_0, KC_ASTERISK}, // Shift 0 is *
    {KC_BSPACE, LALT(KC_BSPACE)},  // Shift Backspace is delete previous word
    {KC_DELETE, LALT(KC_DELETE)},  // Shift Delete is delete previous word
                                   //   {KC_F6, KC_F16}, // Shift F-* is +10 F-*
                                   //   {KC_F7, KC_F17},
                                   //   {KC_F8, KC_F18},
                                   //   {KC_F9, KC_F19},
                                   //   {KC_F10, KC_F20},
                                   //   {KC_F11, KC_F21},
                                   //   {KC_F12, KC_F22},
                                   //   {KC_F13, KC_F23},
                                   //   {KC_F14, KC_F24},
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// Custom Gui Keys
const custom_gui_key_t custom_gui_keys[] = {
    {KC_DELETE, LCTL(KC_K)},  // Gui Delete is delete line forward
};
uint8_t NUM_CUSTOM_GUI_KEYS = sizeof(custom_gui_keys) / sizeof(custom_gui_key_t);

// bool caps_word_press_user(uint16_t keycode) {
//     switch (keycode) {
//       // ignore shift presses (ie. double quote)
//       case KC_LSFT:
//       case KC_RSFT:
//         return true;
//       // Keycodes that continue Caps Word, with shift applied.
//       case KC_A ... KC_Z:
//         //   case KC_MINS: not sure why this is the default behaviour
//         add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
//         return true;

//       // Keycodes that continue Caps Word, without shifting.
//       case KC_1 ... KC_0:
//       case KC_BSPC:
//       case KC_DEL:
//  //   case KC_UNDS:
//       //  Additional keycodes
//       case KC_QUOT:
//         return true;
//       default:
//         return false;  // Deactivate Caps Word.
//     }
// }

/* Macros */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // don't activate on qwerty layer
  if (!IS_LAYER_ON(QWRTY)) {
    if (!process_custom_gui_keys(keycode, record)) {
      return false;
    }
    if (!process_custom_shift_keys(keycode, record)) {
      return false;
    }
  }
  if (!process_layer_lock(keycode, record, LLOCK)) {
    return false;
  }
  if (!process_magic_shift(keycode, record)) {
    return false;
  }
  if (!process_cmd_tab_switcher(keycode, record)) {
    return false;
  }
  if (!process_oneshot_mods(keycode, record)) {
    return false;
  }
  if (!process_symbol_rolls(keycode, record, SYMBL)) {
    return false;
  }

  switch (keycode) {
    case LT(FUNCXTR, KC_RIGHT):
    case LT(FUNCXTR, KC_SLSH):
      if (record->event.pressed) {
#if defined EXECUTE_ON_FUNC
        // Only on hold during LT(FUNCXTR)
        if (!(record->tap.count > 0)) {
          register_code(KC_EXEC);
        }
#endif
        // return true
      } else {
#if defined EXECUTE_ON_FUNC
        if (!(record->tap.count > 0)) {
          unregister_code(KC_EXEC);
        }
#endif
      }
      break;
    case TLNG_LFT:
      if (record->event.pressed) {
        clear_oneshot_mods();
        if (MODS_LSFT) {
          tap_code16_no_mod(WNDW_LFT_TTHRD);
        } else if (MODS_LGUI) {
          tap_code16_no_mod(WNDW_LFT_HLF);
        } else if (MODS_LALT) {
          tap_code16_no_mod(WNDW_LFT_THRD);
        } else if (MODS_LCTRL) {
          // tap_code16_no_mod(TLNG_THRW_LFT);
        } else {
          tap_code16(WNDW_ALMST_MAX);
        }
      }
      break;

    case TLNG_RGHT:
      if (record->event.pressed) {
        clear_oneshot_mods();
        if (MODS_LSFT) {
          tap_code16_no_mod(WNDW_RGHT_TTHRD);
        } else if (MODS_LGUI) {
          tap_code16_no_mod(WNDW_RGHT_HLF);
        } else if (MODS_LALT) {
          tap_code16_no_mod(WNDW_RGNT_THRD);
        } else if (MODS_LCTRL) {
          // tap_code16_no_mod();
        } else {
          tap_code16(WNDW_ALMST_MAX);
          tap_code16(WNDW_VRT_MAX);
        }
      }
      break;
    case TGL_LYT:
      if (record->event.pressed) {
        layer_off(HRDWR);
        if (IS_LAYER_ON(BASE)) {
          // set_single_persistent_default_layer(QWRTY);
          // dprint("BASE layer is on prior to switch");
          layer_off(BASE);
          layer_on(QWRTY);
          default_layer_set(QWRTY);
        } else {
          // set_single_persistent_default_layer(BASE);
          // dprint("QWRTY layer is on prior to switch");
          layer_off(QWRTY);
          layer_on(BASE);
          default_layer_set(BASE);
        }
      }
      return false;
      break;
    case OS_BSPC:
      if (record->event.pressed) {
        register_code(KC_BSPACE);
      } else {
        unregister_code(KC_BSPACE);
      }
      break;
    case OS_DEL:
      if (record->event.pressed) {
        register_code(KC_DELETE);
      } else {
        unregister_code(KC_DELETE);
      }
      break;
    case OS_BCK_FWD:
      if (record->event.pressed) {
        clear_oneshot_mods();
        if (MODS_SFT) {
          tap_code16_no_mod(LGUI(KC_RBRACKET));
        } else {
          tap_code16(LGUI(KC_LBRACKET));
        }
      }
      break;
    case ENC_BTN:
      if (record->event.pressed) {
        // if (IS_LAYER_ON(HIGHER) || MODS_GUI) {
        if (MODS_SFT) {
          tap_code16_no_mod(OS_DRKMD_TGL);
        } else if (MODS_CTRL) {
          tap_code16_no_mod(ZOOM_RESET);
        } else if (MODS_ALT) {
          tap_code16_no_mod(ZOOM_RESET_APP);
        } else if (MODS_GUI) {
          tap_code16(KC_H);  // command-h
        } else {
          tap_code(KC_MUTE);
        }
        return false;
      }
      break;
  }
  return true;
}

void keyboard_post_init_user(void) {
#ifdef QWERTY_BASE
  // Call the post init code.
  layer_off(BASE);
  layer_on(QWRTY);
  default_layer_set(QWRTY);
#endif
}

uint32_t layer_state_set_user(uint32_t state) {
  cmd_tab_switcher_layer_state(state);
  oneshot_mods_layer_state(state);

  state = update_tri_layer_state(state, NUMNAV, AUX, OS);

  switch (get_highest_layer(state)) {
    case BASE:
#if defined EXECUTE_ON_FUNC
      unregister_code(KC_EXEC);
#endif
#ifdef KEY_LOCK_ENABLE
      cancel_key_lock();
#endif
      break;
    case FUNC:
    case FUNCXTR:
// don't unregister_code(KC_EXEC) on this layer
#ifdef KEY_LOCK_ENABLE
      cancel_key_lock();
#endif
      break;
    default:  //  for any other layers
#if defined EXECUTE_ON_FUNC
      unregister_code(KC_EXEC);
#endif
#ifdef KEY_LOCK_ENABLE
      cancel_key_lock();
#endif
      break;
  }

  return state;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(HRDWR, KC_SPC):
      return 350;
    case TD(TD_TGL_SEL):
    case TD(TD_PEMDAS):
    case TD(TD_DOTEQL):
    case TD(TD_OOPS):
      return 225;
    case TD(TD_MULTI_MAX):
    case TD(TD_MULTI_RSTR):
      return 300;
    default:
      return TAPPING_TERM;
  }
}

// Allow Permissive Hold per key (quickly use a layer hold)
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(NUMNAV, KC_ESC):  // quickly use numbers
    case LT(SYMBL, KC_ENT):   // quickly use symbols
      return true;
    default:
      return false;
  }
}

// Mirror settings for get_permissive_hold()
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(NUMNAV, KC_ESC):
    case LT(SYMBL, KC_ENT):
      return true;
    default:
      return false;
  }
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Might roll through arrow keys
    case RGUI_T(KC_LEFT):
    case RALT_T(KC_DOWN):
    case RCTL_T(KC_UP):
      return true;
    default:
      return false;
  }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Allow per key spamming for arrow keys, space, and dash
    case RGUI_T(KC_LEFT):
    case RALT_T(KC_DOWN):
    case RCTL_T(KC_UP):
    case LT(FUNCXTR, KC_RIGHT):
    // case LT(FUNCXTR, KC_SLASH):
    case LT(HRDWR, KC_SPC):
      // case LT(MOUSE, KC_MINUS):
      return false;
    // Force hold by default
    default:
      return true;
  }
}
