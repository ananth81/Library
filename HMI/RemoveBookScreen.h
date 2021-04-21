#ifndef GTKMM_REMOVE_BOOK_SCREEN_H
#define GTKMM_REMOVE_BOOK_SCREEN_H

#include <gtkmm.h>
#include "screen.h"

class RemoveBookScreen :public Screen
{

public:
  RemoveBookScreen(ScreenManager& ScreenMgr ,Gtk::Window& window);
  void DrawScreen(void);
  void ClearScreen(void);
  virtual ~RemoveBookScreen();

protected:
  
private:
  Gtk::Window& window;
  //Signal handlers:
  void on_button_clicked(const Glib::ustring& data);
  class ScreenWidgets {
	   public:
	   ScreenWidgets():buttonRemoveBook("RemoveBook"),
	                   buttonBack("Back"),
	                   Title("Title:"),
	                   Author("Author:"),
	                   SerialNo("Serial No:")
	                   
	                  
	   {}
	   virtual ~ScreenWidgets(){}
	   
       Gtk::Button buttonRemoveBook;
       Gtk::Label  Title;
       Gtk::Entry  TitleEntry;
       Gtk::Label  Author;
       Gtk::Entry  AuthorEntry;
       Gtk::Label  SerialNo;
       Gtk::Entry  SerialNoEntry;
       Gtk::Button buttonBack;
       Gtk::Grid   grid;
       
   };
   ScreenWidgets *ScreenWidgetPtr;
};

#endif
