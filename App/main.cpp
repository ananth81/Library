// File: main.cc


#include <gtkmm/application.h>
#include "HMI/homeScreen.h"
#include "HMI/AddMemberScreen.h"
#include "HMI/AddBookScreen.h"
#include "HMI/RemoveBookScreen.h"
#include "HMI/IssueBookScreen.h"
#include "HMI/RemoveMemberScreen.h"
#include "HMI/QueryBookScreen.h"
#include "SQliteDB/sqliteDB.h"

class Library {
    
    public:
      Library():home(screenMgr,win),
                AddMember(screenMgr,win),
                RemoveMember(screenMgr,win),
                AddBook(screenMgr,win),
                RemoveBook(screenMgr,win),
                IssueBook(screenMgr,win),
                QueryBook(screenMgr,win),
                screenMgr(sqliteDB)
                
       
      {}
     Gtk::Window& getBaseWindow(){ return win;}
     void start(void){ screenMgr.start();}
    private:
      LibSQLiteDB  sqliteDB;
      ScreenManager screenMgr;
      Gtk::Window win;
      homeScreen  home;
      AddMemberScreen AddMember;
      AddBookScreen   AddBook;
      RemoveBookScreen RemoveBook;
      IssueBookScreen  IssueBook;
      QueryBookScreen  QueryBook;
      RemoveMemberScreen RemoveMember;
        
};

int main (int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.library");

  Library lib;
  lib.start();
  //Shows the window and returns when it is closed.
  return app->run(lib.getBaseWindow());
}
