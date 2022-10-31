// Copyright 2021 Google LLC.
// SPDX-License-Identifier: Apache-2.0

#include "cmd_tab_switcher.h"
#include "wheredoesyourmindgo.h"

bool is_cmd_tab_active = false;
bool is_cmd_tab_held   = false;

uint16_t cmd_tab_timer         = 0;
uint16_t cmd_tab_timer_timeout = cmd_tab_timer_default_dur;

void cancel_cmd_shift(void) {
  unregister_mods(MOD_BIT(KC_LGUI));
  if (MODS_LSFT) {
    unregister_mods(MOD_BIT(KC_LSFT));
  }
  is_cmd_tab_active     = false;
  cmd_tab_timer_timeout = cmd_tab_timer_default_dur;
}

void cmd_tab_switcher_layer_state(uint16_t state) {
  switch (get_highest_layer(state)) {
    default:  //  for any other layers, or the default layer
      // cancel cmd-tab switcher when switching back to base layer
      if (is_cmd_tab_active) {
        cancel_cmd_shift();
      }
      break;
  }
}

void cmd_tab_switcher_matrix_scan_user(void) {
  if (is_cmd_tab_active) {
    // RGUI mod will be active when encoder is in use so don't cancel cmd shift once it's starts programatically with cmd_tab_next/previous(). This works since RGUI is used by encoder and LGUI is used by cmd tab switcher.
    if (timer_elapsed(cmd_tab_timer) > cmd_tab_timer_timeout && !is_cmd_tab_held && !MODS_RGUI) {
      cancel_cmd_shift();
    }
  }
}

void cmd_tab_previous(void) {
  if (!is_cmd_tab_active) {
    is_cmd_tab_active = true;
    register_mods(MOD_BIT(KC_LGUI));
  } else {
    // Speed up timer when cmd+tab is already active (ie. when moving left and right in switcher)
    cmd_tab_timer_timeout = cmd_tab_timer_fast_dur;
  }
  register_mods(MOD_BIT(KC_LSFT));
  tap_code(KC_TAB);
  cmd_tab_timer = timer_read();
  unregister_mods(MOD_BIT(KC_LSFT));
}

void cmd_tab_next(void) {
  if (!is_cmd_tab_active) {
    is_cmd_tab_active = true;
    register_mods(MOD_BIT(KC_LGUI));
  } else {
    // Speed up timer when cmd+tab is already active (ie. when moving left and right in switcher)
    cmd_tab_timer_timeout = cmd_tab_timer_fast_dur;
  }
  tap_code(KC_TAB);
  cmd_tab_timer = timer_read();
}

bool process_cmd_tab_switcher(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case OS_PRV_SPC:
    case OS_NXT_SPC:
      if (record->event.pressed) {
        is_cmd_tab_held = true;
      } else {
        cmd_tab_timer   = timer_read();
        is_cmd_tab_held = false;
      }
      break;
    case CMD_TAB_NXT:
      if (record->event.pressed) {
        if (!is_cmd_tab_active) {
          is_cmd_tab_active = true;
          register_mods(MOD_BIT(KC_LGUI));
        } else {
          // Speed up timer when cmd+tab is already active (ie. when moving left and right in switcher)
          cmd_tab_timer_timeout = cmd_tab_timer_fast_dur;
        }
        is_cmd_tab_held = true;
        unregister_mods(MOD_BIT(KC_LSFT));
        // cmd_tab_timer = timer_read(); // Start the timer when the key is released, not pressed
        tap_code(KC_TAB);
      } else {
        cmd_tab_timer   = timer_read();
        is_cmd_tab_held = false;
      }
      break;
    case LGUI(KC_Q):
    case LGUI(KC_H):
      if (record->event.pressed) {
        if (is_cmd_tab_active) {
          cmd_tab_timer_timeout = cmd_tab_timer_default_dur;
        }
      }
      break;
    case OS_EXPOSE:
      if (record->event.pressed) {
        if (is_cmd_tab_active) {
          tap_code(KC_UP);
          return false;
        }
      }
      break;
    case CMD_TAB_PRV:
      if (record->event.pressed) {
        if (!is_cmd_tab_active) {
          is_cmd_tab_active = true;
          register_mods(MOD_BIT(KC_LGUI));
        } else {
          // Speed up timer when cmd+tab is already active (ie. when moving left and right in switcher)
          cmd_tab_timer_timeout = cmd_tab_timer_fast_dur;
        }
        register_mods(MOD_BIT(KC_LSFT));
        tap_code(KC_TAB);
        is_cmd_tab_held = true;
        // cmd_tab_timer = timer_read(); // Start the timer when the key is released, not pressed
      } else {
        cmd_tab_timer   = timer_read();
        is_cmd_tab_held = false;
        unregister_mods(MOD_BIT(KC_LSFT));
      }
      break;
    // instantly switch to app after RGUI is let go when cmd tab is activated using encoder and RGUI
    case KC_RGUI:
    case RGUI_T(KC_LEFT):
      if (!(record->event.pressed)) {
        cancel_cmd_shift();
      }
      break;
  }

  return true;
}
