#include <Arduino.h>
// libraries for I2C oled 0.96" SSD1306
#include <U8g2lib.h>
#include <Wire.h>
// libraries for I2S audio using MAX98357A
#include <AudioFileSourcePROGMEM.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>
// converted mp3 file using xxd
#include "darth-vader-theme.h"

// defining hardware pin
#define BUTTON_PIN 0
#define LED_COLUMN_PIN 1
#define LED_BUTTON_PIN 27
#define I2C_SDA 10 //
#define I2C_SCL 11
#define I2S_BCLK 13
#define I2S_LRCLK 14
#define I2S_DATA 15

/* constructor
see u8g2setupcpp at https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
*/
U8G2_SSD1306_128X64_NONAME_F_2ND_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
AudioGeneratorMP3 *mp3;
AudioFileSourcePROGMEM *file;
AudioOutputI2S *out;

/* xbm images
generated using https://lopaka.app/editor/
*/
static const unsigned char image_Layer_21_bits[] = {0x0c, 0x0f, 0x0c};
static const unsigned char image_Layer_5_bits[] = {0xc0, 0x00, 0xf0, 0x00, 0xfc, 0x03, 0xff, 0x07, 0xfc, 0x03, 0xf0, 0x00, 0xc0, 0x00};
static const unsigned char image_Layer_6_bits[] = {0xe0, 0x03, 0x18, 0x0c, 0x04, 0x10, 0x02, 0x20, 0x92, 0x24, 0xa1, 0x42, 0xc1, 0x41, 0xf1, 0x47, 0xc1, 0x41, 0xa1, 0x42, 0x92, 0x24, 0x02, 0x20, 0x04, 0x10, 0x18, 0x0c, 0xe0, 0x03};
static const unsigned char image_Layer_4_bits[] = {0x00, 0x00, 0xe0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0xcf, 0x03, 0x00, 0x00, 0x00, 0x80, 0x81, 0x0f, 0x0c, 0x00, 0x00, 0x00, 0x60, 0x80, 0x0f, 0x30, 0x00, 0x00, 0x00, 0x18, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x04, 0x00, 0x07, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x07, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x40, 0x00, 0x00, 0x02, 0x00, 0x10, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x0f, 0x00, 0x00, 0xc0, 0xff, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x40, 0x00, 0x00, 0x02, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x07, 0x00, 0x02, 0x00, 0x00, 0x04, 0x00, 0x07, 0x00, 0x01, 0x00, 0x00, 0x18, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x60, 0x80, 0x0f, 0x30, 0x00, 0x00, 0x00, 0x80, 0x81, 0x0f, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x9e, 0xcf, 0x03, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0x00, 0x00, 0x00};

// variables
bool blinking = false;
bool buttonLedState = false;
unsigned long blinkInterval = 200;
unsigned long lastBlink = 0;
volatile int pressCount = 0;
volatile unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 50; // 50 ms debounce
unsigned long selectionStart = 0;
bool selectionActive = false;
unsigned long selectionTimeout = 4000; // 4 seconds

// interrupt routine with debounce feature
void handleButtonInterrupt()
{
  unsigned long now = millis();
  if (now - lastPressTime > debounceDelay)
  {
    pressCount++;
    lastPressTime = now;

    if (!selectionActive)
    {
      selectionActive = true;
      selectionStart = now;
      blinking = true;
      pressCount = 0;
    }
  }
}

void map()
{
  u8g2.clearDisplay();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.drawEllipse(32, 32, 10, 10);
  u8g2.drawEllipse(32, 32, 20, 20);
  u8g2.drawEllipse(12, 24, 77, 31);
  u8g2.drawXBM(99, 38, 11, 7, image_Layer_5_bits);
  u8g2.drawEllipse(83, 12, 7, 7);
  u8g2.setFont(u8g2_font_4x6_tr);
  u8g2.drawStr(12, 63, "9");
  u8g2.drawLine(32, 63, 32, 0);
  u8g2.drawLine(48, 63, 48, 0);
  u8g2.drawLine(64, 63, 64, 0);
  u8g2.drawLine(16, 63, 16, 0);
  u8g2.drawLine(80, 63, 80, 0);
  u8g2.drawLine(96, 63, 96, 0);
  u8g2.drawLine(112, 63, 112, 0);
  u8g2.drawStr(40, 63, "11");
  u8g2.drawStr(72, 63, "13");
  u8g2.drawLine(0, 16, 127, 16);
  u8g2.drawStr(104, 63, "15");
  u8g2.drawLine(0, 48, 127, 48);
  u8g2.drawStr(1, 30, "H");
  u8g2.drawLine(0, 32, 127, 32);
  u8g2.drawXBM(68, 26, 4, 3, image_Layer_21_bits);
  u8g2.sendBuffer();
}

void audioManager()
{
  if (mp3->isRunning())
  {
    if (!mp3->loop())
    {
      mp3->stop();
      Serial.println("Playback finished");
      attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, RISING);
      digitalWrite(LED_COLUMN_PIN, LOW);
    }
  }
}

void setup()
{
  // pin setup
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(LED_BUTTON_PIN, OUTPUT);
  pinMode(LED_COLUMN_PIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED_BUTTON_PIN, LOW);
  digitalWrite(LED_COLUMN_PIN, LOW);

  Serial.begin(115200);
  // cpu speed for audio decoding
  set_sys_clock_khz(250000, true);
  // audio output setup
  out = new AudioOutputI2S();
  out->SetPinout(I2S_BCLK, I2S_LRCLK, I2S_DATA);
  out->SetGain(0.5);
  mp3 = new AudioGeneratorMP3();
  /*
  i2c pin definition
  Wire1 is for I2C1, Wire is for I2C0
  if use I2C0 change u8g2 constructor to U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
  */
  Wire1.setSDA(I2C_SDA);
  Wire1.setSCL(I2C_SCL);
  Wire1.begin();
  u8g2.begin();
  map();
  // attach interrupt
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, RISING);
}

void loop()
{

  // handle blinking and display after button pressed
  if (blinking)
  {
    u8g2.clearBuffer();
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    u8g2.setFont(u8g2_font_4x6_tr);
    u8g2.drawStr(44, 6, "X-000-1139");
    u8g2.drawStr(16, 64, "QATECH ] VELOS [ WARNING");
    u8g2.drawXBM(39, 7, 51, 51, image_Layer_4_bits);
    u8g2.setFont(u8g2_font_haxrcorp4089_tr);
    char buf[12];
    itoa(pressCount, buf, 10);
    u8g2.drawStr(62, 36, buf);
    u8g2.sendBuffer();

    if (millis() - lastBlink >= blinkInterval)
    {
      buttonLedState = !buttonLedState;
      digitalWrite(LED_BUTTON_PIN, buttonLedState);
      lastBlink = millis();
    }
  }

  // check for selectionTimeout and handle song selection
  if (selectionActive && millis() - selectionStart >= selectionTimeout)
  {
    blinking = false;
    buttonLedState = true;
    digitalWrite(LED_BUTTON_PIN, HIGH);

    Serial.print("Selection done! LED = ON, Song selected = ");

    if (pressCount == 1 || pressCount == 2)
    {
      if (pressCount == 1)
        file = new AudioFileSourcePROGMEM(darth_vader_theme, darth_vader_theme_len);
      else
        file = new AudioFileSourcePROGMEM(darth_vader_theme, darth_vader_theme_len);

      mp3->begin(file, out);
      digitalWrite(LED_COLUMN_PIN, HIGH);
      detachInterrupt(digitalPinToInterrupt(BUTTON_PIN));
    }

    map();
    buttonLedState = false;
    digitalWrite(LED_BUTTON_PIN, buttonLedState);
    pressCount = 0;
    selectionActive = false;
  }

  audioManager();

  // debug section
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 200)
  {
    Serial.print("Button pressCount: ");
    Serial.print(pressCount);
    Serial.print(" | LED: ");
    if (blinking)
      Serial.print("BLINKING");
    else
      Serial.print(buttonLedState ? "ON" : "OFF");
    Serial.println();
    lastPrint = millis();
  }
}
