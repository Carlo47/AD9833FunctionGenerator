/**
 * Sketch     AD9833FunctionGenerator.cpp
 * Author     2019-02-15 Ch.Geiser
 * Purpose    Shows the use of an AD9833 breakout bord as DDS function generator
 *            Output frequency and waveform are set on AD9833
 *            Output amplitude is controlled by means of the digital potentiometer MCP41010
 *            which controls the OPAMP AD8051 in 255 steps
 *            AD9833 and MCP41010 have SPI interface
 * 
 * 
 * Features   Frequency     0.1 .. 9'999'999.9 Hz in steps of 0.1 Hz
 *            Waveforms     Sine, Triangle, Square1, Square2 with half the frequency
 *            Sweep         From channel_1 frequency to channel_2 frequency
 *            Sweep step    0.1 .. 99'999.9 Hz
 *            Step time     1 .. 99'999 ms
 * 
 *            Sweep         stopped / started
 *             
 *            Mode          /    Sweep from chn_0 to chn_1 frequency (rising slope)
 *          
 *                          \    Sweep from chn_0 to chn_1 frequency (falling slope)
 *          
 *                          /\   Sweep from chn_0 to chn_1 to chn_0 frequency (rising then falling slope)
 *            
 *                          \/   Sweep from chn_0 to chn_1 to chn_0 frequency (falling then rising slope)
 *                           .--.
 *                          |    v   Sweep once / cyclic
 *                           `--'
 *                   
 *       
 * Board      DoIt ESP32 DevKit V1
 * 
 *                      USB                            .----------- 
 *                   .--I I--.                D27  <---| CLK
 *              3V3 -|  ```  |- Vin           D26  <---| DT   Rotary
 *              GND -|       |- GND           D25  <---| SW   Encoder 
 *              D15 -| ESP32 |- D13           3.3V <---| +    with
 *    DPOT CS   D2  -| DevKit|- D12           GND  <---| GND  Pusbutton 
 *              D4  -| V1    |- D14                    `-----------    
 *              RX2 -|       |- D27                    .-----------  
 *              TX2 -|       |- D26           D2   <---| CS
 *   AD9833 CS  D5  -|       |- D25           D23  <---| DAT  DDS Breakout Board 
 *   AD9833 CLK D18 -|       |- D33           D18  <---| CLK  with
 *              D19 -|       |- D32           D5   <---| FSY  AD9833   DDS
 *              D21 -|       |- D35           GND  <---| GND  MCP41010 DPOT
 *              RX0 -|       |- D34           3.3V <---| Vcc  AD8051   OPAMP
 *              TX0 -|       |- VN                     `-----------    
 *              D22 -|       |- VP                  
 *   AD9833 DAT D23 -|       |- EN
 *                   `-------`
 *                  
 * Refernces  https://www.best-microcontroller-projects.com/ad9833.html
 *            https://www.homemade-circuits.com/using-digital-potentiometer-mcp41xx-with-arduino/
 *            https://github.com/MajicDesigns/MD_AD9833
 *
 * Remarks    I found many discriptions for function generators using the AD9833 on the internet
 *            and i borrowed many ideas there. But I found none with sweep function.  
 *            My implementation is based on the excellent library MD_AD9833.
 * 
 */
#include "AD9833FunctionGenerator.h"

hw_timer_t * timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer()
{
  //portENTER_CRITICAL_ISR(&timerMux);
  // Critical code here
  //portEXIT_CRITICAL_ISR(&timerMux);
  // Give a semaphore that we can check in the loop
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
}

void setup() 
{
  Serial.begin(COMPORT_SPEED);
  
  ad9833FuncGen.setup();
  
  // Show default pins for SPI and I2C
  /*
  Serial.printf("SPI MOSI = %d\r\n", MOSI);
  Serial.printf("SPI MISO = %d\r\n", MISO);
  Serial.printf("SPI SCK  = %d\r\n", SCK);
  Serial.printf("SPI SS   = %d\r\n", SS);
  Serial.printf("I2C SCL  = %d\r\n", SCL);
  Serial.printf("I2C SDA  = %d\r\n", SDA);
  */

  lcd.init();
  lcd.createChar(0, topLine);
  lcd.createChar(1, backslash);
  lcd.createChar(2, roundArrow);

  lcd.backlight();
  lcd.clear();
  lcd.print("   LCD-I2C 4 x 20   "); lcd.setCursor(0,1);
  lcd.print("--------------------"); lcd.setCursor(0,2);
  lcd.print("01234567890123456789"); lcd.setCursor(0,3);
  lcd.print("AaBbCcDdEeFfGgHhIiJj"); 
  lcd.display();
  
  cntrlKnob.setup(); // Shows initial values on LCD

  timerSemaphore = xSemaphoreCreateBinary();
  timer = timerBegin(0, 8000, true);  // Use 1st timer of 4 (counted from zero).
                                      // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more info)
                                      // 80   --> clock = 1.0 usec
                                      // 8000 --> clock = 0.1 msec
  
  
  timerAttachInterrupt(timer, &onTimer, true);  // Attach onTimer function to our timer
                                                // Set alarm to call onTimer function every 0.1 ms
                                                // Repeat the alarm (third parameter)
}

void loop() 
{
  cntrlKnob.loop();  // All the functionallity is handled in the control knobs loop
}