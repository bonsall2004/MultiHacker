#include "WiFi.h"
#include "./Wifi.h"
#include <string.h>
#include "./SSID_Scanner/SSID_Scanner.h"


namespace Wifi 
{

  Menu* WifiMenu = new Menu("Wifi");
  void CreateMenu() {
    WifiMenu->ClearMenuItems();
    WifiMenu->AddMenuItem(new MenuItem("SSID Scanner", SSID_Scanner::CreateMenu, MenuItemType::E_MenuApplication));
    WifiMenu->SetPreviousMenu(CurrentMenu);
    WifiMenu->Draw();
  }
  
};