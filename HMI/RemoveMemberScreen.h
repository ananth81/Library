#ifndef GTKMM_REMOVE_MEMBER_SCREEN_H
#define GTKMM_REMOVE_MEMBER_SCREEN_H


#include <gtkmm.h>
#include "screen.h"

class RemoveMemberScreen :public Screen
{

public:
  RemoveMemberScreen(ScreenManager& ScreenMgr ,Gtk::Window& window);
  void DrawScreen(void);
  void ClearScreen(void);
  virtual ~RemoveMemberScreen();

protected:

private:
  Gtk::Window& window;
  //Signal handlers:
  void on_button_clicked(const Glib::ustring& data);
  class ScreenWidgets {
       public:
       ScreenWidgets():buttonRemoveMember("Remove Member"),
                       buttonBack("Back"),
                       Name("Name:")


       {}
       virtual ~ScreenWidgets(){}

       Gtk::Button buttonRemoveMember;
       Gtk::Label  Name;
       Gtk::Entry  NameEntry;
       Gtk::Button buttonBack;
       Gtk::Grid   grid;

   };
   ScreenWidgets *ScreenWidgetPtr;
};

#endif
