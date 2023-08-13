#pragma once
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include "string.h"

#define TFT_CS_ST7735   10
#define TFT_RST_ST7735  9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        7   


namespace LCD 
{
  extern Adafruit_ST7735 display;
  void PrintTextXCenter(String text, uint8_t ypos, uint8_t TextSize = 1, uint16_t color = 0);
  void PrintlnTextXCenter(String text, uint8_t ypos, uint8_t TextSize = 1, uint16_t color = 0);
  uint8_t GetTextYCenter(uint8_t BoxHeight, uint8_t TextSize = 1);
  void DrawPrompt(String message);
  String AutoEllipsis(String Message, uint8_t TextSize, String suffix = "...");
}