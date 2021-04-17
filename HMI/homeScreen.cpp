#include "homeScreen.h"
#include <iostream>

homeScreen::homeScreen(ScreenManager& ScreenMgr,Gtk::Window& win)
: Screen(ScreenMgr),
  window(win),
  ScreenWidgetPtr(NULL)
{
  screenManager.registerScreen(HMISCREENS::HOME_SCREEN,this); 
 
}
void homeScreen::DrawScreen(void)
{
  window.set_border_width(10);
  ScreenWidgetPtr = new ScreenWidgets;
  
  ScreenWidgetPtr->buttonNewBook.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &homeScreen::on_button_clicked),"AddNewBook"));
  
  ScreenWidgetPtr->buttonRemoveBook.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &homeScreen::on_button_clicked),"RemoveBook"));
  ScreenWidgetPtr->buttonAddNewMember.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &homeScreen::on_button_clicked),"AddNewMember"));
  ScreenWidgetPtr->buttonRemoveMember.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &homeScreen::on_button_clicked),"RemoveMember"));
  ScreenWidgetPtr->buttonIssueBook.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &homeScreen::on_button_clicked),"Issue/ReturnBook"));
  ScreenWidgetPtr->buttonQueryBookAvailability.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &homeScreen::on_button_clicked),"QueryBook"));

  window.add(ScreenWidgetPtr->box);
  ScreenWidgetPtr->box.pack_start(ScreenWidgetPtr->buttonNewBook);
  ScreenWidgetPtr->box.pack_start(ScreenWidgetPtr->buttonRemoveBook);
  ScreenWidgetPtr->box.pack_start(ScreenWidgetPtr->buttonAddNewMember);
  ScreenWidgetPtr->box.pack_start(ScreenWidgetPtr->buttonRemoveMember);
  ScreenWidgetPtr->box.pack_start(ScreenWidgetPtr->buttonIssueBook);
  ScreenWidgetPtr->box.pack_start(ScreenWidgetPtr->buttonQueryBookAvailability);
  window.show_all_children();
 
}

void homeScreen::ClearScreen(void)
{
  if(ScreenWidgetPtr)
    delete ScreenWidgetPtr;
  window.remove();
}

homeScreen::~homeScreen()
{
}

void homeScreen::on_button_clicked(const Glib::ustring& data)
{
  if(data == "AddNewMember")
  screenManager.processEvent(HMIEvents::ADD_NEW_MEMBER_SELECT,NULL);
  else if(data == "RemoveMember")
  screenManager.processEvent(HMIEvents::REMOVE_MEMBER_SELECT,NULL);
  else if(data =="AddNewBook")
  screenManager.processEvent(HMIEvents::ADD_NEW_BOOK_SELECT,NULL);
  else if( data =="RemoveBook")
  screenManager.processEvent(HMIEvents::REMOVE_BOOK_SELECT,NULL);
  else if( data =="Issue/ReturnBook")
  screenManager.processEvent(HMIEvents::ISSUE_RETURN_BOOK_SELECT,NULL);
  else if( data =="QueryBook")
  screenManager.processEvent(HMIEvents::QUERY_BOOK_SELECT,NULL);
}


