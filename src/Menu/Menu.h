#pragma once
#include <Vector.h>
#include "../LCD/LCD.h"
#include "../Math/Math.h"
#include "LinkedList.h"
// UI Colours
#define BACKGROUND 0x861
#define ITEMBACKGROUND 10533
#define SELECTEDITEMBACKGROUND 65504
#define TEXTCOLOR 65528
#define TEXTCOLORSELECTED 0x2126
// Header Size
#define MIN_HEADER_BOX_HEIGHT 18
// Item Sizes
#define MENU_ITEM_SIZE 16
#define ITEMS_TO_DISPLAY Math::FloorTen(LCD::display.height() - MIN_HEADER_BOX_HEIGHT) / MENU_ITEM_SIZE

#define HEADER_BOX_HEIGHT ((LCD::display.height() - (ITEMS_TO_DISPLAY * MENU_ITEM_SIZE)) + MIN_HEADER_BOX_HEIGHT ) - (MENU_ITEM_SIZE * 1.5)

class Menu;
class MenuItem;

extern Menu* CurrentMenu;
extern Menu CachedMenu;

enum class MenuItemType 
{
  E_Application,
  E_SubMenu,
  E_MenuApplication
};

enum class MenuType 
{
  E_MainMenu,
  E_SubMenu,
  E_ApplicationMenu
};

class Menu 
{
  private:
    const String HeaderName;
    LinkedList<MenuItem*> MenuItems = LinkedList<MenuItem*>();
    uint8_t MenuOffset = 1;
    uint8_t SelectedItem = 0;
    Menu* PreviousMenu;
    void DrawHeader();
    void DrawMenuItems();
  
  public:
    Menu(String HeaderName, Menu* PreviousMenu = nullptr) : HeaderName(HeaderName), PreviousMenu(PreviousMenu) {};
    ~Menu();
    void Draw();
    void NavigateUp();
    void NavigateDown();
    void AddMenuItem(MenuItem* item);
    void ClearMenuItems();
    LinkedList<MenuItem*> GetMenuItems() const;
    uint8_t GetSelectedItem() const;
    void SetSelectedItem(uint8_t ID);
    void Back();
    void RunSelected();
    virtual void ExtraCodeToRun() {
      return;
    };
    void SetPreviousMenu(Menu* PrevMenu);
};

class MenuItem
{
  private:
    const String ItemName;
    const MenuItemType ItemType;
    int8_t ID;
    
  public:
    MenuItem(const String ItemName, void (*FunctionToRun)(), MenuItemType ItemType = MenuItemType::E_Application) : ItemName(ItemName), FunctionToRun(FunctionToRun), ItemType(ItemType) {};
    MenuItem(const String ItemName, Menu* SubMenu) : ItemName(ItemName), SubMenu(SubMenu), ItemType(MenuItemType::E_SubMenu) {};
    String GetItemName() const;
    MenuItemType GetItemType() const;
    void Draw(uint8_t Position);
    void SetItemID(uint8_t ID);
    uint8_t GetItemID() const;

    void (*FunctionToRun)();
    Menu* (*MenuApplicationConstructor)();
    Menu* SubMenu;
};