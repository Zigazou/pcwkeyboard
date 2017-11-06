#include "PCWKeyboard.h"

void setup() {
  pcw_keyboard_init();
  Serial.begin(19200);
}

char *keys[16][8] = {
  { "F3/F4", "KP0", "F1/F2", "Paste", "KP9", "KP6", "KP3", "KP2" },
  { "Exit", "PTR", "Cut", "Copy", "KP8", "KP4", "KP5", "KP1" },
  { "Del->", "]", "Return", ">", "KP7", "Shift", "1/2", "[+]" },
  { "=", "-", "[", "P", "<", ";", "?", "."},
  { "0", "9", "O", "|", "L", "K", "M", "," },
  { "8", "7", "U", "Y", "H", "J", "N", "Space" },
  { "6", "S", "R", "T", "G", "F", "B", "V" },
  { "4", "3", "E", "W", "S", "D", "C", "X" },
  { "1", "2", "Stop", "Q", "Tab", "A", "Shift Lock", "Z" },
  { "J1 up", "J1 down", "J1 left", "J1 right", "J1 fire 2", "J1 fire 1", "", "<-Del" },
  { "F5/F6", "Extra", "Cancel", "[-]", "F7/F8", "KPEnter", "KPPoint", "Alt" },
  { "J2 up", "J2 down", "J2 left", "J2 right", "J2 fire 2", "J2 fire 1", "", "" },
  { "(F3/F4)", "(F1/F2)", "(Exit)", "(KP0)", "(Space)", "(KPEnter)", "", "" },
  { "(KP5)", "(KPPoint)", "(KP1)", "(KP3)", "(KP2)", "(Space)", "Shift Lock Led", "~LK2" },
  { "(ASDFGHJ)", "(ZXCVBNM)", "(QEO[L<,/)", "(WRP];>.1/2)", "(Space)", "(Shift)", "LK1", "LK3" },
  { "(H J K L ; < >)", "(BNM,./1/2)", "(QEO[ADZC)", "(WRP]SFXV)", "(Space)", "(Shift)", "Ticker", "UpdateFlag" }
};

extern char pcw_keyboard_map[];
void decodeKeyboardWord(int index) {
  char value;

  //if(index == 15) return;

  value = pcw_keyboard_map[index];
  if(value == 0) return;
  for(int i = 0; i < 8; i++) {
    if(value & 1 && keys[index][i][0] != '\0') {
      Serial.print(keys[index][i]);
    }
    value = value >> 1;
  }
}

void loop() {
  int word_value;

  delay(100);
  for(int i = 0; i < 12; i++) {
    decodeKeyboardWord(i);
  }
}
