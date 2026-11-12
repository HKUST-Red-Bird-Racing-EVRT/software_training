/**
 * @file board.h
 * @author ChiHo (nganchihon@gmail.com)
 * @brief Pin mapping for Homework 4.2
 * @details Every pin used by the program is named here, and only here.
 * src/main.cpp uses the names (BUTTON_1, LED_BUILTIN, ...) and never the raw pins.
 * Moving to a different board means editing this file, not hunting through the code.
 * @version 1.0.0
 * @date 2026-11-12
 *
 * @copyright Copyright (c) 2026 Red Bird Racing
 */

#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>

// === Output ===
// MiniCore already defines LED_BUILTIN as Arduino pin 13 (PB5).
// We redefine it here so the LED pin is written down in this file like every other pin.
#undef LED_BUILTIN
#define LED_BUILTIN PIN_PB5

// === Inputs ===
#define BUTTON_1 PIN_PD1 // note: PD1 is also the UART TX pin, so don't use Serial with this board.h
#define BUTTON_2 PIN_PD2
#define BUTTON_3 PIN_PD3

// Buttons connect the pin to GND when pressed, using the internal pull-up.
// Use pinMode(BUTTON_x, BUTTON_MODE) and compare digitalRead(BUTTON_x) == BUTTON_ACTIVE.
#define BUTTON_MODE INPUT_PULLUP
#define BUTTON_ACTIVE LOW

#endif // BOARD_H
