#include "./SSID_Scanner.h"
#include "WiFi.h"
#include "../../../LCD/LCD.h"
namespace Wifi::SSID_Scanner 
{

  uint8_t SelectedSSID;
  Menu* SSID_Menu = new Menu("Networks");

  void CreateMenu() {
    SSID_Menu->ClearMenuItems();
    SSID_Menu->SetPreviousMenu(CurrentMenu);
    SSID_Menu->SetSelectedItem(0);
    LCD::DrawPrompt("Scanning...");

    uint8_t n = WiFi.scanNetworks();

    if(n == 0) 
    {
      SSID_Menu->AddMenuItem(new MenuItem("No Networks Found", CurrentMenu));
    } else {
      for(uint8_t i = 0; i < n; i++) {
        SSID_Menu->AddMenuItem( new MenuItem((LCD::AutoEllipsis((String)WiFi.SSID(i), 1)), new SSID_SubMenu((String)WiFi.SSID(i), i, CurrentMenu)));
      }
    }
    SSID_Menu->Draw();
  };

  void SelectSSID(uint8_t ID) {
    Wifi::SSID_Scanner::SelectedSSID = ID;
    return;
  };

  void test() {
    Serial.print(WiFi.SSID(Wifi::SSID_Scanner::SelectedSSID));
    return;
  };

};

uint8_t SSID_SubMenu::GetSSID() const {
  return this->SSID_ID;
};

void SSID_SubMenu::ExtraCodeToRun() {
  Wifi::SSID_Scanner::SelectSSID(this->SSID_ID);
  return;
};
