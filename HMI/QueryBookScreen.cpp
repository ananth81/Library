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
  
  
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonQueryBook,1,3);
  ScreenWidgetPtr->grid.attach(ScreenWidgetPtr->buttonBack,1,4);
  
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
      if(ScreenWidgetPtr->mColumns)
      {
		  ScreenWidgetPtr->box.remove(ScreenWidgetPtr->mColumns->m_ScrolledWindow);
          ScreenWidgetPtr->box.remove(ScreenWidgetPtr->mColumns->hbox);
		  delete ScreenWidgetPtr->mColumns;
	  }
      ScreenWidgetPtr->mColumns=new ScreenWidgets::ModelColumns;
      ScreenWidgetPtr->mColumns->m_ScrolledWindow.add(ScreenWidgetPtr->mColumns->m_TreeView);

      //Only show the scrollbars when they are necessary:    
      ScreenWidgetPtr->mColumns->m_ScrolledWindow.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC, Gtk::PolicyType::POLICY_AUTOMATIC);
     
      //Create the Tree model:
      ScreenWidgetPtr->mColumns->m_refTreeModel = Gtk::ListStore::create(*(ScreenWidgetPtr->mColumns));
      ScreenWidgetPtr->mColumns->m_TreeView.set_model(ScreenWidgetPtr->mColumns->m_refTreeModel);
      ScreenWidgetPtr->box.pack_start(ScreenWidgetPtr->mColumns->m_ScrolledWindow);
        
	  //Fill the TreeView's model
	  std::vector<libBook> *ptr=(std::vector<libBook> *)data;
	  std::vector<libBook>::iterator iter = ptr->begin();
	  for(iter=ptr->begin();iter!=ptr->end(); iter++)
	  {
	    auto row = *(ScreenWidgetPtr->mColumns->m_refTreeModel->append());
	    row[ScreenWidgetPtr->mColumns->m_title] = (*iter).getTitle();
	    row[ScreenWidgetPtr->mColumns->m_author] = (*iter).getAuthor();
	    row[ScreenWidgetPtr->mColumns->m_reference] = (*iter).isReference();
	    row[ScreenWidgetPtr->mColumns->doi] = (*iter).getDateOfIssue()==NULL_DATE?"N/A":(*iter).getDateOfIssue();
	    row[ScreenWidgetPtr->mColumns->dor] = (*iter).getDateOfReturn()==NULL_DATE?"N/A":(*iter).getDateOfReturn();
	    row[ScreenWidgetPtr->mColumns->memberID] = (*iter).getMemberID()=="0"?"N/A":(*iter).getMemberID();
	    row[ScreenWidgetPtr->mColumns->memberName] = (*iter).getMemberName();
	    row[ScreenWidgetPtr->mColumns->serial] = (*iter).getSerialNo();
      }
	  
	  //Add the TreeView's view columns:
	  ScreenWidgetPtr->mColumns->m_TreeView.append_column("SerialNo",ScreenWidgetPtr->mColumns->serial);
	  ScreenWidgetPtr->mColumns->m_TreeView.append_column("Title", ScreenWidgetPtr->mColumns->m_title);
	  ScreenWidgetPtr->mColumns->m_TreeView.append_column("Author",ScreenWidgetPtr->mColumns->m_author);
	  ScreenWidgetPtr->mColumns->m_TreeView.append_column("Reference", ScreenWidgetPtr->mColumns->m_reference);
	  ScreenWidgetPtr->mColumns->m_TreeView.append_column("Date Of Issue",ScreenWidgetPtr->mColumns->doi);
	  ScreenWidgetPtr->mColumns->m_TreeView.append_column("Date Of Return", ScreenWidgetPtr->mColumns->dor);
	  ScreenWidgetPtr->mColumns->m_TreeView.append_column("MemberID",ScreenWidgetPtr->mColumns->memberID);
	  ScreenWidgetPtr->mColumns->m_TreeView.append_column("Member Name",ScreenWidgetPtr->mColumns->memberName);
	  ScreenWidgetPtr->mColumns->TreeView_TreeSelection=ScreenWidgetPtr->mColumns->m_TreeView.get_selection();
	  ScreenWidgetPtr->mColumns->TreeView_TreeSelection->signal_changed().connect(sigc::mem_fun(*this,
      &QueryBookScreen::on_selection_changed));
      
      ScreenWidgetPtr->mColumns->m_TreeView.expand_all();
      
      window.show_all_children();
  }
  else if(HMIEvents::HMI_UPDATE_MEMBER_LIST == event)
  {
      std::vector<libMember> *ptr=(std::vector<libMember> *)data;
	  std::vector<libMember>::iterator iter = ptr->begin();
	  std::cout<< "Creating Dialog box"<<std::endl;
	  if(ScreenWidgetPtr->memberColptr)
	    delete ScreenWidgetPtr->memberColptr;
      ScreenWidgetPtr->memberColptr= new ScreenWidgets::MemberColumns();
      
      ScreenWidgetPtr->memberColptr->dialog.set_default_size(300,70);
      
      ScreenWidgetPtr->memberColptr->dialog.get_content_area()->pack_start(ScreenWidgetPtr->memberColptr->m_ScrolledWindow);
      ScreenWidgetPtr->memberColptr->m_ScrolledWindow.add(ScreenWidgetPtr->memberColptr->m_TreeView);
      
      ScreenWidgetPtr->memberColptr->m_refTreeModel = Gtk::ListStore::create(*(ScreenWidgetPtr->memberColptr));
      ScreenWidgetPtr->memberColptr->m_TreeView.set_model(ScreenWidgetPtr->memberColptr->m_refTreeModel);
     
      ScreenWidgetPtr->memberColptr->m_ScrolledWindow.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC, Gtk::PolicyType::POLICY_AUTOMATIC);
     
      ScreenWidgetPtr->memberColptr->m_TreeView.append_column("MemberID",ScreenWidgetPtr->memberColptr->m_memberID);
	  ScreenWidgetPtr->memberColptr->m_TreeView.append_column("Name", ScreenWidgetPtr->memberColptr->m_memberName);
	  ScreenWidgetPtr->memberColptr->m_TreeView.append_column("Address",ScreenWidgetPtr->memberColptr->m_memberAddress);
	  
      for(iter=ptr->begin();iter!=ptr->end(); iter++)
	  {
	    auto row = *(ScreenWidgetPtr->memberColptr->m_refTreeModel->append());
	    row[ScreenWidgetPtr->memberColptr->m_memberID] = (*iter).getMemberID();
	    row[ScreenWidgetPtr->memberColptr->m_memberName] = (*iter).getName();
	    row[ScreenWidgetPtr->memberColptr->m_memberAddress] = (*iter).getAddress();
	    
      } 
    
      ScreenWidgetPtr->memberColptr->TreeView_TreeSelection=ScreenWidgetPtr->memberColptr->m_TreeView.get_selection();
	  ScreenWidgetPtr->memberColptr->TreeView_TreeSelection->signal_changed().connect(sigc::mem_fun(*this,
      &QueryBookScreen::on_member_selection_changed));
      
      ScreenWidgetPtr->mColumns->m_TreeView.expand_all();
      ScreenWidgetPtr->memberColptr->dialog.show();
      ScreenWidgetPtr->memberColptr->dialog.show_all_children();

  }

}
void QueryBookScreen::on_member_selection_changed(void)
{
	if(!ScreenWidgetPtr->memberColptr->onSelectionButtonsRenderded)
	{
	  Glib::RefPtr< Gtk::TreeModel > MemberTreeModel=ScreenWidgetPtr->memberColptr->TreeView_TreeSelection->get_model();
      Gtk::TreeModel::iterator iter=ScreenWidgetPtr->memberColptr->TreeView_TreeSelection->get_selected(MemberTreeModel);
      Gtk::TreeModel::Row row = *iter;
      ScreenWidgetPtr->memberColptr->dialog.get_content_area()->pack_start(ScreenWidgetPtr->memberColptr->buttonOK);
      ScreenWidgetPtr->memberColptr->dialog.get_content_area()->pack_start(ScreenWidgetPtr->memberColptr->buttonCancel);   
      ScreenWidgetPtr->memberColptr->buttonOK.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
           &QueryBookScreen::on_button_clicked),"MemberSelectOK"));
      ScreenWidgetPtr->memberColptr->buttonCancel.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
           &QueryBookScreen::on_button_clicked),"MemberSelectCancel"));
      ScreenWidgetPtr->memberColptr->onSelectionButtonsRenderded=true;
      
      ScreenWidgetPtr->memberColptr->dialog.show_all_children();	
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
                   NULL_DATE,
                   NULL_DATE);
	  screenManager.processEvent(HMIEvents::QUERY_BOOK_SELECT_CONFIRM,(void*)&book);
	  
    }
    else if(data == "BookIssue")
    {
       screenManager.processEvent(HMIEvents::ISSUE_BOOK_SELECT_CONFIRM,NULL);
    }
    else if(data == "BookReturn")
    {
	   Glib::RefPtr< Gtk::TreeModel > BookTreeModel=ScreenWidgetPtr->mColumns->TreeView_TreeSelection->get_model();
       Gtk::TreeModel::iterator iter=ScreenWidgetPtr->mColumns->TreeView_TreeSelection->get_selected(BookTreeModel);
       Gtk::TreeModel::Row row = *iter;
       libBook book;
       book.setSerialNo(row.get_value(ScreenWidgetPtr->mColumns->serial).c_str());
       screenManager.processEvent(HMIEvents::RETURN_BOOK_SELECT_CONFIRM,(void*)&book);
		
    }
    else if(data == "BookRemove")
    {
       Glib::RefPtr< Gtk::TreeModel > BookTreeModel=ScreenWidgetPtr->mColumns->TreeView_TreeSelection->get_model();
       Gtk::TreeModel::iterator iter=ScreenWidgetPtr->mColumns->TreeView_TreeSelection->get_selected(BookTreeModel);
       Gtk::TreeModel::Row row = *iter;
       libBook book;
       book.setSerialNo(  row.get_value(ScreenWidgetPtr->mColumns->serial).c_str());
       screenManager.processEvent(HMIEvents::QUERY_BOOK_REMOVE_CONFIRM,(void*)&book);
       ScreenWidgetPtr->mColumns->m_refTreeModel->erase(*iter);
       
       
    }
    else if (data =="MemberSelectOK")
    {
	   
	   Glib::RefPtr< Gtk::TreeModel > TreeModel=ScreenWidgetPtr->mColumns->TreeView_TreeSelection->get_model();
       Gtk::TreeModel::iterator iter=ScreenWidgetPtr->mColumns->TreeView_TreeSelection->get_selected(TreeModel);
       Gtk::TreeModel::Row row = *iter;
       libBook book;
       book.setSerialNo(  row.get_value(ScreenWidgetPtr->mColumns->serial).c_str());
       
       TreeModel=ScreenWidgetPtr->memberColptr->TreeView_TreeSelection->get_model();
       iter=ScreenWidgetPtr->memberColptr->TreeView_TreeSelection->get_selected(TreeModel);
       row = *iter;
       book.setMemberID(row.get_value(ScreenWidgetPtr->memberColptr->m_memberID).c_str());
       book.setMemberName(row.get_value(ScreenWidgetPtr->memberColptr->m_memberName).c_str());
       screenManager.processEvent(HMIEvents::ISSUE_BOOK_TO_MEMBER,(void*)&book);
       ScreenWidgetPtr->memberColptr->dialog.hide();
	   
	   window.show_all_children();
	}
	else if(data == "MemberSelectCancel")
	{
		ScreenWidgetPtr->memberColptr->dialog.hide();
		
		window.show_all_children();
	}
}

void QueryBookScreen::on_selection_changed(void)
{
    
    if(ScreenWidgetPtr->mColumns->TreeView_TreeSelection->count_selected_rows())
    {
        Glib::RefPtr< Gtk::TreeModel > BookTreeModel=ScreenWidgetPtr->mColumns->TreeView_TreeSelection->get_model();
        Gtk::TreeModel::iterator iter=ScreenWidgetPtr->mColumns->TreeView_TreeSelection->get_selected(BookTreeModel);
        Gtk::TreeModel::Row row = *iter;
        ScreenWidgetPtr->mColumns->buttonIssue.set_sensitive(row[ScreenWidgetPtr->mColumns->m_reference]=="No" &&
        row[ScreenWidgetPtr->mColumns->memberID]=="N/A");
        ScreenWidgetPtr->mColumns->buttonReturn.set_sensitive(row[ScreenWidgetPtr->mColumns->memberID]!="N/A");
        ScreenWidgetPtr->mColumns->buttonRemove.set_sensitive(row[ScreenWidgetPtr->mColumns->memberID]=="N/A");
        
        if(!ScreenWidgetPtr->mColumns->onSelectionButtonsRenderded)
        {
           ScreenWidgetPtr->box.pack_start(ScreenWidgetPtr->mColumns->hbox);
           ScreenWidgetPtr->mColumns->hbox.pack_start(ScreenWidgetPtr->mColumns->buttonIssue);
           ScreenWidgetPtr->mColumns->hbox.pack_start(ScreenWidgetPtr->mColumns->buttonReturn);
           ScreenWidgetPtr->mColumns->hbox.pack_start(ScreenWidgetPtr->mColumns->buttonRemove);
           ScreenWidgetPtr->mColumns->buttonIssue.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
                  &QueryBookScreen::on_button_clicked),"BookIssue"));
           ScreenWidgetPtr->mColumns->buttonReturn.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
                  &QueryBookScreen::on_button_clicked),"BookReturn"));
           ScreenWidgetPtr->mColumns->buttonRemove.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
                  &QueryBookScreen::on_button_clicked),"BookRemove"));
      
           ScreenWidgetPtr->mColumns->onSelectionButtonsRenderded=true;
           
        }
        window.show_all_children();
    }
    else
    {
      ScreenWidgetPtr->mColumns->buttonIssue.set_sensitive(false);
      ScreenWidgetPtr->mColumns->buttonReturn.set_sensitive(false);
      ScreenWidgetPtr->mColumns->buttonRemove.set_sensitive(false);
    }
}


