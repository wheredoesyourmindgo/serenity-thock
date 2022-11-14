#pragma once

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
// #define TAPPING_TOGGLE 2

// #define RGBLIGHT_SLEEP true
// #define DEBUG_ACTION

#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
// Enable per key rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD_PER_KEY
// #define RETRO_TAPPING_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY


// #define LEADER_PER_KEY_TIMING
// #define LEADER_TIMEOUT 250

// Keyboard specific
#if defined SIGNUM_KEYBOARD
#undef MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_MOVE_DELTA 5
#elif defined BOARDWALK_KEYBOARD
// #define MOUSEKEY_INTERVAL       12
/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed, defaults to 5 for Boardwalk */
//  #undef DEBOUNCE
//  #define DEBOUNCE 10
#elif defined PLANCK_KEYBOARD
    #if ENCODER_ENABLE
    #define ENCODER_RESOLUTION 2
    #endif
#elif defined RISTRETTO_KEYBOARD
#define ENCODER_DIRECTION_FLIP
#endif
