USER_NAME := wheredoesyourmindgo


# LEADER_ENABLE = yes 		# + Leaders
TAP_DANCE_ENABLE = yes 		# + Tap Dance
# MOUSEKEY_ENABLE = no 		# + Mouse keys
EXTRAKEY_ENABLE = yes 		# + Audio control and System control
# AUTO_SHIFT_ENABLE = no 		# - Auto Shift
KEY_LOCK_ENABLE = yes 		# Key lock
# LTO_ENABLE = yes
# COMMAND_ENABLE = no			# - Command Mode
# free up some space for ristretto
# SPACE_CADET_ENABLE = no
# GRAVE_ESC_ENABLE = no
# If more space is needed consider the following option. See https://github.com/qmk/qmk_firmware/blob/develop/docs/squeezing_avr.md for more info.
# MAGIC_ENABLE = no

# LTO_ENABLE = yes
# CONSOLE_ENABLE = yes
# COMBO_ENABLE = yes # Combos
# SWAP_HANDS_ENABLE = yes # Swap Hands
# WINDOW_MGT = yes

SRC += wheredoesyourmindgo.c
# caps word not working with conumdrum
# use caps word/sentence
# SRC += features/caps_word.c
# SRC += features/caps_sentence.c
# use oneshot mods fix
SRC += features/oneshot_mods.c
SRC += features/custom_shift_keys.c
SRC += features/custom_gui_keys.c
SRC += features/magic_shift.c
SRC += features/cmd_tab_switcher.c
SRC += features/symbol_rolls.c
SRC += features/layer_lock.c

ifeq ($(strip $(EXECUTE_ON_FUNC)), yes)
  OPT_DEFS += -DEXECUTE_ON_FUNC
endif

ifeq ($(strip $(QWERTY_BASE)), yes)
  OPT_DEFS += -DQWERTY_BASE
endif



