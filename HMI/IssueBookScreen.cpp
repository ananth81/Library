#include "IssueBookScreen.h"
#include <iostream>

IssueBookScreen::IssueBookScreen(ScreenManager& ScreenMgr,Gtk::Window& win)
: Screen(ScreenMgr),
  window(win),
  ScreenWidgetPtr(NULL) 
{
  screenManager.registerScreen(HMISCREENS::ISSUERETURNBOOK_SCREEN,this); 
  
}
void IssueBookScreen::DrawScreen(void)
{
  window.set_border_width(10);
  ScreenWidgetPtr = new ScreenWidgets;
  ScreenWidgetPtr->buttonIssueBook.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &IssueBookScreen::on_button_clicked),"IssueBook"));
  ScreenWidgetPtr->buttonBack.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &IssueBookScreen::on_button_clicked),"Back"));
              
              
  
  window.add(ScreenWidgetPtr->grid);
  
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->Title,0,0);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->TitleEntry,1,0);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->Author,0,1);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->AuthorEntry,1,1);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->SerialNo,0,2);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->SerialNoEntry,1,2);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->MemberID,0,3);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->MemberIDEntry,1,3);
  
  
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonIssueBook,1,4);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonReturnBook,1,5);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonBack,1,6);
  window.show_all_children();
 
}
void IssueBookScreen::ClearScreen(void)
{
  if(ScreenWidgetPtr)
      delete ScreenWidgetPtr;
  window.remove();	
}

IssueBookScreen::~IssueBookScreen()
{
}

void IssueBookScreen::on_button_clicked(const Glib::ustring& data)
{
	if(data == "Back")
	  screenManager.processEvent(HMIEvents::PREVIOUS_SCREEN,NULL);
}

