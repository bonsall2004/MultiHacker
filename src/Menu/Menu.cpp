#include "Menu.h"
#include <Arduino.h>
#include <type_traits>

// -------------------------- Menu -------------------------- //

void Menu::DrawHeader() 
{
  LCD::display.fillScreen(ITEMBACKGROUND);
  LCD::display.fillRect(0, 0, LCD::display.width(), HEADER_BOX_HEIGHT, SELECTEDITEMBACKGROUND);
  uint8_t textSize = (this->HeaderName.length() * 16) > LCD::display.width() ? 1 : 2;
  LCD::PrintlnTextXCenter(LCD::AutoEllipsis(this->HeaderName, textSize), LCD::GetTextYCenter(HEADER_BOX_HEIGHT, textSize), textSize, TEXTCOLORSELECTED);
}

void Menu::DrawMenuItems() 
{
  uint8_t startIndex = (this->MenuOffset - 1) * (ITEMS_TO_DISPLAY);
  uint8_t endIndex = min((uint8_t)(startIndex + ITEMS_TO_DISPLAY), (uint8_t)(MenuItems.size()));
  if((startIndex + ITEMS_TO_DISPLAY) != endIndex) {
    LCD::display.fillRect(0, HEADER_BOX_HEIGHT, LCD::display.width(), LCD::display.height(), ITEMBACKGROUND);
  }
  Serial.println("startIndex");
  Serial.println(startIndex);
  Serial.println("endIndex");
  Serial.println(endIndex);
  Serial.println("size");
  Serial.println(MenuItems.size());
  
  uint8_t positionIndex = 0;

  for (uint8_t i = startIndex; i < endIndex; i++) 
  {
    positionIndex++;
    MenuItem* item = MenuItems[i];
    item->Draw(positionIndex);
  }
}

Menu::~Menu() {
  MenuItems.clear();
}

void Menu::Draw() 
{
  this->DrawHeader();
  this->DrawMenuItems();
  CurrentMenu = this;
  CurrentMenu->SetSelectedItem(0);
};

LinkedList<MenuItem*> Menu::GetMenuItems() const 
{
  return this->MenuItems;
}

void Menu::AddMenuItem(MenuItem* item) 
{
  item->SetItemID((uint8_t)this->MenuItems.size());
  this->MenuItems.add(item);
}

uint8_t Menu::GetSelectedItem() const 
{
  return this->SelectedItem;
}

void Menu::SetPreviousMenu(Menu* PrevMenu) 
{
  this->PreviousMenu = PrevMenu;
  return;
}

void Menu::SetSelectedItem(uint8_t ID) 
{
  if(this->MenuItems.size() > ID) {
    this->SelectedItem = ID;
  } else if(ID < 0) {
    this->SelectedItem = this->MenuItems.size();
  } else {
    this->SelectedItem = 0;
  }
}

void Menu::Back() 
{
  if(this->PreviousMenu == nullptr) {
    return;
  }
  this->PreviousMenu->Draw();
  return;
}

void Menu::RunSelected() {
  switch (this->MenuItems[this->SelectedItem]->GetItemType())
  {
  case MenuItemType::E_SubMenu:
    this->MenuItems[this->SelectedItem]->SubMenu->SetPreviousMenu(this);
    this->MenuItems[this->SelectedItem]->SubMenu->Draw();
    break;

  case MenuItemType::E_Application:
    this->MenuItems[this->SelectedItem]->FunctionToRun();
    break;

  case MenuItemType::E_MenuApplication:
    this->MenuItems[this->SelectedItem]->FunctionToRun();
    break;
  default:
    break;
  }
}

void Menu::ClearMenuItems() 
{
  this->MenuItems.clear();
}

void Menu::NavigateDown() {
  this->SelectedItem = (this->SelectedItem + 1) % (this->MenuItems.size());
  this->MenuOffset = Math::RoundUp(this->SelectedItem+1, ITEMS_TO_DISPLAY);
  this->DrawMenuItems();
}

void Menu::NavigateUp() {
  this->SelectedItem = (this->SelectedItem - 1 + this->MenuItems.size()) % (this->MenuItems.size());
  this->MenuOffset = Math::RoundUp(this->SelectedItem+1, ITEMS_TO_DISPLAY);
  this->DrawMenuItems();
}

// ----------------------- Menu Item ----------------------- //

String MenuItem::GetItemName() const 
{
  return this->ItemName;
}

MenuItemType MenuItem::GetItemType() const 
{
  return this->ItemType;
}

void MenuItem::Draw(uint8_t Position) {
  uint16_t TextColour = this->ID == CurrentMenu->GetSelectedItem() ? TEXTCOLORSELECTED : TEXTCOLOR;
  uint16_t BackgroundColour = this->ID == CurrentMenu->GetSelectedItem() ? SELECTEDITEMBACKGROUND : ITEMBACKGROUND;
  LCD::display.fillRect(0, (HEADER_BOX_HEIGHT + ((Position-1) *MENU_ITEM_SIZE)), LCD::display.width(), MENU_ITEM_SIZE, BackgroundColour);
  LCD::PrintlnTextXCenter(this->GetItemName(), LCD::GetTextYCenter(MENU_ITEM_SIZE) + HEADER_BOX_HEIGHT + ((Position-1) *MENU_ITEM_SIZE), 1, TextColour);
  switch (this->ItemType)
  {
  case (MenuItemType::E_Application):
    break;
  default:
    LCD::display.fillTriangle(LCD::display.width() - 8, (((Position-1) *MENU_ITEM_SIZE) + 2) + HEADER_BOX_HEIGHT, LCD::display.width() - 8, ((((Position-1) *MENU_ITEM_SIZE) + MENU_ITEM_SIZE) - 2) + HEADER_BOX_HEIGHT, LCD::display.width() - 2, (((Position-1) *MENU_ITEM_SIZE) + (MENU_ITEM_SIZE / 2) + HEADER_BOX_HEIGHT), TextColour);
    break;
  }
}

void MenuItem::SetItemID(uint8_t ID) {
  this->ID = ID;
}

uint8_t MenuItem::GetItemID() const {
  return this->ID;
}
