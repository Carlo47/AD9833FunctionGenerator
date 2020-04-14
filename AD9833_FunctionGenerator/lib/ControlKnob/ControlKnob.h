#include <LiquidCrystal_I2C.h>
#include "RotaryEncoder.h"
#include "AD9833FuncGen.h"

#ifndef CONTROLKNOB_H
#define CONTROLKNOB_H

extern hw_timer_t * timer;
extern portMUX_TYPE timerMux;
extern volatile SemaphoreHandle_t timerSemaphore;

class ControlKnob;
enum class StateShow   {BOTH_SETTINGS, CHN_0_SETTINGS, CHN_1_SETTINGS, SWEEP_SETTINGS};
enum class StateSetChn {SELECT_STATE, SET_MODE, SET_VOLUME, SET_FREQ, SET_F1M, SET_F100K, SET_F10K, SET_F1K, SET_F100, SET_F10, SET_F1, SET_F01};
enum class StateSetSwp {SELECT_STATE, SET_MODE, SET_TIME, SET_FREQSTEP, SET_REP, SET_RUN, SET_10S, SET_1S, SET_100MS, SET_10MS, SET_1MS, SET_F100K, SET_F10K, SET_F1K, SET_F100, SET_F10, SET_F1, SET_F01};

typedef  void (ControlKnob::*ScreenFunc)();

inline StateShow& operator++(StateShow& state, int) 
{
  const int i = static_cast<int>(state) + 1;
  state = static_cast<StateShow>((i) % 4);
  return state;
}

inline StateShow& operator--(StateShow& state, int) 
{
    const int i = static_cast<int>(state) - 1;
    if (i < 0) 
    {
      state = static_cast<StateShow> (3);
    } 
    else 
    {
      state = static_cast<StateShow>((i) % 4);
    }
    return state;
}

class ControlKnob: public RotaryEncoder
{
  public:
    ControlKnob(uint8_t pinClk, uint8_t pinData, uint8_t pinButton, 
      LiquidCrystal_I2C &lcd, AD9833FuncGen &fgen) : RotaryEncoder(pinClk, pinData, pinButton), _lcd(lcd), _fGen(fgen)
    {
      RotaryEncoder::setup(); // Call setup method of base class
      screenFunc[0] = &ControlKnob::showScreen0;
      screenFunc[1] = &ControlKnob::showScreen1;
      screenFunc[2] = &ControlKnob::showScreen2;
      screenFunc[3] = &ControlKnob::showScreen3;
    }

    void loop();
    void setup();

  protected:
    void onCW();
    void onCCW();
    void onClick();
    void onLongClick();
    void onDoubleClick();

  private:
    void blinkPosition(uint8_t col, uint8_t row);
    void nextScreen();
    void prevScreen();
    void switchChannel();

    void showScreen0();
    void showScreen1();
    void showScreen2();
    void showScreen3();
    void showSettings(ChannelSettings &settings);
    void setSettings(ChannelSettings &settings);

    void nextMode(ChannelSettings &settings);
    void prevMode(ChannelSettings &settings);
    void incrVolume(ChannelSettings &settings);
    void decrVolume(ChannelSettings &settings);
    void incrFreq(ChannelSettings &settings);
    void decrFreq(ChannelSettings &settings);
    void incrFreqDigit(ChannelSettings &settings, uint8_t digit, double multiplier, uint8_t rowLCD);
    void decrFreqDigit(ChannelSettings &settings, uint8_t digit, double multiplier, uint8_t rowLCD);

    void nextSweepMode(SweepSettings &settings);
    void prevSweepMode(SweepSettings &settings);
    void toggleSweepRepeat(SweepSettings &settings);
    void toggleSweepRunning(SweepSettings &settings);
    void runSweep();
    void incrSweepTime(SweepSettings &settings);
    void decrSweepTime(SweepSettings &settings);
    void incrSwpFreqStep(SweepSettings &settings);
    void decrSwpFreqStep(SweepSettings &settings);
    void incrSwpTimeDigit(SweepSettings &settings, uint8_t digit, uint32_t multiplier, uint8_t rowLCD);
    void decrSwpTimeDigit(SweepSettings &settings, uint8_t digit, uint32_t multiplier, uint8_t rowLCD);

    void incrSwpFreqStepDigit(SweepSettings &settings, uint8_t digit, double multiplier, uint8_t rowLCD);
    void decrSwpFreqStepDigit(SweepSettings &settings, uint8_t digit, double multiplier, uint8_t rowLCD);

    ScreenFunc screenFunc[4];
    LiquidCrystal_I2C &_lcd;
    AD9833FuncGen &_fGen;
    StateShow _stateShow = StateShow::BOTH_SETTINGS;
    StateSetChn _stateSetChn = StateSetChn::SELECT_STATE;
    StateSetSwp _stateSetSwp = StateSetSwp::SELECT_STATE;
};
#endif