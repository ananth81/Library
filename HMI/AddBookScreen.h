#ifndef GTKMM_ADD_BOOK_SCREEN_H
#define GTKMM_ADD_BOOK_SCREEN_H


#include <gtkmm.h>
#include "screen.h"

class AddBookScreen :public Screen
{

public:
  AddBookScreen(ScreenManager& ScreenMgr ,Gtk::Window& window);
  void DrawScreen(void);
  void ClearScreen(void);
  virtual ~AddBookScreen();

protected:
  
private:
  Gtk::Window& window;
  //Signal handlers:
  void on_button_clicked(const Glib::ustring& data);
  class ScreenWidgets {
	   public:
	   ScreenWidgets():buttonAddBook("AddBook"),
	                   buttonBack("Back"),
	                   Title("Title:"),
	                   Author("Author:"),
	                   IsReference("Reference Book:")
	                   
	                  
	   {}
	   virtual ~ScreenWidgets(){}
	   
       Gtk::Button buttonAddBook;
       Gtk::Label  Title;
       Gtk::Entry  TitleEntry;
       Gtk::Label  Author;
       Gtk::Entry  AuthorEntry;
       Gtk::Label  IsReference;
       Gtk::ComboBoxText m_Combo;;
       Gtk::Button buttonBack;
       Gtk::Grid   grid;
       
   };
   ScreenWidgets *ScreenWidgetPtr;
};

#endif
