#ifndef GTKMM_ADD_BOOK_SCREEN_H
#define GTKMM_ADD_BOOK_SCREEN_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
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
	                   SerialNo("Serial No:")
	                   
	                  
	   {}
	   virtual ~ScreenWidgets(){}
	   
       Gtk::Button buttonAddBook;
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
