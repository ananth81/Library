// File: helloworld.cc

#include "AddMemberScreen.h"
#include <iostream>

AddMemberScreen::AddMemberScreen(ScreenManager& ScreenMgr,Gtk::Window& win)
: Screen(ScreenMgr),
  window(win),
  ScreenWidgetPtr(NULL)
{
  screenManager.registerScreen(HMISCREENS::ADDMEMBER_SCREEN,this);

}
void AddMemberScreen::DrawScreen(void)
{
  window.set_border_width(10);
  ScreenWidgetPtr = new ScreenWidgets;
  ScreenWidgetPtr->buttonAddNewMember.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &AddMemberScreen::on_button_clicked),"AddNewMember"));
  ScreenWidgetPtr->buttonBack.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &AddMemberScreen::on_button_clicked),"Back"));



  window.add(ScreenWidgetPtr->grid);

  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->Name,0,0);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->NameEntry,1,0);

  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->Address,0,1);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->AddressEntry,1,1);


  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonAddNewMember,1,2);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonBack,1,3);
  window.show_all_children();

}
void AddMemberScreen::ClearScreen(void)
{
  if(ScreenWidgetPtr)
      delete ScreenWidgetPtr;
  window.remove();
}

AddMemberScreen::~AddMemberScreen()
{
}

void AddMemberScreen::on_button_clicked(const Glib::ustring& data)
{
    if(data == "Back")
    {
      screenManager.processEvent(HMIEvents::PREVIOUS_SCREEN,NULL);
    }
    else if(data == "AddNewMember")
    {
      libMember member(ScreenWidgetPtr->NameEntry.get_text(),ScreenWidgetPtr->AddressEntry.get_text(),"0");
      screenManager.processEvent(HMIEvents::ADD_NEW_MEMBER_SELECT_CONFIRM,(void*)&member);
    }

}

