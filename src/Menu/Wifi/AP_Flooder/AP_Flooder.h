#pragma once
#include "../../Menu.h"
#include <string.h>
#include "WiFi.h"

namespace Wifi::AP_Flooder 
{
  extern Menu* SSID_Menu;
  void CreateMenu();
  extern uint8_t Spam_AP_Count;
  void SelectSSID(uint8_t ID);
  void CreateAP(uint8_t AP_Count, String Name = "None");
  void DeleteAllSpamAP();
  String GenerateRandomSSID(uint8_t Length);
  void SingleAP();
  void TenAP();
  void TwentyFiveAP();
  void FiftyAP();
  void HundredAP();
};

class AP_Flooder_Item : public MenuItem
{
  public:
    AP_Flooder_Item(const String ItemName, void (*FunctionToRun)(), MenuItemType ItemType = MenuItemType::E_Application) : MenuItem(ItemName, FunctionToRun, ItemType) {};
    AP_Flooder_Item(const String ItemName, Menu* SubMenu) : MenuItem(ItemName, SubMenu){};
};

class AP_Flooder_SubMenu : public Menu
{
  private:
    const uint8_t SSID_ID;
  public:
    // Constructor definition with member initialization list
    AP_Flooder_SubMenu(String HeaderName, uint8_t ssidID, Menu* PreviousMenu) : Menu(HeaderName, PreviousMenu), SSID_ID(ssidID) {

    }
    void ExtraCodeToRun() override;
    uint8_t GetSSID() const;
};