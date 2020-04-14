#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "ControlKnob.h"
#include "AD9833FuncGen.h"

#ifndef AD9833FUNCTIONGENERATOR_H
#define AD9833FUNCTIONGENERATOR_H

#define COMPORT_SPEED 115200

#define LCD_ADDRESS   0x27
#define NBR_COLS      20
#define NBR_ROWS      4

#define PIN_CLK       18 // Default SPI CLK
#define PIN_DATA      23 // Default SPI DATA (MOSI)
#define PIN_FSYNC     5  // Default SPI CHIP SELECT AD9833
#define PIN_CS_DPOT   2  // SPI CHIP SELECT MCP41xx digital potentiometer

#define PIN_CTRLKNOB_CLK 27
#define PIN_CTRLKNOB_DAT 26
#define PIN_CTRLKNOB_SW  25

LiquidCrystal_I2C lcd(LCD_ADDRESS, NBR_COLS, NBR_ROWS);
AD9833FuncGen ad9833FuncGen(PIN_FSYNC, PIN_CS_DPOT);

ControlKnob cntrlKnob(PIN_CTRLKNOB_CLK, PIN_CTRLKNOB_DAT, PIN_CTRLKNOB_SW, lcd, ad9833FuncGen);

// Custom characters 
// topline n0t used
byte topLine[] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte backslash[] = {
  B00000,
  B10000,
  B01000,
  B00100,
  B00010,
  B00001,
  B00000,
  B00000
};

byte roundArrow[] = {
  B00000,
  B01101,
  B10011,
  B10111,
  B10000,
  B10001,
  B01110,
  B00000
};
#endif