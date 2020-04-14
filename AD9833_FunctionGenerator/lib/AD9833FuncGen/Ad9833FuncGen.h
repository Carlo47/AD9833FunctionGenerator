#include <SPI.h>
#include <MD_AD9833.h>

#ifndef AD9833FUNCGEN_H
#define AD9833FUNCGEN_H  

#define MCP_WRITE     0b00010001

typedef struct
{
  MD_AD9833::channel_t chn;
  MD_AD9833::mode_t mode;
  double   frequency;
  uint16_t phase;
  uint8_t  volume;  // 0..255, range of digital potentiometer. Beyond 210 greater distortions occur
  float    mVpp;    // Uout = 14.712 x volume + 44.11 
} ChannelSettings;

enum class SweepMode {CH_0_1, CH_1_0, CH_0_1_0, CH_1_0_1};

typedef struct
{
  SweepMode mode;
  uint32_t time;
  double   fsweep;
  double   freqstep;
  bool     repeat;
  bool     running;
  bool     done;
  bool     firstslope;
  MD_AD9833::channel_t activeChannel;
} SweepSettings;

typedef struct
{
  ChannelSettings ch_0;
  ChannelSettings ch_1;
  SweepSettings   swp;
} AD9833Settings;

class AD9833FuncGen: public MD_AD9833
{
  public:
    AD9833FuncGen(uint8_t pinFsync, uint8_t pinCsDpot) : MD_AD9833(pinFsync), _pinFsync(pinFsync), _pinCsDpot(pinCsDpot)
      {
        pinMode(_pinCsDpot, OUTPUT);    
        digitalWrite(_pinCsDpot, HIGH); // Disable chip select of digital potentiometer
        MD_AD9833::begin();             // Initialize base class
      }
    void setup();
    void setVolume(uint8_t value);
    float convertVolumeTomVpp(uint8_t volume);
    void activateChannelSettings(MD_AD9833::channel_t chn);
    AD9833Settings settings;  // Allow direct access to settinghs

  private:
    void MCP41xxxWrite(uint8_t value, uint8_t pinCsDpot);
    uint8_t _pinFsync;
    uint8_t _pinCsDpot;    
};

#endif