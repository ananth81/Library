#ifndef GTKMM_ISSUE_BOOK_SCREEN_H
#define GTKMM_ISSUE_BOOK_SCREEN_H


#include <gtkmm.h>
#include "screen.h"

class IssueBookScreen :public Screen
{

public:
  IssueBookScreen(ScreenManager& ScreenMgr ,Gtk::Window& window);
  void DrawScreen(void);
  void ClearScreen(void);
  virtual ~IssueBookScreen();

protected:

private:
  Gtk::Window& window;
  //Signal handlers:
  void on_button_clicked(const Glib::ustring& data);
  class ScreenWidgets {
       public:
       ScreenWidgets():buttonIssueBook("IssueBook"),
                       buttonReturnBook("ReturnBook"),
                       buttonBack("Back"),
                       Title("Title:"),
                       Author("Author:"),
                       SerialNo("Serial No:"),
                       MemberID("MemberID:")


       {}
       virtual ~ScreenWidgets(){}

       Gtk::Button buttonIssueBook;
       Gtk::Button buttonReturnBook;
       Gtk::Label  Title;
       Gtk::Entry  TitleEntry;
       Gtk::Label  Author;
       Gtk::Entry  AuthorEntry;
       Gtk::Label  SerialNo;
       Gtk::Entry  SerialNoEntry;
       Gtk::Label  MemberID;
       Gtk::Entry  MemberIDEntry;
       Gtk::Button buttonBack;
       Gtk::Grid   grid;

   };
   ScreenWidgets *ScreenWidgetPtr;
};

#endif
