USER_NAME := wheredoesyourmindgo


# LEADER_ENABLE = yes 		# + Leaders
TAP_DANCE_ENABLE = no 		# + Tap Dance
# MOUSEKEY_ENABLE = no 		# + Mouse keys
EXTRAKEY_ENABLE = yes 		# + Audio control and System control
KEY_LOCK_ENABLE = yes 		# Key lock

SRC += wheredoesyourmindgo.c
# caps word not working with conumdrum
# use caps word/sentence
# use oneshot mods fix
SRC += features/oneshot_mods.c
SRC += features/custom_shift_keys.c
# SRC += features/custom_gui_keys.c
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



