#include "RemoveMemberScreen.h"
#include <iostream>

RemoveMemberScreen::RemoveMemberScreen(ScreenManager& ScreenMgr,Gtk::Window& win)
: Screen(ScreenMgr),
  window(win),
  ScreenWidgetPtr(NULL) 
{
  screenManager.registerScreen(HMISCREENS::REMOVEMEMBER_SCREEN,this); 
  
}
void RemoveMemberScreen::DrawScreen(void)
{
  window.set_border_width(10);
  ScreenWidgetPtr = new ScreenWidgets;
  ScreenWidgetPtr->buttonRemoveMember.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &RemoveMemberScreen::on_button_clicked),"RemoveMember"));
  ScreenWidgetPtr->buttonBack.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &RemoveMemberScreen::on_button_clicked),"Back"));
              
              
  
  window.add(ScreenWidgetPtr->grid);
  
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->Name,0,0);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->NameEntry,1,0);
  
  
  
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonRemoveMember,1,1);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonBack,1,2);
  window.show_all_children();
 
}
void RemoveMemberScreen::ClearScreen(void)
{
  if(ScreenWidgetPtr)
      delete ScreenWidgetPtr;
  window.remove();	
}

RemoveMemberScreen::~RemoveMemberScreen()
{
}

void RemoveMemberScreen::on_button_clicked(const Glib::ustring& data)
{
	if(data == "Back")
	  screenManager.processEvent(HMIEvents::PREVIOUS_SCREEN,NULL);
}

