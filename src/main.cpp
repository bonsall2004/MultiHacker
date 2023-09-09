#include <Arduino.h>
#include "./LCD/LCD.h"
#include "./Menu/Menu.h"
#include "./Menu/Wifi/Wifi.h"

#define DOWN_PIN 5 // GPIO 5
#define UP_PIN 18 //GPIO 18
#define SELECT_PIN 19 // GPIO 19
#define BACK_PIN 2  // GPIO2
#define OTHER_PIN 0  // GPIO2
#define BACKLIGHT_PIN 3  // GPIO3

#define debounceif(pin) if(Debounce(pin)) 

bool Debounce(int pin);

Menu* MainMenu;
Menu* CurrentMenu;
void test1() {
  return;
}

void setup() {
  Serial.begin(115200);

  pinMode(UP_PIN, OUTPUT);
  pinMode(SELECT_PIN, OUTPUT);
  pinMode(DOWN_PIN, OUTPUT);
  pinMode(BACK_PIN, OUTPUT);
  pinMode(3, OUTPUT);

  LCD::display.initR(0);
  LCD::display.fillRect(0, 0, LCD::display.width(), LCD::display.height(), ITEMBACKGROUND);
  LCD::display.setRotation(1);
  MainMenu = new Menu("General");
  MainMenu->AddMenuItem(new MenuItem("Wifi", Wifi::CreateMenu, MenuItemType::E_MenuApplication));
  for(int i = 0; i < (100); i++) {
    MainMenu->AddMenuItem(new MenuItem((String)i, &test1));
  }
  CurrentMenu = MainMenu;
  CurrentMenu->Draw();
  digitalWrite(3, HIGH);
}

bool test = true;
void loop() {
  debounceif(DOWN_PIN) {
    CurrentMenu->NavigateDown();
  }
  debounceif(UP_PIN) {
    CurrentMenu->NavigateUp();
  }
  debounceif(BACK_PIN) {
    CurrentMenu->Back();
  }
  debounceif(SELECT_PIN) {
    CurrentMenu->RunSelected();
  }
}



bool Debounce(int pin) {
  uint8_t ButtonPressed = digitalRead(pin);
  if(ButtonPressed == 1) 
  {
    delay(50);
    ButtonPressed = digitalRead(pin);
    if(ButtonPressed == 0) 
   {
      return true;
    } else {
      return false;
    }
  } else {

    return false;
    }
}
