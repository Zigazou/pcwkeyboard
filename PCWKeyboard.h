#ifndef PCWKeyboard_h
#define PCWKeyboard_h

#define CLOCK_PIN 2
#define DATA_PIN 3

void pcw_keyboard_init();
void pcw_keyboard_clock_handler();
void pcw_keyboard_data_handler();

#endif
