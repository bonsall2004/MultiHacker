#include "../../Menu.h"
#include <string.h>
#include "WiFi.h"

namespace Wifi::SSID_Scanner 
{
  extern Menu* SSID_Menu;
  void CreateMenu();
  void SelectSSID();
  void test();
};

class SSID_Menu_Item : public MenuItem
{
  private:
  uint8_t SSID_ID;
  public:
    SSID_Menu_Item(const String ItemName, void (*FunctionToRun)(), MenuItemType ItemType = MenuItemType::E_Application) : MenuItem(ItemName, FunctionToRun, ItemType) {};
    SSID_Menu_Item(const String ItemName, Menu* SubMenu) : MenuItem(ItemName, SubMenu){};
    void SetSSID(uint8_t id);
    uint8_t GetSSID_ID(); 
    void something();
};

class SSID_SubMenu : public Menu
{
  private:
    const uint8_t SSID_ID;
  public:
    // Constructor definition with member initialization list
    SSID_SubMenu(String HeaderName, uint8_t ssidID, Menu* PreviousMenu) : Menu(HeaderName, PreviousMenu), SSID_ID(ssidID) {
        this->AddMenuItem(new MenuItem("Deauth", &Wifi::SSID_Scanner::test));
        // this->AddMenuItem(new MenuItem(LCD::AutoEllipsis(WiFi.SSID(this->GetSSID()), 1), &something));
    }

    uint8_t GetSSID() const;
};