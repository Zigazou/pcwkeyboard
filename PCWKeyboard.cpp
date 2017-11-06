#include "PCWKeyboard.h"

#include <Arduino.h>

volatile int pcw_keyboard_current;
volatile int pcw_keyboard_last;
volatile int pcw_keyboard_bit_position;
volatile char pcw_keyboard_map[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void pcw_keyboard_clock_handler() {
  int bit_value;

  pcw_keyboard_bit_position--;
  bit_value = digitalRead(DATA_PIN) == HIGH ? 1 : 0;
  pcw_keyboard_current |= bit_value << pcw_keyboard_bit_position;

  if(pcw_keyboard_bit_position == 0) {
    int index = (pcw_keyboard_current >> 8) & 0x0f;
    pcw_keyboard_map[index] = (char)(pcw_keyboard_current & 0xff);
    pcw_keyboard_current = 0;
    pcw_keyboard_bit_position = 12;
  }
}

void pcw_keyboard_data_handler() {
  if(digitalRead(CLOCK_PIN) == LOW) return;

  pcw_keyboard_current = 0;
  pcw_keyboard_bit_position = 12;
}

void pcw_keyboard_init() {
  pcw_keyboard_current = 0;
  pcw_keyboard_bit_position = 12;

  pinMode(CLOCK_PIN, INPUT_PULLUP);
  pinMode(DATA_PIN, INPUT_PULLUP);
/*
  attachInterrupt(
    digitalPinToInterrupt(DATA_PIN),
    pcw_keyboard_data_handler,
    RISING
  );*/

  attachInterrupt(
    digitalPinToInterrupt(CLOCK_PIN),
    pcw_keyboard_clock_handler,
    FALLING
  );
}
