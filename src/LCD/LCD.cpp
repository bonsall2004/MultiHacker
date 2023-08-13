#include "LCD.h"

namespace LCD 
{
  Adafruit_ST7735 display = Adafruit_ST7735(TFT_CS_ST7735, TFT_DC, TFT_RST_ST7735);

  void drawTextCenter(String Text, uint8_t yPos, uint8_t TextSize, uint16_t Color, bool println) {
    display.setTextColor(Color);
    display.setTextSize(TextSize);
    uint8_t xPos = ((display.width() / 2) - (Text.length() * ((TextSize * 6) / 2)));
    display.setCursor(xPos, yPos);
    if(println == true) {
      display.println(Text);
    } else {
      display.print(Text);
    }
    return;
  }

  void PrintTextXCenter(String Text, uint8_t yPos, uint8_t TextSize, uint16_t Color) 
  {
    drawTextCenter(Text, yPos, TextSize, Color, false);
  }

  void PrintlnTextXCenter(String Text, uint8_t yPos, uint8_t TextSize, uint16_t Color) 
  {
    drawTextCenter(Text, yPos, TextSize, Color, true);
  }

  uint8_t GetTextYCenter(uint8_t BoxHeight, uint8_t TextSize) 
  {
    return (BoxHeight - (TextSize * 8)) / 2;
  }

  void DrawPrompt(String message) {
    LCD::display.fillRect(0, 0, LCD::display.width(), LCD::display.height(), 10533);
    display.fillRect(5, 5, display.width() - 10, display.height() - 10, 65504);
    PrintTextXCenter(message, (display.height() / 2 )-16, 1, 0x2126);
  }

  String AutoEllipsis(String Message, uint8_t textSize, String suffix) {
    textSize = textSize * 8;
    uint16_t messageWidth = Message.length() * textSize;
    
    if (messageWidth > (display.width())) {
        int ellipsisWidth = suffix.length() * textSize;
        int maxMessageWidth = display.width() - ellipsisWidth;
        int truncatedLength = maxMessageWidth / textSize;
        
        Message = Message.substring(0, truncatedLength) + suffix;
    }

    return Message;
  }
}
