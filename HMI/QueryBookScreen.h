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
  class ScreenWidgets {
	   public:
	   ScreenWidgets():buttonQueryBook("QueryBook"),
	                   buttonBack("Back"),
	                   Title("Title:"),
	                   Author("Author:"),
	                   SerialNo("Serial No:"),
	                   mColumns(NULL),
	                   box(Gtk::Orientation::ORIENTATION_VERTICAL)
	                   
	                  
	   {}
	   virtual ~ScreenWidgets(){}
	   class ModelColumns : public Gtk::TreeModel::ColumnRecord
       {
          public:

          ModelColumns()
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
       };
	   
       Gtk::Button buttonQueryBook;
       ModelColumns *mColumns;
       
       Gtk::Label  Title;
       Gtk::Entry  TitleEntry;
       Gtk::Label  Author;
       Gtk::Entry  AuthorEntry;
       Gtk::Label  SerialNo;
       Gtk::Entry  SerialNoEntry;
       Gtk::Button buttonBack;
       Gtk::Grid   grid;
       Gtk::Box    box;
       
   };
   ScreenWidgets *ScreenWidgetPtr;
};

#endif
