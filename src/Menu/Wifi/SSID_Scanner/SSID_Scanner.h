#pragma once
#include "../../Menu.h"
#include <string.h>
#include "WiFi.h"

namespace Wifi::SSID_Scanner 
{
  extern Menu* SSID_Menu;
  void CreateMenu();
  extern uint8_t SelectedSSID;
  void SelectSSID(uint8_t ID);
  void test();
  void Clone();
};

class SSID_Menu_Item : public MenuItem
{
  public:
    SSID_Menu_Item(const String ItemName, void (*FunctionToRun)(), MenuItemType ItemType = MenuItemType::E_Application) : MenuItem(ItemName, FunctionToRun, ItemType) {};
    SSID_Menu_Item(const String ItemName, Menu* SubMenu) : MenuItem(ItemName, SubMenu){};
};

class SSID_SubMenu : public Menu
{
  private:
    const uint8_t SSID_ID;
  public:
    // Constructor definition with member initialization list
    SSID_SubMenu(String HeaderName, uint8_t ssidID, Menu* PreviousMenu) : Menu(HeaderName, PreviousMenu), SSID_ID(ssidID) {
        Serial.print(SSID_ID);
        this->AddMenuItem(new SSID_Menu_Item("Clone", &Wifi::SSID_Scanner::Clone));
        this->AddMenuItem(new SSID_Menu_Item("Deauth", &Wifi::SSID_Scanner::test));
    }
    void ExtraCodeToRun() override;
    uint8_t GetSSID() const;
};