#include <iostream>
#include "AddBookScreen.h"
#include "libbook.h"

AddBookScreen::AddBookScreen(ScreenManager& ScreenMgr,Gtk::Window& win)
: Screen(ScreenMgr),
  window(win),
  ScreenWidgetPtr(NULL)
{
  screenManager.registerScreen(HMISCREENS::ADDNEWBOOK_SCREEN,this);

}
void AddBookScreen::DrawScreen(void)
{
  window.set_border_width(10);
  ScreenWidgetPtr = new ScreenWidgets;
  ScreenWidgetPtr->buttonAddBook.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &AddBookScreen::on_button_clicked),"AddBook"));
  ScreenWidgetPtr->buttonBack.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &AddBookScreen::on_button_clicked),"Back"));



  window.add(ScreenWidgetPtr->grid);

  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->Title,0,0);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->TitleEntry,1,0);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->Author,0,1);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->AuthorEntry,1,1);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->IsReference,0,2);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->m_Combo,1,2);
  ScreenWidgetPtr->m_Combo.append("No");
  ScreenWidgetPtr->m_Combo.append("Yes");
  ScreenWidgetPtr->m_Combo.set_active(0);

  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonAddBook,1,3);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonBack,1,4);
  window.show_all_children();

}
void AddBookScreen::ClearScreen(void)
{
  if(ScreenWidgetPtr)
      delete ScreenWidgetPtr;
  window.remove();
}

AddBookScreen::~AddBookScreen()
{
}

void AddBookScreen::on_button_clicked(const Glib::ustring& data)
{
    if(data == "Back")
      screenManager.processEvent(HMIEvents::PREVIOUS_SCREEN,NULL);
    else if( data == "AddBook")
    {
      libBook newBook(ScreenWidgetPtr->TitleEntry.get_text(),
                      ScreenWidgetPtr->AuthorEntry.get_text(),
                      ScreenWidgetPtr->m_Combo.get_active_text(),
                      NULL_DATE,
                      NULL_DATE
                      );

      screenManager.processEvent(HMIEvents::ADD_NEW_BOOK_CONFIRM,(void*)&newBook);
    }
}

