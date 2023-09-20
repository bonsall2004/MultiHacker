#include "WiFi.h"
#include "./Wifi.h"
#include <string.h>
#include "./SSID_Scanner/SSID_Scanner.h"
#include "./AP_Flooder/AP_Flooder.h"


namespace Wifi 
{

  Menu* WifiMenu = new Menu("Wifi");
  void CreateMenu() {
    WifiMenu->ClearMenuItems();
    WifiMenu->AddMenuItem(new MenuItem("AP Sniffer", SSID_Scanner::CreateMenu, MenuItemType::E_MenuApplication));
    WifiMenu->AddMenuItem(new MenuItem("AP Flood", AP_Flooder::CreateMenu, MenuItemType::E_MenuApplication));
    WifiMenu->SetPreviousMenu(CurrentMenu);
    WifiMenu->Draw();
  }
  
};