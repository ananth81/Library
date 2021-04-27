#ifndef GTKMM_HOME_SCREEN_H
#define GTKMM_HOME_SCREEN_H

#include <gtkmm.h>
#include "screen.h"

class homeScreen :public Screen
{

public:
  homeScreen(ScreenManager& ScreenMgr,Gtk::Window& win);
  void DrawScreen(void);
  void ClearScreen(void);
  virtual ~homeScreen();

private:
  Gtk::Window& window;
  //Signal handlers:
  void on_button_clicked(const Glib::ustring& data);

  class ScreenWidgets {
      public:
      ScreenWidgets():buttonNewBook("Add New Book"),
                buttonRemoveBook("Remove Book"),
                buttonAddNewMember("Add New Member"),
                buttonRemoveMember("Remove Member"),
                buttonIssueBook("Issue / Return Book"),
                buttonQueryBookAvailability("Query Book Availability"),
                box(Gtk::Orientation::ORIENTATION_VERTICAL)

      {
      }
     virtual ~ScreenWidgets(){}
     Gtk::Button buttonNewBook;
     Gtk::Button buttonRemoveBook;
     Gtk::Button buttonAddNewMember;
     Gtk::Button buttonRemoveMember;
     Gtk::Button buttonIssueBook;
     Gtk::Button buttonQueryBookAvailability;
     Gtk::Box box;
  };
  ScreenWidgets *ScreenWidgetPtr;
};

#endif
