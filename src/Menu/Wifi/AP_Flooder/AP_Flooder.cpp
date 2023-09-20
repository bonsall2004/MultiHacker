#include "./AP_Flooder.h"
#include "WiFi.h"
#include "../../../LCD/LCD.h"
namespace Wifi::AP_Flooder 
{

  Menu* AP_Flooder_Option_Menu = new Menu("AP Spammer");
  uint8_t Spam_AP_Count = 0;

  String GenerateRandomSSID(uint8_t Length) {
    static const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    String randomString = "";

    for (int i = 0; i < Length; i++) {
      int index = random(sizeof(charset) - 1);
      randomString += charset[index];
    }
    return randomString;
  }

  void CreateAP(uint8_t AP_Count, String Name) {
    Wifi::AP_Flooder::Spam_AP_Count += AP_Count;
    for(uint8_t i = 0; i < AP_Count; i++) {
      
      if(Name == "None") {
        WiFi.softAP(GenerateRandomSSID(8), "Password1234", random(1, 14));
      } else {
        WiFi.softAP(Name, "Password1234", random(1, 14));
      }

      if(AP_Count >= 2) {
        vTaskDelay(25);
      };
    }

    LCD::DrawPrompt("Created "+(String)AP_Count+" Access \nPoint"+(AP_Count == 1 ? "" : "s"));
    delay(1500);
    CurrentMenu->Draw();
    return;
  }

  void DeleteAllSpamAP() {
    for(uint8_t i = 0; i < Spam_AP_Count; i++) {
      WiFi.softAPdisconnect(true);
    }
    Spam_AP_Count = 0;

    LCD::DrawPrompt("Cleared Active SSIDs");
    while(digitalRead(2) != HIGH) {

    };
    CurrentMenu->Draw();
    return;
  };

  void CreateMenu() {
    AP_Flooder_Option_Menu->ClearMenuItems();
    AP_Flooder_Option_Menu->SetPreviousMenu(CurrentMenu);
    AP_Flooder_Option_Menu->SetSelectedItem(0);
    AP_Flooder_Option_Menu->AddMenuItem(new AP_Flooder_Item("+1", &Wifi::AP_Flooder::SingleAP));
    AP_Flooder_Option_Menu->AddMenuItem(new AP_Flooder_Item("+10", &Wifi::AP_Flooder::TenAP));
    AP_Flooder_Option_Menu->AddMenuItem(new AP_Flooder_Item("+25", &Wifi::AP_Flooder::TwentyFiveAP));
    AP_Flooder_Option_Menu->AddMenuItem(new AP_Flooder_Item("+50", &Wifi::AP_Flooder::FiftyAP));
    AP_Flooder_Option_Menu->AddMenuItem(new AP_Flooder_Item("+100", &Wifi::AP_Flooder::HundredAP));
    AP_Flooder_Option_Menu->AddMenuItem(new AP_Flooder_Item("Delete All", &Wifi::AP_Flooder::DeleteAllSpamAP));
    AP_Flooder_Option_Menu->Draw();
  };

  void SingleAP() {
    CreateAP(1);
  };

  void TenAP() {
    CreateAP(10);
  };

  void TwentyFiveAP() {
    CreateAP(25);
  };

  void FiftyAP() {
    CreateAP(50);
  };

  void HundredAP() {
    CreateAP(100);
  };
};