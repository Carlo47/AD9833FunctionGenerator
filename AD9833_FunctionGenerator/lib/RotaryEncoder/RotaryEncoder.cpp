/**
  * Drehgeber-Klasse mit Entprellung der Drehbewegung und des axialen Tasters.
  * 
  * Die auszuführenden Methoden
  * onCW()     (Drehung im Uhrzeigersinn - clock wise)
  * onCCW()    (Drehung im Gegenuhrzeigersinn - counter clock wise)
  * onClick()  (Betätigen des axialen Tasters)
  * sind in einer abgeleiteten Klasse zu implementieren.
  * 
  *       ______          ______  
  * ____||      ||______||         Clk       
  *     :       :       :
  *    ______   :      ______
  * _|| :    ||______|| :    ||_   Data
  *     :       :       :
  *     :_______:       :_______
  * ____|       |_______|          Cleaned clock (copy stable data value on jittering clock edge)
  *
  * Drehung im Uhrzeigersinn, wenn der vorherige saubere Clockzustand 0 war und 
  * der aktuelle Clockzustand 1 ist.
  * Drehung im Gegenuhrzeigersinn, wenn der vorherige saubere Clockzustand 1 war 
  * und der aktuelle Clockzustand 1 ist.
  * Die Verknüpfung der Clockzustände wird gemacht, um nur auf eine Flanke bei 
  * einem Drehschritt zu reagieren.
  *
  */

#include <Arduino.h>
#include "RotaryEncoder.h"
 
void RotaryEncoder::setup()
{
  pinMode(_pinClk, INPUT);
  pinMode(_pinData, INPUT);
  pinMode(_pinButton, INPUT_PULLUP);
  _prevClkState = HIGH;
  _prevCleanedClkState = HIGH; 
  _buttonState = HIGH;
  _clickCount = 0;
  _msFirstClick = 0;
}

void RotaryEncoder::loop()
{
  _clkState  = digitalRead(_pinClk);
  _dataState = digitalRead(_pinData);
  _prevButtonState = _buttonState;
  _buttonState = digitalRead(_pinButton);

  // Debouncing pushbutton
  if (_prevButtonState == HIGH && _buttonState == LOW) // Axial pushbutton pressed
  {
    _msButtonDown = millis();                          // Memorize time
  }
  else if (_prevButtonState == LOW && _buttonState == HIGH) // Pushbutton released
  {
    if (millis() - _msButtonDown < _msDebounce)        // Pushutton bounces
    {
      // Ignore bouncing
    }
    else if (millis() - _msButtonDown > _msLongClick)  // Its a long click
    {
      onLongClick();
    }
    else
    {
      _clickCount++;                  
      if (_clickCount == 1)           // Time of 1st click, just memorize
        _msFirstClick = millis();
    }
  }
  else       // This branch only passed through when nothing is to do in loop 
  {
    if (_clickCount == 1 && millis() - _msFirstClick > _msDoubleClickGap) // Time after 1st click expired
      {
        _msFirstClick = 0;
        _clickCount = 0;
        onClick();
      }
    else if (_clickCount > 1)         // More than 1 click done 
    {
      _msFirstClick = 0;
      _clickCount = 0;
      onDoubleClick(); 
    } 
  }
  
    
  // Debouncing rotary encoder
  if (_prevClkState != _clkState)     // Clock change detected (even bouncing)
  {
    _prevClkState = _clkState;
    _cleanedClkState = _dataState;    // Copy data state to get clean clock
    // Serial.println("bouncing");

    if (_prevCleanedClkState != _cleanedClkState) // Clock change detected 
    {
      /*
      char s[60];
      sprintf(s, "clean clock changed from %d to %d with clk %d", _prevCleanedClkState, _cleanedClkState, _clkState);
      Serial.println(s); 
      */
      
      if (_prevCleanedClkState == LOW && _clkState == 1)
        onCW();
      if (_prevCleanedClkState == HIGH && _clkState == 1)
        onCCW();
    }
    _prevCleanedClkState = _cleanedClkState;
  }
}
