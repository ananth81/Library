#ifndef GTKMM_ADD_MEMBER_SCREEN_H
#define GTKMM_ADD_MEMBER_SCREEN_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm.h>
#include "screen.h"

class AddMemberScreen :public Screen
{

public:
  AddMemberScreen(ScreenManager& ScreenMgr ,Gtk::Window& window);
  void DrawScreen(void);
  void ClearScreen(void);
  virtual ~AddMemberScreen();

protected:
  
private:
  Gtk::Window& window;
  //Signal handlers:
  void on_button_clicked(const Glib::ustring& data);
  class ScreenWidgets {
	   public:
	   ScreenWidgets():buttonAddNewMember("Add New Member"),
	                   buttonBack("Back"),
	                   Name("Name:"),
	                   Address("Address:")
	                  
	   {}
	   virtual ~ScreenWidgets(){}
	   
       Gtk::Button buttonAddNewMember;
       Gtk::Label  Name;
       Gtk::Entry  NameEntry;
       Gtk::Label  Address;
       Gtk::Entry  AddressEntry;
       Gtk::Button buttonBack;
       Gtk::Grid   grid;
       
   };
   ScreenWidgets *ScreenWidgetPtr;
};

#endif
