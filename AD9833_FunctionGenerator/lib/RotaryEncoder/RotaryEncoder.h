/**
  * Drehgeber-Klasse mit Entprellung der Drehbewegung und des axialen Tasters.
  * 
  * Die auszuführenden Methoden
  *     onCW()            (Drehung im Uhrzeigersinn - clock wise)
  *     onCCW()           (Drehung im Gegenuhrzeigersinn - counter clock wise)
  *     onClick()         (Betätigen des axialen Tasters)
  *     onLongClick()     (Langes Betätigen des axialen Tasters)
  *     onDoubleClick()   (Doppeltes Betätigen des axialen Tasters)
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
 
#include<Arduino.h>

#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

class RotaryEncoder
{
  virtual void onCW();
  virtual void onCCW();
  virtual void onClick();
  virtual void onLongClick();
  virtual void onDoubleClick();
  
  public:
    //Konstruktor
    RotaryEncoder(uint8_t pinClk, uint8_t pinData, uint8_t pinButton) : _pinClk(pinClk), _pinData(pinData), _pinButton(pinButton)
    {
    }

    void setup();
 
    void loop();
   
  private:
    uint8_t _clkState;
    uint8_t _prevClkState;
    uint8_t _cleanedClkState;
    uint8_t _prevCleanedClkState;
    uint8_t _buttonState;
    uint8_t _prevButtonState;
    uint8_t _dataState;
    uint8_t _pinClk;
    uint8_t _pinData;
    uint8_t _pinButton;
    uint8_t _clickCount;
    unsigned long _msDebounce = 50;        // Nach 50ms sollte der Button einen stationären Zustand erreicht haben
    unsigned long _msLongClick = 300;      // Button länger als 300ms gehalten gilt als LongClick
    unsigned long _msDoubleClickGap = 250; // Zwei Buttenclicks innerhalb 250ms gelten als DoubleClick
    unsigned long _msButtonDown;
    unsigned long _msFirstClick;
};

#endif
