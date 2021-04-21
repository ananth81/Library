#include "QueryBookScreen.h"
#include <iostream>
#include "libbook.h"
QueryBookScreen::QueryBookScreen(ScreenManager& ScreenMgr,Gtk::Window& win)
: Screen(ScreenMgr),
  window(win),
  ScreenWidgetPtr(NULL) 
{
  screenManager.registerScreen(HMISCREENS::QUERYBOOK_SCREEN,this); 
  
}
void QueryBookScreen::DrawScreen(void)
{
  window.set_border_width(10);
  ScreenWidgetPtr = new ScreenWidgets;
  ScreenWidgetPtr->buttonQueryBook.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &QueryBookScreen::on_button_clicked),"QueryBook"));
  ScreenWidgetPtr->buttonBack.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
              &QueryBookScreen::on_button_clicked),"Back"));
              
              
  
  window.add(ScreenWidgetPtr->box);
  ScreenWidgetPtr->box.pack_start(ScreenWidgetPtr->grid);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->Title,0,0);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->TitleEntry,1,0);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->Author,0,1);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->AuthorEntry,1,1);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->SerialNo,0,2);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->SerialNoEntry,1,2);
  
  
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonQueryBook,1,3);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonBack,1,4);
  
  ScreenWidgetPtr->m_ScrolledWindow.add(ScreenWidgetPtr->m_TreeView);

      //Only show the scrollbars when they are necessary:    
  ScreenWidgetPtr->m_ScrolledWindow.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC, Gtk::PolicyType::POLICY_AUTOMATIC);
     
  
    
      //Create the Tree model:
  ScreenWidgetPtr->m_refTreeModel = Gtk::ListStore::create(ScreenWidgetPtr->mColumns);
  ScreenWidgetPtr->m_TreeView.set_model(ScreenWidgetPtr->m_refTreeModel);
  ScreenWidgetPtr->box.pack_start(ScreenWidgetPtr->m_ScrolledWindow);
  window.show_all_children();
 
}
void QueryBookScreen::ClearScreen(void)
{
  if(ScreenWidgetPtr)
      delete ScreenWidgetPtr;
  window.remove();	
}

void QueryBookScreen::UpdateDataToHMI(HMIEvents::HMIEvents_t event, void* data)
{
   if(HMIEvents::HMI_UPDATE_BOOK_QUERY_LIST == event)
   {
      //Add the TreeView, inside a ScrolledWindow, with the button underneath:
      

	  //Fill the TreeView's model
	  std::vector<libBook> *ptr=(std::vector<libBook> *)data;
	  std::vector<libBook>::iterator iter = ptr->begin();
	  for(iter=ptr->begin();iter!=ptr->end(); iter++)
	  {
	    auto row = *(ScreenWidgetPtr->m_refTreeModel->append());
	    row[ScreenWidgetPtr->mColumns.m_title] = (*iter).getTitle();
	    row[ScreenWidgetPtr->mColumns.m_author] = (*iter).getAuthor();
	    row[ScreenWidgetPtr->mColumns.m_reference] = (*iter).isReference();
	    row[ScreenWidgetPtr->mColumns.doi] = (*iter).getDateOfIssue();
	    row[ScreenWidgetPtr->mColumns.dor] = (*iter).getDateOfReturn();
	    row[ScreenWidgetPtr->mColumns.memberID] = (*iter).getMemberID();
      }
	  
	  //Add the TreeView's view columns:
	  //This number will be shown with the default numeric formatting.
	  ScreenWidgetPtr->m_TreeView.append_column("Title", ScreenWidgetPtr->mColumns.m_title);
	  ScreenWidgetPtr->m_TreeView.append_column("Author",ScreenWidgetPtr->mColumns.m_author);
	  ScreenWidgetPtr->m_TreeView.append_column("Reference", ScreenWidgetPtr->mColumns.m_reference);
	  ScreenWidgetPtr->m_TreeView.append_column("Date Of Issue",ScreenWidgetPtr->mColumns.doi);
	  ScreenWidgetPtr->m_TreeView.append_column("Date Of Return", ScreenWidgetPtr->mColumns.dor);
	  ScreenWidgetPtr->m_TreeView.append_column("MemberID",ScreenWidgetPtr->mColumns.memberID);

      ScreenWidgetPtr->m_TreeView.expand_all();
      
      window.show_all_children();
  }

}

QueryBookScreen::~QueryBookScreen()
{
}

void QueryBookScreen::on_button_clicked(const Glib::ustring& data)
{
	if(data == "Back")
	  screenManager.processEvent(HMIEvents::PREVIOUS_SCREEN,NULL);
	else if(data == "QueryBook")
	{
	  libBook book(ScreenWidgetPtr->TitleEntry.get_text(),
	               ScreenWidgetPtr->AuthorEntry.get_text(),
	               "No",
                   "0000/00/00",
                   "0000/00/00");
	  screenManager.processEvent(HMIEvents::QUERY_BOOK_SELECT_CONFIRM,(void*)&book);
	  
    }
}

