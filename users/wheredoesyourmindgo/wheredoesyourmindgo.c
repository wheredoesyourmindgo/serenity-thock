#include "wheredoesyourmindgo.h"
#include "features/oneshot_mods.h"
#include "features/custom_shift_keys.h"
#include "features/custom_gui_keys.h"
#include "features/magic_shift.h"
#include "features/cmd_tab_switcher.h"
#include "features/symbol_rolls.h"
#include "features/layer_lock.h"
#include "features/hide_and_mute.h"

#ifdef CONSOLE_ENABLE
#  include "print.h"
#endif

// extern int retro_tapping_counter;

// Helper for implementing tap vs. long-press keys. Given a tap-hold
// key event, replaces the hold function with `long_press_keycode`.
bool process_tap_or_long_press_key(
    keyrecord_t* record, uint16_t long_press_keycode) {
  if (record->tap.count == 0) {  // Key is being held.
    if (record->event.pressed) {
      tap_code16(long_press_keycode);
    }
    return false;  // Skip default handling.
  }
  return true;  // Continue default handling.
}


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
  if (!hide_and_mute(keycode, record, LT(FUNC,KC_MUTE))) {
    return false;
  }

  switch (keycode) {
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
    case WNDW_LP_MAX:
        if (record->tap.count > 0) {    // Key is being tapped.
            if (record->event.pressed) {
                // Handle tap press event...
                tap_code16(WNDW_MAX);
            }
        } else {                        // Key is being held.
            if (record->event.pressed) {
                // Handle hold press event...
                tap_code16(WNDW_VRT_MAX);
            }
        }
        return false;  // Skip default handling.
        break;
    case WNDW_LP_CNTR:
        if (record->tap.count > 0) {    // Key is being tapped.
            if (record->event.pressed) {
                // Handle tap press event...
                tap_code16(WNDW_CNTR);
            }
        } else {                        // Key is being held.
            if (record->event.pressed) {
                // Handle hold press event...
                tap_code16(WNDW_ALMST_MAX);
            }
        }
        return false;  // Skip default handling.
        break;
    case WNDW_LP_RST:
        if (record->tap.count > 0) {    // Key is being tapped.
            if (record->event.pressed) {
                // Handle tap press event...
                tap_code16(WNDW_RSTR);
            }
        } else {                        // Key is being held.
            if (record->event.pressed) {
                // Handle hold press event...
                tap_code16(WNDW_LST);
            }
        }
        return false;  // Skip default handling.
        break;
    case WNDW_LP_SMLR:
        if (record->tap.count > 0) {    // Key is being tapped.
            if (record->event.pressed) {
                // Handle tap press event...
                tap_code16(WNDW_SMLLR);
            }
        } else {                        // Key is being held.
            if (record->event.pressed) {
                // Handle hold press event...
                tap_code16(WNDW_LFT_HLF);
            }
        }
        return false;  // Skip default handling.
        break;
    case WNDW_LP_LGR:
        if (record->tap.count > 0) {    // Key is being tapped.
            if (record->event.pressed) {
                // Handle tap press event...
                tap_code16(WNDW_LRGR);
            }
        } else {                        // Key is being held.
            if (record->event.pressed) {
                // Handle hold press event...
                tap_code16(WNDW_RGHT_HLF);
            }
        }
        return false;  // Skip default handling.
        break;
    case MSN_LP_FLLSCRN:  // Mission Control on tap, OS full screen on long press
        // return process_tap_or_long_press_key(record, OS_FLLSCRN);
        if (record->tap.count > 0) {    // Key is being tapped.
            if (record->event.pressed) {
                // Handle tap press event...
                tap_code16(OS_MSN_CNTRL);
            } else {
                // Handle tap release event...
            }
        } else {                        // Key is being held.
            if (record->event.pressed) {
                // Handle hold press event...
                tap_code16(OS_FLLSCRN);
            } else {
                // Handle hold release event...
            }
        }
        return false;  // Skip default handling.
        break;
    case PRV_SPC_LP:
        if (record->tap.count > 0) {    // Key is being tapped.
            if (record->event.pressed) {
                // Handle tap press event...
                tap_code16(OS_PRV_SPC);
            }
        } else {                        // Key is being held.
            if (record->event.pressed) {
                // Handle hold press event...
                tap_code16(OS_TL_WNDW_L);
            }
        }
        return false;  // Skip default handling.
        break;
    case NXT_SPC_LP:
        if (record->tap.count > 0) {    // Key is being tapped.
            if (record->event.pressed) {
                // Handle tap press event...
                tap_code16(OS_NXT_SPC);
            }
        } else {                        // Key is being held.
            if (record->event.pressed) {
                // Handle hold press event...
                tap_code16(OS_TL_WNDW_R);
            }
        }
        return false;  // Skip default handling.
        break;
    case QUOT_LP:
        return process_tap_or_long_press_key(record, KC_DOUBLE_QUOTE);
        break;
    case DOT_LP:
        return process_tap_or_long_press_key(record, KC_COMM);
        break;
    // Cancel Layer Lock on Escape
    case KC_ESC:
        if (record->event.pressed) {
            const uint8_t layer = get_highest_layer(layer_state);
            if (is_layer_locked(layer)) {
                layer_lock_off(layer);
                return false;  // Skip default handling.
            }
        }
        break;
    case LT(NUMNAV, KC_ESC):
        if (record->tap.count > 0) {
            if (record->event.pressed) {
                const uint8_t layer = get_highest_layer(layer_state);
                if (is_layer_locked(layer)) {
                    layer_lock_off(layer);
                    return false;  // Skip default handling.
                }
            }
        }
        break;
    case TGL_SELECT_LP:
        if (record->tap.count > 0) {
            if (record->event.pressed) {
                // right once fixes toggle select on word/line beginnings
                tap_code(KC_RIGHT);
                tap_code16(LALT(KC_LEFT));
                tap_code16(LALT(LSFT(KC_RGHT)));
            }
        } else {
            if (record->event.pressed) {
                tap_code(KC_RIGHT);
                tap_code16(LGUI(KC_LEFT));
                tap_code16(LGUI(LSFT(KC_RGHT)));
                // select all
                // tap_code(KC_RIGHT);
                // tap_code16(LGUI(KC_UP));
                // tap_code16(LGUI(LSFT(KC_DOWN)));
            }
        }
        return false;  // Skip default handling.
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
  
      // Use `static` variable to remember the previous status.
    static bool func_on = false;

    if (func_on != (IS_LAYER_ON_STATE(state, FUNC) || (IS_LAYER_ON_STATE(state, FUNCXTR)))) {
        func_on = !func_on;
        if (func_on) {
            // Just entered one of the FUNC layers.
            #if defined EXECUTE_ON_FUNC
            register_code(KC_EXEC);
            #endif
        } else {
            // Just exited the one of FUNC layers.
            #if defined EXECUTE_ON_FUNC
            unregister_code(KC_EXEC);
            #endif
        }
    }

    // always call cancel_key_lock()
    #ifdef KEY_LOCK_ENABLE
    cancel_key_lock();
    #endif

    return state;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(HRDWR, KC_SPC):
      return 350;
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
