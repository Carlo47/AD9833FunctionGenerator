#include "ControlKnob.h"

/**
 * Shows initial screen
 */
void ControlKnob::setup()
{
  showScreen0();
}

/**
 * Runs loop of base class and runs sweep if enabled
 */
void ControlKnob::loop()
{
  RotaryEncoder::loop();
  if (_fGen.settings.swp.running)
  {
    runSweep();
  }
}

/**
 * Handles clockwise rotation of rotary encoder shaft
 */
void ControlKnob::onCW()
{
  //Serial.printf("onCW stateShow=%d, stateSetChn=%d, stateSetSwp=%d\r\n", (int)_stateShow, (int)_stateSetChn, (int)_stateSetSwp);
  
  if (_stateSetChn == StateSetChn::SELECT_STATE && _stateSetSwp == StateSetSwp::SELECT_STATE)
  {
    nextScreen();
    if (_stateShow == StateShow::CHN_0_SETTINGS) setSettings(_fGen.settings.ch_0);
    if (_stateShow == StateShow::CHN_1_SETTINGS) setSettings(_fGen.settings.ch_1);
  } 
  else
  {  
    switch (_stateShow)
    {
      case StateShow::BOTH_SETTINGS:  
      break;
      case StateShow::CHN_0_SETTINGS:
        setSettings(_fGen.settings.ch_0);
        switch (_stateSetChn)
        { 
          case StateSetChn::SET_MODE:
            nextMode(_fGen.settings.ch_0);
            showScreen1();
            blinkPosition(0, 1);
          break;
          case StateSetChn::SET_VOLUME:
            incrVolume(_fGen.settings.ch_0);
            showScreen1();
            blinkPosition(0, 2);
          break;
          case StateSetChn::SET_FREQ:
          break;
          case StateSetChn::SET_F1M:
          case StateSetChn::SET_F100K:
          case StateSetChn::SET_F10K:
          case StateSetChn::SET_F1K:
          case StateSetChn::SET_F100:
          case StateSetChn::SET_F10:
          case StateSetChn::SET_F1:
          case StateSetChn::SET_F01:
            incrFreq(_fGen.settings.ch_0);
          break;
          default:
          break;
        }
      break;
      case StateShow::CHN_1_SETTINGS:
        setSettings(_fGen.settings.ch_1);
        switch (_stateSetChn)
        {
          case StateSetChn::SET_MODE:
            nextMode(_fGen.settings.ch_1);
            showScreen2();
            blinkPosition(0, 1);
          break;
          case StateSetChn::SET_VOLUME:
            incrVolume(_fGen.settings.ch_1);
            showScreen2();
            blinkPosition(0, 2);
          break;
          case StateSetChn::SET_FREQ:
          break;
          case StateSetChn::SET_F1M:
          case StateSetChn::SET_F100K:
          case StateSetChn::SET_F10K:
          case StateSetChn::SET_F1K:
          case StateSetChn::SET_F100:
          case StateSetChn::SET_F10:
          case StateSetChn::SET_F1:
          case StateSetChn::SET_F01:
            incrFreq(_fGen.settings.ch_1);
          break;
          default:
          break;
        }
      break;
      case StateShow::SWEEP_SETTINGS:
        switch(_stateSetSwp)
        {
          case StateSetSwp::SET_MODE:
            nextSweepMode(_fGen.settings.swp);
            showScreen3();
            blinkPosition(0, 1);
          break;
          case StateSetSwp::SET_REP:
            toggleSweepRepeat(_fGen.settings.swp);
            showScreen3();
            blinkPosition(11, 1);
          break;
          case StateSetSwp::SET_TIME:
          break;
          case StateSetSwp::SET_10S:
          case StateSetSwp::SET_1S:
          case StateSetSwp::SET_100MS:
          case StateSetSwp::SET_10MS:
          case StateSetSwp::SET_1MS:
            incrSweepTime(_fGen.settings.swp);
          break;
          case StateSetSwp::SET_FREQSTEP:
          break;
          case StateSetSwp::SET_F100K:
          case StateSetSwp::SET_F10K:
          case StateSetSwp::SET_F1K:
          case StateSetSwp::SET_F100:
          case StateSetSwp::SET_F10:
          case StateSetSwp::SET_F1:
          case StateSetSwp::SET_F01:
            incrSwpFreqStep(_fGen.settings.swp);
          break;
          case StateSetSwp::SET_RUN:
            toggleSweepRunning(_fGen.settings.swp);
            showScreen3();
            blinkPosition(0, 0);
          break;
          default:
          break;
        }
      break;
      default:
      break;
    }
  }
}

/**
 * Handles counterclockwise rotation of rotary encoder shaft
 */
void ControlKnob::onCCW()
{
  Serial.printf("onCCW stateShow=%d, stateSetChn=%d, stateSetSwp=%d\r\n", (int)_stateShow, (int)_stateSetChn, (int)_stateSetSwp);
  if (_stateSetChn == StateSetChn::SELECT_STATE && _stateSetSwp == StateSetSwp::SELECT_STATE)
  {
    prevScreen();
    if (_stateShow == StateShow::CHN_0_SETTINGS) setSettings(_fGen.settings.ch_0);
    if (_stateShow == StateShow::CHN_1_SETTINGS) setSettings(_fGen.settings.ch_1);
  } 
  else
  {
    switch (_stateShow)
    {
      case StateShow::BOTH_SETTINGS:
      break;
      case StateShow::CHN_0_SETTINGS:
        setSettings(_fGen.settings.ch_0);
        switch (_stateSetChn)
        {
          case StateSetChn::SET_MODE:
            prevMode(_fGen.settings.ch_0);
            showScreen1();
            blinkPosition(0, 1);
          break;
          case StateSetChn::SET_VOLUME:
            decrVolume(_fGen.settings.ch_0);
            showScreen1();
            blinkPosition(0, 2);
          break;
          case StateSetChn::SET_FREQ:
          break;
          case StateSetChn::SET_F1M:
          case StateSetChn::SET_F100K:
          case StateSetChn::SET_F10K:
          case StateSetChn::SET_F1K:
          case StateSetChn::SET_F100:
          case StateSetChn::SET_F10:
          case StateSetChn::SET_F1:
          case StateSetChn::SET_F01:
            decrFreq(_fGen.settings.ch_0);
          break;
          default:
          break;
        }
      break;
      case StateShow::CHN_1_SETTINGS:
        setSettings(_fGen.settings.ch_1);
        switch (_stateSetChn)
        {
          case StateSetChn::SET_MODE:
            prevMode(_fGen.settings.ch_1);
            showScreen2();
            blinkPosition(0, 1);
          break;
          case StateSetChn::SET_VOLUME:
            decrVolume(_fGen.settings.ch_1);
            showScreen2();
            blinkPosition(0, 2);
          break;
          case StateSetChn::SET_FREQ:
          break;
          case StateSetChn::SET_F1M:
          case StateSetChn::SET_F100K:
          case StateSetChn::SET_F10K:
          case StateSetChn::SET_F1K:
          case StateSetChn::SET_F100:
          case StateSetChn::SET_F10:
          case StateSetChn::SET_F1:
          case StateSetChn::SET_F01:
            decrFreq(_fGen.settings.ch_1);
          break;
          default:
          break;
        }
      break;
      case StateShow::SWEEP_SETTINGS:
        switch (_stateSetSwp)
        {
          case StateSetSwp::SET_MODE:
            prevSweepMode(_fGen.settings.swp);
            showScreen3();
            blinkPosition(0, 1);
          break;
          case StateSetSwp::SET_REP:
            toggleSweepRepeat(_fGen.settings.swp);
            showScreen3();
            blinkPosition(11, 1);
          break;
          case StateSetSwp::SET_TIME:
          break;
          case StateSetSwp::SET_10S:
          case StateSetSwp::SET_1S:
          case StateSetSwp::SET_100MS:
          case StateSetSwp::SET_10MS:
          case StateSetSwp::SET_1MS:
            decrSweepTime(_fGen.settings.swp);
          break;
          case StateSetSwp::SET_FREQSTEP:
          break;
          case StateSetSwp::SET_F100K:
          case StateSetSwp::SET_F10K:
          case StateSetSwp::SET_F1K:
          case StateSetSwp::SET_F100:
          case StateSetSwp::SET_F10:
          case StateSetSwp::SET_F1:
          case StateSetSwp::SET_F01:
            decrSwpFreqStep(_fGen.settings.swp);
          break;
          case StateSetSwp::SET_RUN:
            toggleSweepRunning(_fGen.settings.swp);
            showScreen3();
            blinkPosition(0, 0);
          break;
          default:
          break;
        }
      break;
    }
  }
}

/**
 * Handles click of rotary encoders push button
 */
void ControlKnob::onClick()
{
  //Serial.printf("onClick stateShow=%d, stateSetChn=%d, stateSetSwp=%d\r\n", (int)_stateShow, (int)_stateSetChn, (int)_stateSetSwp);
  switch (_stateShow)
    {
      case StateShow::BOTH_SETTINGS:
        switchChannel();
      break;
      case StateShow::CHN_0_SETTINGS:
        Serial.println("CHN_0_SETTINGS");
        switch (_stateSetChn)
        {
          case StateSetChn::SELECT_STATE:
          break;
          case StateSetChn::SET_MODE:
            Serial.println("SET_MODE"); 
            _stateSetChn = StateSetChn::SET_VOLUME;
            blinkPosition(0, 2);
          break;
          case StateSetChn::SET_VOLUME:
            _stateSetChn = StateSetChn::SET_FREQ;
            blinkPosition(0, 3);
          break;
          case StateSetChn::SET_FREQ:
            _stateSetChn = StateSetChn::SET_F1M;
            blinkPosition(11, 3);
          break;
          case StateSetChn::SET_F1M:
            _stateSetChn = StateSetChn::SET_F100K;
            blinkPosition(12, 3);
          break;
          case StateSetChn::SET_F100K:
            _stateSetChn = StateSetChn::SET_F10K;
            blinkPosition(13, 3);
          break;
          case StateSetChn::SET_F10K:
            _stateSetChn = StateSetChn::SET_F1K;
            blinkPosition(14, 3);
          break;
          case StateSetChn::SET_F1K:
            _stateSetChn = StateSetChn::SET_F100;
            blinkPosition(15, 3);
          break;
          case StateSetChn::SET_F100:
            _stateSetChn = StateSetChn::SET_F10;
            blinkPosition(16, 3);
          break;
          case StateSetChn::SET_F10:
            _stateSetChn = StateSetChn::SET_F1;
            blinkPosition(17, 3);
          break;
           case StateSetChn::SET_F1:
            _stateSetChn = StateSetChn::SET_F01;
            blinkPosition(19, 3);
          break;
          case StateSetChn::SET_F01:
            _stateSetChn = StateSetChn::SET_MODE;
            blinkPosition(0, 1);
          break; 
          default:
          break;        
        }
      break;
      case StateShow::CHN_1_SETTINGS:
        Serial.println("CHN_1_SETTINGS");
        switch (_stateSetChn)
        {
          case StateSetChn::SELECT_STATE:
          break;
          case StateSetChn::SET_MODE:
            Serial.println("SET_MODE"); 
            _stateSetChn = StateSetChn::SET_VOLUME;
            blinkPosition(0, 2);
          break;
          case StateSetChn::SET_VOLUME:
            _stateSetChn = StateSetChn::SET_FREQ;
            blinkPosition(0, 3);
          break;
          case StateSetChn::SET_FREQ:
            _stateSetChn = StateSetChn::SET_F1M;
            blinkPosition(11, 3);
          break;
          case StateSetChn::SET_F1M:
            _stateSetChn = StateSetChn::SET_F100K;
            blinkPosition(12, 3);
          break;
          case StateSetChn::SET_F100K:
            _stateSetChn = StateSetChn::SET_F10K;
            blinkPosition(13, 3);
          break;
          case StateSetChn::SET_F10K:
            _stateSetChn = StateSetChn::SET_F1K;
            blinkPosition(14, 3);
          break;
          case StateSetChn::SET_F1K:
            _stateSetChn = StateSetChn::SET_F100;
            blinkPosition(15, 3);
          break;
          case StateSetChn::SET_F100:
            _stateSetChn = StateSetChn::SET_F10;
            blinkPosition(16, 3);
          break;
          case StateSetChn::SET_F10:
            _stateSetChn = StateSetChn::SET_F1;
            blinkPosition(17, 3);
          break;
           case StateSetChn::SET_F1:
            _stateSetChn = StateSetChn::SET_F01;
            blinkPosition(19, 3);
          break;
          case StateSetChn::SET_F01:
            _stateSetChn = StateSetChn::SET_MODE;
            blinkPosition(0, 1);
          break; 
          default:
          break;        
        }      
      break;
      case StateShow::SWEEP_SETTINGS: 
        Serial.println("SWEEP_SETTINGS");
        switch (_stateSetSwp)
        {
          case StateSetSwp::SELECT_STATE:
          break;
          case StateSetSwp::SET_MODE:
            _stateSetSwp = StateSetSwp::SET_REP;
            blinkPosition(11, 1);
          break;
          case StateSetSwp::SET_REP:
            _stateSetSwp = StateSetSwp::SET_TIME;
            blinkPosition(0, 2);
          break;
          case StateSetSwp::SET_TIME:
            _stateSetSwp = StateSetSwp::SET_10S;
            blinkPosition(7, 2);
          break;
          case StateSetSwp::SET_10S:
            _stateSetSwp = StateSetSwp::SET_1S;
            blinkPosition(8, 2);
          break;
          case StateSetSwp::SET_1S:
            _stateSetSwp = StateSetSwp::SET_100MS;
            blinkPosition(9, 2);
          break;
          case StateSetSwp::SET_100MS:
            _stateSetSwp = StateSetSwp::SET_10MS;
            blinkPosition(10, 2);
          break;
          case StateSetSwp::SET_10MS:
            _stateSetSwp = StateSetSwp::SET_1MS;
            blinkPosition(11, 2);
          break;
          case StateSetSwp::SET_1MS:
            _stateSetSwp = StateSetSwp::SET_FREQSTEP;
            blinkPosition(0, 3);
          break;
          case StateSetSwp::SET_FREQSTEP:
            _stateSetSwp = StateSetSwp::SET_F100K;
            blinkPosition(7, 3);
          break;          
          case StateSetSwp::SET_F100K:
            _stateSetSwp = StateSetSwp::SET_F10K;
            blinkPosition(8, 3);
          break;
          case StateSetSwp::SET_F10K:
            _stateSetSwp = StateSetSwp::SET_F1K;
            blinkPosition(9, 3);
          break;
          case StateSetSwp::SET_F1K:
            _stateSetSwp = StateSetSwp::SET_F100;
            blinkPosition(10, 3);
          break;
          case StateSetSwp::SET_F100:
            _stateSetSwp = StateSetSwp::SET_F10;
            blinkPosition(11, 3);
          break;
          case StateSetSwp::SET_F10:
            _stateSetSwp = StateSetSwp::SET_F1;
            blinkPosition(12, 3);
          break;
          case StateSetSwp::SET_F1:
            _stateSetSwp = StateSetSwp::SET_F01;
            blinkPosition(14, 3);
          break;
          case StateSetSwp::SET_F01:
            _stateSetSwp = StateSetSwp::SET_RUN;
            //_fGen.setMode(MD_AD9833::MODE_OFF);
            blinkPosition(0, 0);
          break;
          case StateSetSwp::SET_RUN:
            _stateSetSwp = StateSetSwp::SET_MODE;
            blinkPosition(0, 1);
          break;
          default:
          break;
        }
      break;
      default:
      break;
    } 
}

/**
 * Handles long click of rotary encoders push button
 */
void ControlKnob::onLongClick()
{
  //Serial.printf("onLongClick stateShow=%d, stateSetChn=%d, stateSetSwp=%d\r\n", (int)_stateShow, (int)_stateSetChn, (int)_stateSetSwp);
  MD_AD9833::channel_t chn = _fGen.getActiveFrequency();
  ChannelSettings chnSettings = (chn == MD_AD9833::CHAN_0) ? _fGen.settings.ch_0 : _fGen.settings.ch_1;
  MD_AD9833::mode_t mode = _fGen.getMode();
  switch (_stateShow)
  {
    case StateShow::BOTH_SETTINGS:
      if (mode != MD_AD9833::MODE_OFF)
      {
        _fGen.setMode(MD_AD9833::MODE_OFF);
      }
      else
      {
        _fGen.setMode(chnSettings.mode);
      }
      
    break;
    case StateShow::CHN_0_SETTINGS:
      if (_stateSetChn == StateSetChn::SELECT_STATE)
      {
        _stateSetChn = StateSetChn::SET_MODE;
        blinkPosition(0, 1);
      }
      else
      {
        _stateSetChn = StateSetChn::SELECT_STATE;
        _stateShow = StateShow::CHN_0_SETTINGS;
        showScreen1();
      }
      
    break;
    case StateShow::CHN_1_SETTINGS:
      if (_stateSetChn == StateSetChn::SELECT_STATE)
      {
        _stateSetChn = StateSetChn::SET_MODE;
        blinkPosition(0, 1);
      }
      else
      {
        _stateSetChn = StateSetChn::SELECT_STATE;
        _stateShow = StateShow::CHN_1_SETTINGS;
        showScreen2();
      }
    break;
    case StateShow::SWEEP_SETTINGS:
      switch (_stateSetSwp)
      {
        case StateSetSwp::SELECT_STATE:
          Serial.println("StateSetSwp::SELECT_STATE");
          _stateSetSwp = StateSetSwp::SET_RUN;
          //_fGen.setMode(MD_AD9833::MODE_OFF);
          blinkPosition(0, 0);
        break;
        case StateSetSwp::SET_RUN:
          Serial.println("StateSetSwp::RUN");
          _stateSetSwp = StateSetSwp::SELECT_STATE;
          //_fGen.settings.swp.running = false;
          //_fGen.setMode(MD_AD9833::MODE_OFF);
          showScreen3();
        break;
        default:
          Serial.println("StateSetSwp::DEFAULT");
          _stateSetSwp = StateSetSwp::SET_RUN;
          //showScreen3();
          blinkPosition(0, 0);
        break;
      }
    break;
  }
}

/**
 * Handles double click of rotary encoders push button
 * Not used
 */
void ControlKnob::onDoubleClick()
{
  //Serial.printf("onDoubleClick stateShow=%d, stateSetChn=%d, stateSetSwp=%d\r\n", (int)_stateShow, (int)_stateSetChn, (int)_stateSetSwp);
}

/**
 * Blinks cursor at selected column/row position
 */
void ControlKnob::blinkPosition(uint8_t col, uint8_t row)
{
  _lcd.setCursor(col, row);
  _lcd.blink();
}

/**
 * Shows next screen on LCD
 */
void ControlKnob::nextScreen()
{
  ScreenFunc func = screenFunc[static_cast<int>(_stateShow++)];
  (this->*func)();
}

/**
 * Shows previous screen on LCD
 */
void ControlKnob::prevScreen()
{
  ScreenFunc func = screenFunc[static_cast<int>(_stateShow--)];
  Serial.println((int)_stateShow);
  (this->*func)();
}

/**
 * Activates settings of the selected channel for output
 */
void ControlKnob::setSettings(ChannelSettings &settings)
{
  _fGen.setActiveFrequency(settings.chn);
  _fGen.setFrequency(settings.chn, settings.frequency);
  _fGen.setMode(settings.mode);
  _fGen.setVolume(settings.volume);
}

/**
 * Shows settings of selected channel
 */
void ControlKnob::showSettings(ChannelSettings &settings)
{
  uint8_t chnX = (settings.chn == MD_AD9833::CHAN_0 ? 0 : 1);
  _lcd.clear();
  _lcd.noBlink();
  _lcd.printf("Channel    %d", chnX);

  switch (settings.mode)
  {
    case MD_AD9833::MODE_OFF: 
    break;
    case MD_AD9833::MODE_SINE:
      _lcd.setCursor(0 ,1);
      _lcd.print("Mode       Sine    ");
      _lcd.setCursor(0, 2);    
      _lcd.printf("Amplitude  %04.0f  %03d", settings.mVpp, settings.volume);
      _lcd.setCursor(0, 3);  
      _lcd.printf("Frequency  %09.1f", settings.frequency);
    break;
    case MD_AD9833::MODE_TRIANGLE:
      _lcd.setCursor(0 ,1);
      _lcd.print("Mode       Triangle");
      _lcd.setCursor(0, 2); 
      _lcd.printf("Amplitude  %04.0f  %03d", settings.mVpp, settings.volume);   
      _lcd.setCursor(0, 3);  
      _lcd.printf("Frequency  %09.1f", settings.frequency);
    break;
    case MD_AD9833::MODE_SQUARE1:
      _lcd.setCursor(0 ,1);
      _lcd.print("Mode       Square1 ");
      _lcd.setCursor(0, 2);    
      _lcd.print("Amplitude  max");
      _lcd.setCursor(0, 3);  
      _lcd.printf("Frequency  %09.1f", settings.frequency);
    break;
    case MD_AD9833::MODE_SQUARE2:
      _lcd.setCursor(0 ,1);
      _lcd.print("Mode       Square2 ");
      _lcd.setCursor(0, 2);    
      _lcd.print("Amplitude  max");
      _lcd.setCursor(0, 3);  
      _lcd.printf("Frequency  %09.1f", settings.frequency/2);
    break;
  }   
  _lcd.display();
}

/** 
 * Show settings of both channels.
 * The active channel is enclosed in <> like <Chan 0> or <Chan 1>
 */
void ControlKnob::showScreen0()
{
  //Serial.printf("showScreen0 stateShow=%d, StateSetChn=%d\r\n", static_cast<int>(_stateShow), static_cast<int>(_stateSetChn));
  _lcd.clear();
  _lcd.noBlink();
  if (_fGen.getActiveFrequency() == MD_AD9833::CHAN_0 )
  {
    _lcd.print("<Chan 0>  | Chan 1");
  }
  else
  {
    _lcd.print(" Chan 0   |<Chan 1>");
  }
  _lcd.setCursor(1, 1);
  switch (_fGen.settings.ch_0.mode)
  {
    case MD_AD9833::MODE_OFF: 
    break;
    case MD_AD9833::MODE_SINE:
      _lcd.setCursor(1, 1);
      _lcd.print("Sine     |");
      _lcd.setCursor(1, 2);
      _lcd.printf("%04.0f %03d |", _fGen.settings.ch_0.mVpp, _fGen.settings.ch_0.volume);
      _lcd.setCursor(0, 3);
      _lcd.printf("%09.1f |", _fGen.settings.ch_0.frequency);
    break;
    case MD_AD9833::MODE_TRIANGLE:
      _lcd.setCursor(1, 1);
      _lcd.print("Triangle |");
      _lcd.setCursor(1, 2);
      _lcd.printf("%04.0f %03d |", _fGen.settings.ch_0.mVpp, _fGen.settings.ch_0.volume);
      _lcd.setCursor(0, 3);
      _lcd.printf("%09.1f |", _fGen.settings.ch_0.frequency);
    break;
    case MD_AD9833::MODE_SQUARE1:
      _lcd.setCursor(1, 1);
      _lcd.print("Square1  |");
      _lcd.setCursor(1, 2);
      _lcd.printf("max      |");
      _lcd.setCursor(0, 3);
      _lcd.printf("%09.1f |", _fGen.settings.ch_0.frequency);
    break;
    case MD_AD9833::MODE_SQUARE2:
      _lcd.setCursor(1, 1);
      _lcd.print("Square2  |");
      _lcd.setCursor(1, 2);
      _lcd.printf("max      |");
      _lcd.setCursor(0, 3);
      _lcd.printf("%09.1f |", _fGen.settings.ch_0.frequency/2);
    break;
  }
  
  switch (_fGen.settings.ch_1.mode)
  {
    case MD_AD9833::MODE_OFF: 
    break;
    case MD_AD9833::MODE_SINE:
      _lcd.setCursor(12, 1);
      _lcd.print("Sine");
      _lcd.setCursor(12, 2);
      _lcd.printf("%04.0f %03d", _fGen.settings.ch_1.mVpp, _fGen.settings.ch_1.volume);
      _lcd.setCursor(11, 3);
      _lcd.printf("%09.1f", _fGen.settings.ch_1.frequency);
    break;
    case MD_AD9833::MODE_TRIANGLE:
      _lcd.setCursor(12, 1);
      _lcd.print("Triangle");
      _lcd.setCursor(12, 2);
      _lcd.printf("%04.0f %03d", _fGen.settings.ch_1.mVpp, _fGen.settings.ch_1.volume);
      _lcd.setCursor(11, 3);
      _lcd.printf("%09.1f", _fGen.settings.ch_1.frequency);
    break;
    case MD_AD9833::MODE_SQUARE1:
      _lcd.setCursor(12, 1);
      _lcd.print("Square1");
      _lcd.setCursor(12, 2);
      _lcd.printf("max");
      _lcd.setCursor(11, 3);
      _lcd.printf("%09.1f", _fGen.settings.ch_1.frequency);
    break;
    case MD_AD9833::MODE_SQUARE2:
      _lcd.setCursor(12, 1);
      _lcd.print("Square2");
      _lcd.setCursor(12, 2);
      _lcd.printf("max");
      _lcd.setCursor(11, 3);
      _lcd.printf("%09.1f", _fGen.settings.ch_1.frequency/2);
    break;
  }  
  _lcd.display();
}

/**
 * Shows settings of channel_0
 */
void ControlKnob::showScreen1()
{
  //Serial.printf("showScreen1 stateShow=%d, StateSetChn=%d\r\n", static_cast<int>(_stateShow), static_cast<int>(_stateSetChn));
  showSettings(_fGen.settings.ch_0);
}

/**
 * Shows settings of channel_1
 */
void ControlKnob::showScreen2()
{
  //Serial.printf("showScreen2 stateShow=%d, StateSetChn=%d\r\n", static_cast<int>(_stateShow), static_cast<int>(_stateSetChn));
  showSettings(_fGen.settings.ch_1);
}

/**
 * Shows sweep settings
 */
void ControlKnob::showScreen3()
{
  //Serial.printf("showScreen3 stateShow=%d, stateSetChn=%d, stateSetSwp=%d\r\n", (int)_stateShow, (int)_stateSetChn, (int)_stateSetSwp);
  _lcd.clear();
  _lcd.noBlink();

  _lcd.print("Sweep  ");
  _fGen.settings.swp.running == false ? _lcd.print("stopped") : _lcd.print("started");
  _lcd.setCursor(0, 1);

  switch (_fGen.settings.swp.mode)
  {
    case SweepMode::CH_0_1:
    _lcd.print("Mode   /");
    break;
    case SweepMode::CH_1_0:
    _lcd.print("Mode   "); _lcd.write(char(1)); 
    break;
    case SweepMode::CH_0_1_0:
    _lcd.print("Mode   /"); _lcd.write(char(1));
    break;
    case SweepMode::CH_1_0_1:
    _lcd.print("Mode   "); _lcd.write(char(1)); _lcd.print("/");
    break;
    default:
    break;
  } 
  _lcd.setCursor(11, 1); _lcd.write(char(2));
  _lcd.setCursor(13, 1);
  _fGen.settings.swp.repeat == true ? _lcd.print("cyclic") : _lcd.print("once");
  _lcd.setCursor(0, 2);
  _lcd.printf("Time   %05d ms", _fGen.settings.swp.time);
  _lcd.setCursor(0, 3);
  _lcd.printf("Step   %08.1f Hz", _fGen.settings.swp.freqstep);
  _lcd.display();
}

/**
 * Selects frequency of channel 0 or 
 * channel 1 for output
 */
void ControlKnob::switchChannel()
{
  MD_AD9833::channel_t channel = _fGen.getActiveFrequency();

  switch (channel)
  {
    case MD_AD9833::CHAN_0:
      _fGen.activateChannelSettings(MD_AD9833::CHAN_1);
    break;
    case MD_AD9833::CHAN_1:
      _fGen.activateChannelSettings(MD_AD9833::CHAN_0);
    break;
  }
  showScreen0();
}

/**
 * Switches to next wave form for selected channel
 */
void ControlKnob::nextMode(ChannelSettings &settings)
{
  switch (settings.mode)
  {
    case MD_AD9833::MODE_OFF:
    break;
    case MD_AD9833::MODE_SINE:
      settings.mode = MD_AD9833::MODE_TRIANGLE;
      _fGen.setMode(MD_AD9833::MODE_TRIANGLE);
    break; 
      case MD_AD9833::MODE_TRIANGLE:
        settings.mode = MD_AD9833::MODE_SQUARE1;
        _fGen.setMode(MD_AD9833::MODE_SQUARE1);  
    break;
    case MD_AD9833::MODE_SQUARE1:
      settings.mode = MD_AD9833::MODE_SQUARE2;
      _fGen.setMode(MD_AD9833::MODE_SQUARE2);
    break;
    case MD_AD9833::MODE_SQUARE2:
      settings.mode = MD_AD9833::MODE_SINE;
      _fGen.setMode(MD_AD9833::MODE_SINE);   
    break; 
    default:
      Serial.println("Invalid mode");
    break;
  }
}

/**
 * Switches to previous wave form for selected channel
 */
void ControlKnob::prevMode(ChannelSettings &settings)
{
  switch (settings.mode)
  {
    case MD_AD9833::MODE_OFF:
    break;
    case MD_AD9833::MODE_SINE:
      settings.mode = MD_AD9833::MODE_SQUARE2;
      _fGen.setMode(MD_AD9833::MODE_SQUARE2);
    break;
    case MD_AD9833::MODE_SQUARE2:
      settings.mode = MD_AD9833::MODE_SQUARE1;
      _fGen.setMode(MD_AD9833::MODE_SQUARE1);  
    break;
    case MD_AD9833::MODE_SQUARE1:
      settings.mode = MD_AD9833::MODE_TRIANGLE;
      _fGen.setMode(MD_AD9833::MODE_TRIANGLE);
    break;
    case MD_AD9833::MODE_TRIANGLE:
      settings.mode = MD_AD9833::MODE_SINE;
      _fGen.setMode(MD_AD9833::MODE_SINE);    
    break;
    default:
      Serial.println("Invalid mode");
    break;
  }
}

/**
 * Increments volume by 1 step and wrappes around to 0 at 255
 */
void ControlKnob::incrVolume(ChannelSettings &settings)
{
  settings.volume == 255 ? settings.volume = 0 : settings.volume++;
  settings.mVpp = _fGen.convertVolumeTomVpp(settings.volume);
  _fGen.setVolume(settings.volume);
}

/**
 * Decrements volume by 1 step and wrappes around to 255 at 0
 */
void ControlKnob::decrVolume(ChannelSettings &settings)
{
  settings.volume == 0 ? settings.volume = 255 : settings.volume--;
  settings.mVpp = _fGen.convertVolumeTomVpp(settings.volume);
  _fGen.setVolume(settings.volume);
}

/**
 * Increments selected frequency digit 
 */
void ControlKnob::incrFreq(ChannelSettings &settings)
{
  switch (_stateSetChn)
  {
    case StateSetChn::SET_F1M:
      incrFreqDigit(settings, 0, 1000000, 3);
    break;
    case StateSetChn::SET_F100K:
      incrFreqDigit(settings, 1, 100000, 3);
    break;
    case StateSetChn::SET_F10K:
      incrFreqDigit(settings, 2, 10000, 3);
    break;
    case StateSetChn::SET_F1K:
      incrFreqDigit(settings, 3, 1000, 3);
    break;
    case StateSetChn::SET_F100:
      incrFreqDigit(settings, 4, 100, 3);
    break;
    case StateSetChn::SET_F10:
      incrFreqDigit(settings, 5, 10, 3);
    break;
    case StateSetChn::SET_F1:
      incrFreqDigit(settings, 6, 1, 3);
    break;
    case StateSetChn::SET_F01:
      incrFreqDigit(settings, 8, 0.1, 3);
    break;
    default:
    break;
  }
}

/**
 * Decrements selected frequency digit 
 */
void ControlKnob::decrFreq(ChannelSettings &settings)
{
  switch (_stateSetChn)
  {
    case StateSetChn::SET_F1M:
      decrFreqDigit(settings, 0, 1000000, 3);
    break;
    case StateSetChn::SET_F100K:
      decrFreqDigit(settings, 1, 100000, 3);
    break;
    case StateSetChn::SET_F10K:
      decrFreqDigit(settings, 2, 10000, 3);
    break;
    case StateSetChn::SET_F1K:
      decrFreqDigit(settings, 3, 1000, 3);
    break;
    case StateSetChn::SET_F100:
      decrFreqDigit(settings, 4, 100, 3);
    break;
    case StateSetChn::SET_F10:
      decrFreqDigit(settings, 5, 10, 3);
    break;
    case StateSetChn::SET_F1:
      decrFreqDigit(settings, 6, 1, 3);
    break;
    case StateSetChn::SET_F01:
      decrFreqDigit(settings, 8, 0.1, 3);
    break;
    default:
    break;
  }
}

/**
 * Increments selected frequency digit and 
 * updates LCD accordingly
 */
void ControlKnob::incrFreqDigit(ChannelSettings &settings, uint8_t digit, double multiplier, uint8_t rowLCD)
{
  const uint8_t digitPosition = digit + 11;
  uint8_t digitOld, digitNew = 0;
  char digits[10];
  sprintf(digits, "%09.1f", settings.frequency);
  digitOld = digits[digit] - 48;
  digitNew = (digitOld + 1) % 10;
  settings.frequency += (digitNew - digitOld) * multiplier;
  _fGen.setFrequency(settings.chn, settings.frequency);
  _lcd.setCursor(digitPosition, rowLCD);
  _lcd.print(digitNew);
  _lcd.setCursor(digitPosition, rowLCD);
  _lcd.display();  
}

/**
 * Decrements selected frequency digit and 
 * updates LCD accordingly
 */
void ControlKnob::decrFreqDigit(ChannelSettings &settings, uint8_t digit, double multiplier, uint8_t rowLCD)
{
  const uint8_t digitPosition = digit + 11;
  uint8_t digitOld, digitNew = 0;
  char digits[10];
  sprintf(digits, "%09.1f", settings.frequency);
  digitOld = digits[digit] - 48;
  digitNew = digitOld == 0 ? 9 : digitOld - 1;
  Serial.printf("digitOld = %d, digitNew = %d\r\n", digitOld, digitNew);
  settings.frequency += (digitNew - digitOld) * multiplier;
  _fGen.setFrequency(settings.chn, settings.frequency);
  _lcd.setCursor(digitPosition, rowLCD);
  _lcd.print(digitNew);
  _lcd.setCursor(digitPosition, rowLCD);
  _lcd.display();  
}

/**
 * Selects next sweep mode and wrappes around
 */
void ControlKnob::nextSweepMode(SweepSettings &settings)
{
  switch (settings.mode)
  {
    case SweepMode::CH_0_1:
      settings.mode = SweepMode::CH_1_0;
      settings.fsweep = _fGen.settings.ch_1.frequency;
    break; 
    case SweepMode::CH_1_0:
      settings.mode = SweepMode::CH_0_1_0;
      settings.fsweep = _fGen.settings.ch_0.frequency; 
    break;
    case SweepMode::CH_0_1_0:
      settings.mode = SweepMode::CH_1_0_1;
      settings.fsweep = _fGen.settings.ch_1.frequency;
    break;
    case SweepMode::CH_1_0_1:
      settings.mode = SweepMode::CH_0_1;
      settings.fsweep = _fGen.settings.ch_0.frequency;   
    break;
    default:
      Serial.println("  Invalid sweep mode");
    break; 
  }
}

/**
 * Selects previous sweep mode and wrappes around
 */
void ControlKnob::prevSweepMode(SweepSettings &settings)
{
  switch (settings.mode)
  {
    case SweepMode::CH_0_1:
      settings.mode = SweepMode::CH_1_0_1;
      settings.fsweep = _fGen.settings.ch_1.frequency;
    break; 
    case SweepMode::CH_1_0:
      settings.mode = SweepMode::CH_0_1;
      settings.fsweep = _fGen.settings.ch_0.frequency; 
    break;
    case SweepMode::CH_0_1_0:
      settings.mode = SweepMode::CH_1_0;
      settings.fsweep = _fGen.settings.ch_1.frequency;
    break;
    case SweepMode::CH_1_0_1:
      settings.mode = SweepMode::CH_0_1_0;
      settings.fsweep = _fGen.settings.ch_0.frequency;   
    break; 
  }
}

/**
 * Toggles wether sweep is repeated ore not
 */
void ControlKnob::toggleSweepRepeat(SweepSettings &settings)
{
  settings.repeat = (settings.repeat == false) ? true : false;
}

/**
 * Toggles sweep on or off
 * Allows stopping a long running sweep
 */
void ControlKnob::toggleSweepRunning(SweepSettings &settings)
{
  if (settings.running)
  {
    settings.running = false;
    // Stop timer
    timerAlarmDisable(timer);
    _fGen.setMode(MD_AD9833::MODE_OFF);
  }
  else
  {
    settings.running = true;
    settings.activeChannel = MD_AD9833::CHAN_0;
    _fGen.setActiveFrequency(settings.activeChannel);
    timerAlarmWrite(timer, _fGen.settings.swp.time * 10.0, true);
    // Start an alarm
    timerAlarmEnable(timer);
    switch (settings.mode)
    {
      case SweepMode::CH_0_1:
      case SweepMode::CH_0_1_0:
        _fGen.setFrequency(settings.activeChannel, _fGen.settings.ch_0.frequency);
        _fGen.settings.swp.fsweep = _fGen.settings.ch_0.frequency;
      break;
      case SweepMode::CH_1_0:
      case SweepMode::CH_1_0_1:
        _fGen.setFrequency(settings.activeChannel, _fGen.settings.ch_1.frequency);
        _fGen.settings.swp.fsweep = _fGen.settings.ch_1.frequency;
      break;
      default:
      break;
    }
    _fGen.setMode(_fGen.settings.ch_0.mode);
    _fGen.settings.swp.firstslope = true;
    _fGen.settings.swp.done = false;
  } 
}

/**
 * Increments duration of 1 frequency step
 */
void ControlKnob::incrSweepTime(SweepSettings &settings)
{
  switch (_stateSetSwp)
  {
    case StateSetSwp::SET_10S:
      incrSwpTimeDigit(settings, 0, 10000, 2);
    break;
    case StateSetSwp::SET_1S:
      incrSwpTimeDigit(settings, 1, 1000, 2);
    break;
    case StateSetSwp::SET_100MS:
      incrSwpTimeDigit(settings, 2, 100, 2);
    break;
    case StateSetSwp::SET_10MS:
      incrSwpTimeDigit(settings, 3, 10, 2);
    break;
    case StateSetSwp::SET_1MS:
      incrSwpTimeDigit(settings, 4, 1, 2);
    break;
    default:
    break;
  }
  timerAlarmWrite(timer, settings.time * 10.0, true);
}

/**
 * Decrements duration of 1 frequency step
 */
void ControlKnob::decrSweepTime(SweepSettings &settings)
{
  switch (_stateSetSwp)
  {
    case StateSetSwp::SET_10S:
      decrSwpTimeDigit(settings, 0, 10000, 2);
    break;
    case StateSetSwp::SET_1S:
      decrSwpTimeDigit(settings, 1, 1000, 2);
    break;
    case StateSetSwp::SET_100MS:
      decrSwpTimeDigit(settings, 2, 100, 2);
    break;
    case StateSetSwp::SET_10MS:
      decrSwpTimeDigit(settings, 3, 10, 2);
    break;
    case StateSetSwp::SET_1MS:
      decrSwpTimeDigit(settings, 4, 1, 2);
    break;
    default:
    break;
  }
  timerAlarmWrite(timer, settings.time * 10.0, true);
}

/**
 * Increments selected sweep duration digit and updates LCD accordingly
 * Prevents duration becomming 0 
 */
void ControlKnob::incrSwpTimeDigit(SweepSettings &settings, uint8_t digit, uint32_t multiplier, uint8_t rowLCD)
{
  const uint8_t digitPosition = digit + 7;
  uint8_t digitOld, digitNew = 0;
  char digits[10];
  sprintf(digits, "%05d", settings.time);
  digitOld = digits[digit] - 48;
  digitNew = (digitOld + 1) % 10;
  settings.time += (digitNew - digitOld) * multiplier;
  if (settings.time < 1)
  {
    digitNew = 1;
    settings.time = digitNew * multiplier;
  }
  _lcd.setCursor(digitPosition, rowLCD);
  _lcd.print(digitNew);
  _lcd.setCursor(digitPosition, rowLCD);
  _lcd.display();    
}

/**
 * Decrements selected sweep duration digit and updates LCD accordingly
 * Prevents duration becomming 0 
 */
void ControlKnob::decrSwpTimeDigit(SweepSettings &settings, uint8_t digit, uint32_t multiplier, uint8_t rowLCD)
{
  const uint8_t digitPosition = digit + 7;
  uint8_t digitOld, digitNew = 0;
  char digits[10];
  sprintf(digits, "%05d", settings.time);
  digitOld = digits[digit] - 48;
  digitNew = digitOld == 0 ? 9 : digitOld - 1;
  settings.time += (digitNew - digitOld) * multiplier;
  if (settings.time < 1)
  {
    digitNew = 1;
    settings.time = digitNew * multiplier;
  }
  _lcd.setCursor(digitPosition, rowLCD);
  _lcd.print(digitNew);
  _lcd.setCursor(digitPosition, rowLCD);
  _lcd.display(); 
}

/**
 * Increments sweep frequency step
 */
void ControlKnob::incrSwpFreqStep(SweepSettings &settings)
{
  //Serial.printf("incrSweepFreqStep stateSwp=%d\r\n", (int)_stateSetSwp );
  switch (_stateSetSwp)
  {
    case StateSetSwp::SET_F100K:
      incrSwpFreqStepDigit(settings, 0, 100000, 3);
    break;
    case StateSetSwp::SET_F10K:
      incrSwpFreqStepDigit(settings, 1, 10000, 3);
    break;
    case StateSetSwp::SET_F1K:
      incrSwpFreqStepDigit(settings, 2, 1000, 3);
    break;
    case StateSetSwp::SET_F100:
      incrSwpFreqStepDigit(settings, 3, 100, 3);
    break;
    case StateSetSwp::SET_F10:
      incrSwpFreqStepDigit(settings, 4, 10, 3);
    break;
    case StateSetSwp::SET_F1:
      incrSwpFreqStepDigit(settings, 5, 1, 3);
    break;
    case StateSetSwp::SET_F01:
      incrSwpFreqStepDigit(settings, 7, 0.1, 3);
    break;
    default:
    break;
  }
}

/**
 * Decrements sweep frequency step
 */
void ControlKnob::decrSwpFreqStep(SweepSettings &settings)
{
  //Serial.printf("decrSweepFreqStep stateSwp=%d\r\n", (int)_stateSetSwp );
  switch (_stateSetSwp)
  {
    case StateSetSwp::SET_F100K:
      decrSwpFreqStepDigit(settings, 0, 100000, 3);
    break;
    case StateSetSwp::SET_F10K:
      decrSwpFreqStepDigit(settings, 1, 10000, 3);
    break;
    case StateSetSwp::SET_F1K:
      decrSwpFreqStepDigit(settings, 2, 1000, 3);
    break;
    case StateSetSwp::SET_F100:
      decrSwpFreqStepDigit(settings, 3, 100, 3);
    break;
    case StateSetSwp::SET_F10:
      decrSwpFreqStepDigit(settings, 4, 10, 3);
    break;
    case StateSetSwp::SET_F1:
      decrSwpFreqStepDigit(settings, 5, 1, 3);
    break;
    case StateSetSwp::SET_F01:
      decrSwpFreqStepDigit(settings, 7, 0.1, 3);
    break;
    default:
    break;
  }  
}

/**
 * Increments selected sweep frequency digit and updates LCD accordingly
 */
void ControlKnob::incrSwpFreqStepDigit(SweepSettings &settings, uint8_t digit, double multiplier, uint8_t rowLCD)
{
  const uint8_t digitPosition = digit + 7;
  uint8_t digitOld, digitNew = 0;
  char digits[10];
  sprintf(digits, "%08.1f", settings.freqstep);
  digitOld = digits[digit] - 48;
  digitNew = (digitOld + 1) % 10;
  settings.freqstep += (digitNew - digitOld) * multiplier;
  _lcd.setCursor(digitPosition, rowLCD);
  _lcd.print(digitNew);
  _lcd.setCursor(digitPosition, rowLCD);
  _lcd.display();  
}

/**
 * Decrements selected sweep frequency digit and updates LCD accordingly
 */
void ControlKnob::decrSwpFreqStepDigit(SweepSettings &settings, uint8_t digit, double multiplier, uint8_t rowLCD)
{
  const uint8_t digitPosition = digit + 7;
  uint8_t digitOld, digitNew = 0;
  char digits[10];
  sprintf(digits, "%08.1f", settings.freqstep);
  digitOld = digits[digit] - 48;
  digitNew = digitOld == 0 ? 9 : digitOld - 1;
  Serial.printf("digitOld = %d, digitNew = %d\r\n", digitOld, digitNew);
  settings.freqstep += (digitNew - digitOld) * multiplier;
  _lcd.setCursor(digitPosition, rowLCD);
  _lcd.print(digitNew);
  _lcd.setCursor(digitPosition, rowLCD);
  _lcd.display();
}

/**
 * Enables sweeping of channel_0 frequency
 */
void ControlKnob::runSweep()
{
  switch (_fGen.settings.swp.mode)
  {
    case SweepMode::CH_0_1:
      //Serial.printf("/ fsweep=%f, f0=%f, f1=%f\r\n", _fGen.settings.swp.fsweep, _fGen.settings.ch_0.frequency, _fGen.settings.ch_1.frequency);
      if (_fGen.settings.swp.fsweep <= _fGen.settings.ch_1.frequency)
      {
        // if timer has fired
        if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE)
        {
          portENTER_CRITICAL(&timerMux);
          _fGen.setFrequency(_fGen.settings.swp.activeChannel, _fGen.settings.swp.fsweep);
          _fGen.setActiveFrequency(_fGen.settings.swp.activeChannel);
          _fGen.settings.swp.fsweep += _fGen.settings.swp.freqstep;
          _fGen.settings.swp.activeChannel = (_fGen.settings.swp.activeChannel == MD_AD9833::CHAN_0) ? MD_AD9833::CHAN_1 : MD_AD9833::CHAN_0;       
          portEXIT_CRITICAL(&timerMux);
        }
      }
      else
      {
        _fGen.settings.swp.fsweep = _fGen.settings.ch_0.frequency;  // needed for cyclic sweep
        _fGen.settings.swp.done = true;
      }   
    break;

    case SweepMode::CH_1_0:
      //Serial.printf("\\ fsweep=%f, f0=%f, f1=%f\r\n", _fGen.settings.swp.fsweep, _fGen.settings.ch_0.frequency, _fGen.settings.ch_1.frequency);
      if (_fGen.settings.swp.fsweep >= _fGen.settings.ch_0.frequency)
      {
        // if timer has fired
        if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE)
        {
          portENTER_CRITICAL(&timerMux);
          _fGen.setFrequency(_fGen.settings.swp.activeChannel, _fGen.settings.swp.fsweep);
          _fGen.setActiveFrequency(_fGen.settings.swp.activeChannel);
          _fGen.settings.swp.fsweep -= _fGen.settings.swp.freqstep;
          _fGen.settings.swp.activeChannel = (_fGen.settings.swp.activeChannel == MD_AD9833::CHAN_0) ? MD_AD9833::CHAN_1 : MD_AD9833::CHAN_0;       
          portEXIT_CRITICAL(&timerMux);
        }
      }
      else
      {
        _fGen.settings.swp.fsweep = _fGen.settings.ch_1.frequency;
        _fGen.settings.swp.done = true;
      }
    break;

    case SweepMode::CH_0_1_0:
      //Serial.printf("/\\ fsweep=%f, f0=%f, f1=%f\r\n", _fGen.settings.swp.fsweep, _fGen.settings.ch_0.frequency, _fGen.settings.ch_1.frequency);
      if (_fGen.settings.swp.fsweep <= _fGen.settings.ch_1.frequency && _fGen.settings.swp.firstslope)
      {
        // if timer has fired
        if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE)
        {
          portENTER_CRITICAL(&timerMux);
          _fGen.setFrequency(_fGen.settings.swp.activeChannel, _fGen.settings.swp.fsweep);
          _fGen.setActiveFrequency(_fGen.settings.swp.activeChannel);
          _fGen.settings.swp.fsweep += _fGen.settings.swp.freqstep;
          _fGen.settings.swp.activeChannel = (_fGen.settings.swp.activeChannel == MD_AD9833::CHAN_0) ? MD_AD9833::CHAN_1 : MD_AD9833::CHAN_0;       
          portEXIT_CRITICAL(&timerMux);
        }
      }
      else
      { // max. frequency reached, first slope done, now reset flag 
        if (_fGen.settings.swp.firstslope)
        {
          _fGen.settings.swp.firstslope = false;
        }
        else
        { // do 2nd slope
          if (_fGen.settings.swp.fsweep >= _fGen.settings.ch_0.frequency)
          {
            // if timer has fired
            if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE)
            {
              portENTER_CRITICAL(&timerMux);
              _fGen.setFrequency(_fGen.settings.swp.activeChannel, _fGen.settings.swp.fsweep);
              _fGen.setActiveFrequency(_fGen.settings.swp.activeChannel);
              _fGen.settings.swp.fsweep -= _fGen.settings.swp.freqstep;
              _fGen.settings.swp.activeChannel = (_fGen.settings.swp.activeChannel == MD_AD9833::CHAN_0) ? MD_AD9833::CHAN_1 : MD_AD9833::CHAN_0;       
              portEXIT_CRITICAL(&timerMux);
            }
          }
          else
          { // min. frequency reached
            _fGen.settings.swp.done = true;
            _fGen.settings.swp.firstslope = true;  // set flag for cyclic sweep
          }
        }
      }
    break;
    case SweepMode::CH_1_0_1:
      //Serial.printf("\\/\\ fsweep=%f, f0=%f, f1=%f\r\n", _fGen.settings.swp.fsweep, _fGen.settings.ch_0.frequency, _fGen.settings.ch_1.frequency);
      if (_fGen.settings.swp.fsweep >= _fGen.settings.ch_0.frequency && _fGen.settings.swp.firstslope)
      {
        // if timer has fired
        if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE)
        {
          portENTER_CRITICAL(&timerMux);
          _fGen.setFrequency(_fGen.settings.swp.activeChannel, _fGen.settings.swp.fsweep);
          _fGen.setActiveFrequency(_fGen.settings.swp.activeChannel);
          _fGen.settings.swp.fsweep -= _fGen.settings.swp.freqstep;
          _fGen.settings.swp.activeChannel = (_fGen.settings.swp.activeChannel == MD_AD9833::CHAN_0) ? MD_AD9833::CHAN_1 : MD_AD9833::CHAN_0;       
          portEXIT_CRITICAL(&timerMux);
        }
      }
      else
      { // min. frequency reached, first slope done, now reset flag
        if (_fGen.settings.swp.firstslope)
        {
          _fGen.settings.swp.firstslope = false;
        }
        else
        { // do 2nd slope
          if (_fGen.settings.swp.fsweep <= _fGen.settings.ch_1.frequency)
          {
            // if timer has fired
            if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE)
            {
              portENTER_CRITICAL(&timerMux);
              _fGen.setFrequency(_fGen.settings.swp.activeChannel, _fGen.settings.swp.fsweep);
              _fGen.setActiveFrequency(_fGen.settings.swp.activeChannel);
              _fGen.settings.swp.fsweep += _fGen.settings.swp.freqstep;
              _fGen.settings.swp.activeChannel = (_fGen.settings.swp.activeChannel == MD_AD9833::CHAN_0) ? MD_AD9833::CHAN_1 : MD_AD9833::CHAN_0;       
              portEXIT_CRITICAL(&timerMux);
            }
          }
          else
          { // min frequency reached
            _fGen.settings.swp.done = true;
            _fGen.settings.swp.firstslope = true;  // set flag for cyclic sweep
          }
        }  
      }
    break;
    default:
    break;
  }
  if (_fGen.settings.swp.repeat == false && _fGen.settings.swp.done)
  {
    toggleSweepRunning(_fGen.settings.swp);
    showScreen3();
    blinkPosition(0, 0);
  }
}