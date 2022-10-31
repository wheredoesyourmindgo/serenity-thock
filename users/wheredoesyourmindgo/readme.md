# Serenity

## About

This is a QMK layout that includes dedicated right and left shift keys. The Base layer uses the Serenity alpha layout. This layout is configured for use with macOS and would generally be used with a 42+ key layout.

## Features

- 6+ layers, including: Lower (Numbers/Navigation), Low (Symbols), Lowest (Mouse Mode), Higher (Cut-copy-paste/Special), High (Media/Keyboard), and Highest (Function). See below for 3 additional macOS layers.
- One Shot Mods on Home Row when activating any of the 6 principle layers. These are particularly useful for same hand mod presses (eg. "Command + 1..5") that require use of the same hand.
- Control, Alt, GUI, and Shift Mods on both sides. Arrow keys on bottom right double as Layer/Mod toggle when held. All four arrow keys can be spammed when tapped twice.
- Two dual use keys. The Lower Layer and Higher layer keys can be used as Shift keys for improved dexterity and better ergonomics. When using a multi-key combo with mods the inner adjacent key that is used for activating the Lowest (left) and Highest layer (right) can be used as a Shift mod key. It doesn't matter which order you press the sequence of mod keys. As long as 1 or more mod keys is pressed in conjunction with the adjacent Lower/Higher Layer key, that key press will immediately become a Shift mod press until the key is released. See below for use case.
- Layers can be held/stuck using the "y" & "g" keys while activating a layer. Use cases include persistence of the Keyboard Mouse, or performing numerical data entry with the Lower_layer active for extended periods. Un-stick layers by tapping the respective layer key again.
- Easy and flexible capslock; Capslock can be toggled on/off with a opposite shift tap when Low or High layer is active. Additionally,
  - Caps-word can be toggled with a simultaneous left and right tap. Caps-word will disable at the first occurrence of a space, comma, semi-colon, colon, period(dot), escape, tab, or enter tap. Left shift is greedy in regard to interruption.
  - Caps-sentence can be toggled with a opposite shift tap when Lower or Higher layer is active. Caps-sentence will disable at the first occurrence of a period(dot), escape, or enter tap. Right shift is greedy in regard to interruption.
- Key lock on Mouse layer for dexterity and ease of use with text selections or holding mouse button clicks.
- (macOS) Easy access to macOS command key using thumbs. macOS is chock-full of shortcuts that utilize the command key so I'm calling this a feature.
- (macOS) Double left control tap hides active window and mutes volume. Left control is greedy in regard to interruption.
- (macOS) An additional shortcut within the Higher layer on the "z" key doubles as a word, line, all select when single, double, and triple tapped respectively. This text select expansion functionality is reminiscent to how double, triple, and quadruple mouse clicks behaves (note - line select via double tap may not work as intended on lines that soft wrap).
- (macOS) Additional Layer for macOS shortcuts, activated with simultaneous lower and higher hold. See keymap.c
- (macOS) Window Management shortcuts using [Rectangle](https://rectangleapp.com)
& [Rectangle](https://rectangleapp.com/) on the Higher layer. See [Reference](#WindowMgtRef) below for additional info.
- (macOS) Shortcuts for quick access to word & line backspace and word & line delete forward. These are activated from Lower, Lowest, Higher, and Highest layers, respectively. For convenience, the word delete will not trigger when entering numbers in Lower layer, which is ideal for using backspace within Lower layer (the side effect is that words that end with a number can't be word-deleted until Lower hold is released and held again).
- (make option) Hold the Execute key (KC_EXECUTE) while holding down the function key. This can be enabled by building firmware with `EXECUTE_ON_FUNC=yes` option. The Execute keycode is not used by MacOS, but it will register, so it can be converted to something else such as the Function "fn" key via a Karabiner-Elements rule which will enable further customization via Karabiner-Elements with additional rules.

## Usage

### Mods

Control, Alt/Option, GUI/Command mods are mirrored, located on bottom left and right. When activating a multi-combo mod press, move your hand in the same fashion as you would if there were an arrow cluster there towards the bottom corner. Effectively, this in turn should feel very reminiscent to using home row mods. Since mods are mirrored on both the bottom right and left use opposite hand to press key. When activating single mod presses, leave your hand above the home row and lower the corresponding finger down 2 rows to activate the press and hold. This is done identically to how mods are typically activated with a standard ANSI layout. Again, since mods are mirrored on both the bottom right and left use opposite hand to press key.

### Case for Right Handed Space

1. Right handedness is not uncommon.
2. It is useful to be able to use space while using the navigation arrows without having to release the layer hold to re-press the same
   key, especially when returning to the lower layer repeatedly.
3. The Lower & Low layers are used for numbers and symbols. It is faster/easier to follow these layer presses by tapping space with the opposite hand instead of releasing and re-tapping the same key.
4. Allows for setting tapping term much lower (0) on frequently used numbers and symbols layers since those are mapped to Esc and Enter respectively. By using Permissive Hold, the result is Lower (number) and Low (symbol) are more greedy than Enter presses and Escape presses, while the Space (and Tab) taps can be more greedy on the right side of the keyboard.
5. Related, having enter key next to space is not ideal due to the chance of miss-tap resulting from the proximity; thus, tab joins space on right side, enter with escape on left.

## Reference


### Rectangle

Rectangle shortcuts are arranged on the Higher layer on the left-hand side on home row. Alternate shortcuts can be triggered using the mods on the home row on the right side within the Higher layer. Below is a map of the commands and mod presses.

| **Mod** | `S` | `R`  | `H` | `N` |
|--- | --- | --- | --- | ---|
|**Shift**|OSD Current Layout|Cycle Layout Back|Cycle Layout Forward|Floating Layout|
|**Cmd**|*currently void*|Shrink Main|Expand Main|Toggle Float Focused|
|**Opt**|Toggle Global Tiling|Decrease Main Count|Increase Main Count|Toggle Focus w/ Mouse|
|**Ctrl**|Reload Amethyst|Throw Focused to Left Space|Throw Focused to Right Space|Re-evaluate Layout|
|**-**|Switch Focus to Main|Move Focus C-Clockwise|Move Focus Clockwise|Swap Main w/ Focused|

## Tips

-   When using a keyboard flashed with this firmware/layout on a MacBook, consider using Karabiner Elements to disable the built-in Apple keyboard when QMK keyboard is plugged in.
-   On macOS, using System Preferences or Karabiner Elements, consider using F keys as standard Function keys since OS and Media controls are already implemented in their respective layers.
- Certain (command line) applications may require use of function keys, namely F1-F10. Worth considering mapping the higher function keys first (start w/ F24 and work downwards) for OS shortcuts as desired.
-   In order to optimize this layout for use with Windows or \*nix you'll likely want to modify the mod order since this layout is primarily targeted towards use with macOS (which utilizes the Command/GUI key in a manner similar to how Windows treats the Control key). The order for mods on the left half is Control --> Option/Alt --> Command/GUI --> Shift; These mods are in reverse order on the right half.
-   Keep in mind, when activating a Layer on the bottom row in conjunction with a Mod key press on the home row (ex. Shift+Arrow_Left to select text) the key sequence order is important. The layer must be held first, then home row mod can be activated.
-   Capslock + Vim can be dizzying, I recommend using CapsLocker for MacOS for a decent notification when capslock is toggled.
-   For more information on home row mods see an extensive write-up at [https://precondition.github.io/home-row-mods](https://precondition.github.io/home-row-mods)
