#include "QueryBookScreen.h"
#include <iostream>

QueryBookScreen::QueryBookScreen(ScreenManager& ScreenMgr,Gtk::Window& win)
: Screen(ScreenMgr),
  window(win),
  ScreenWidgetPtr(NULL) 
{
  screenManager.registerScreen(HMISCREENS::QUERYBOOK_SCREEN,this); 
  
}
void QueryBookScreen::DrawScreen(void)
{
  window.set_border_width(10);
  ScreenWidgetPtr = new ScreenWidgets;
  ScreenWidgetPtr->buttonQueryBook.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &QueryBookScreen::on_button_clicked),"QueryBook"));
  ScreenWidgetPtr->buttonBack.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &QueryBookScreen::on_button_clicked),"Back"));
              
              
  
  window.add(ScreenWidgetPtr->grid);
  
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->Title,0,0);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->TitleEntry,1,0);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->Author,0,1);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->AuthorEntry,1,1);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->SerialNo,0,2);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->SerialNoEntry,1,2);
  
  
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonQueryBook,1,3);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonBack,1,4);
  window.show_all_children();
 
}
void QueryBookScreen::ClearScreen(void)
{
  if(ScreenWidgetPtr)
      delete ScreenWidgetPtr;
  window.remove();	
}

QueryBookScreen::~QueryBookScreen()
{
}

void QueryBookScreen::on_button_clicked(const Glib::ustring& data)
{
	if(data == "Back")
	  screenManager.processEvent(HMIEvents::PREVIOUS_SCREEN,NULL);
}

