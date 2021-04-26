#ifndef GTKMM_QUERY_BOOK_SCREEN_H
#define GTKMM_QUERY_BOOK_SCREEN_H


#include <gtkmm.h>
#include "screen.h"

class QueryBookScreen :public Screen
{

public:
  QueryBookScreen(ScreenManager& ScreenMgr ,Gtk::Window& window);
  void DrawScreen(void);
  void ClearScreen(void);
  void UpdateDataToHMI(HMIEvents::HMIEvents_t , void*);
  virtual ~QueryBookScreen();

protected:
  
private:
  Gtk::Window& window;
  //Signal handlers:
  void on_button_clicked(const Glib::ustring& data);
  void on_selection_changed(void);
  class ScreenWidgets {
	   public:
	   ScreenWidgets():buttonQueryBook("QueryBook"),
	                   buttonBack("Back"),
                       Title("Title:"),
	                   Author("Author:"),
	                   mColumns(NULL),
                       memberColptr(NULL),
	                   box(Gtk::Orientation::ORIENTATION_VERTICAL)
                       
	                   
	                  
	   {}
	   virtual ~ScreenWidgets(){}
	   class ModelColumns : public Gtk::TreeModel::ColumnRecord
       {
          public:

          ModelColumns():onSelectionButtonsRenderded(false),
                         buttonIssue("IssueBook"),
                         buttonReturn("Return Book"),
                         buttonRemove("DeleteBook"),
                         hbox(Gtk::Orientation::ORIENTATION_HORIZONTAL)
	                   
             { add(m_title); 
			   add(m_author); 
			   add(m_reference); 
			   add(doi);
			   add(dor);
			   add(serial);
			   add(memberID);
			   }

          Gtk::TreeModelColumn<Glib::ustring> m_title;
          Gtk::TreeModelColumn<Glib::ustring> m_author;
          Gtk::TreeModelColumn<Glib::ustring> m_reference;
          Gtk::TreeModelColumn<Glib::ustring> doi;
          Gtk::TreeModelColumn<Glib::ustring> dor;
          Gtk::TreeModelColumn<Glib::ustring> serial;
          Gtk::TreeModelColumn<Glib::ustring> memberID;
          Gtk::ScrolledWindow m_ScrolledWindow;
          Gtk::TreeView m_TreeView;
          Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
          Glib::RefPtr<Gtk::TreeSelection> TreeView_TreeSelection;
          Gtk::Box    hbox;
          Gtk::Button buttonReturn;
          Gtk::Button buttonIssue;
          Gtk::Button buttonRemove;
          
          bool onSelectionButtonsRenderded;
       };
	   
       class MemberColumns : public Gtk::TreeModel::ColumnRecord
       {
          public:

          MemberColumns():vbox(Gtk::Orientation::ORIENTATION_VERTICAL),
                         buttonOK("OK"),
                         buttonCancel("Cancel"),
                         dialog("Member Select")
	                   
             { add(m_memberID); 
			   add(m_memberName);
			   add(m_memberAddress);
             }

          Gtk::TreeModelColumn<Glib::ustring> m_memberID;
          Gtk::TreeModelColumn<Glib::ustring> m_memberName;
          Gtk::TreeModelColumn<Glib::ustring> m_memberAddress;
          Gtk::ScrolledWindow m_ScrolledWindow;
          Gtk::TreeView m_TreeView;
          Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
          Glib::RefPtr<Gtk::TreeSelection> TreeView_TreeSelection;
          Gtk::Box    vbox;
          Gtk::Button buttonOK;
          Gtk::Button buttonCancel;
          Gtk::Dialog dialog;
          
          
       };
	   
       Gtk::Button buttonQueryBook;
       ModelColumns *mColumns;
       
       Gtk::Label  Title;
       Gtk::Entry  TitleEntry;
       Gtk::Label  Author;
       Gtk::Entry  AuthorEntry;
       Gtk::Button buttonBack;
       Gtk::Grid   grid;
       Gtk::Box    box;
       MemberColumns *memberColptr;
       
       
   };
   ScreenWidgets *ScreenWidgetPtr;
};

#endif
