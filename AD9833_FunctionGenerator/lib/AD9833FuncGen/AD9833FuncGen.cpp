#include "AD9833FuncGen.h"

/**
 * Set initial values of both AD9833 channels 
 * and set channel_0 as active 
 */
void AD9833FuncGen::setup()
{ 
  //Settings channel 0
  settings.ch_0.chn       = MD_AD9833::CHAN_0;
  settings.ch_0.mode      = MD_AD9833::MODE_SINE;
  settings.ch_0.frequency = 415.3;
  settings.ch_0.phase     = getPhase(MD_AD9833::CHAN_0);
  settings.ch_0.volume    = 99;  // 1500 mVpp
  settings.ch_0.mVpp      = convertVolumeTomVpp(settings.ch_0.volume);

  //Settings channel 1
  settings.ch_1.chn       = MD_AD9833::CHAN_1;
  settings.ch_1.mode      = MD_AD9833::MODE_TRIANGLE;
  settings.ch_1.frequency = 554.4;
  settings.ch_1.phase     = getPhase(MD_AD9833::CHAN_1);
  settings.ch_1.volume    = 65; // 1000 mVpp
  settings.ch_1.mVpp      = convertVolumeTomVpp(settings.ch_1.volume);

  //Settings sweep
  settings.swp.mode = SweepMode::CH_0_1;
  settings.swp.repeat = false;
  settings.swp.running = false;
  settings.swp.done = false;
  settings.swp.firstslope = true;
  settings.swp.time = 10;
  settings.swp.fsweep = settings.ch_0.frequency;
  settings.swp.freqstep = 1.0;

  activateChannelSettings(MD_AD9833::CHAN_0);
}

/**
 * Activates stored settings for the selected channel 
 */
void AD9833FuncGen::activateChannelSettings(MD_AD9833::channel_t chn)
{
  ChannelSettings &s = (chn == MD_AD9833::CHAN_0) ? settings.ch_0 : settings.ch_1;
  setActiveFrequency(chn);
  setMode(s.mode);
  setFrequency(chn, s.frequency);
  setVolume(s.volume); 
}

/**
 * Sets output amplitude by setting the value of the digital potentiometer
 */
void AD9833FuncGen::setVolume(uint8_t value)
{
  MCP41xxxWrite(value, _pinCsDpot);
}

/**
 * Converts the value 0..255 of the digital potentiometer
 * to milli volts measured on output of OPAMP.
 * Formula is derived from a series of measurements
 * (Trendline from Excel table)
 */
float AD9833FuncGen::convertVolumeTomVpp(uint8_t volume)
{ 
  return 14.712 * volume + 44.11;  
}

/**
 * Write a value (0..255) to the digital potentiometer MCP41xxx
 */
void AD9833FuncGen::MCP41xxxWrite(uint8_t value, uint8_t pinCS) 
{
  digitalWrite(pinCS, LOW);  // Begin transfer
  SPI.transfer(MCP_WRITE);   // Write the command
  SPI.transfer(value);       // Write the potentiometer value
  digitalWrite(pinCS, HIGH); // End transfer 
}
