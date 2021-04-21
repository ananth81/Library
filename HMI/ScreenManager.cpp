#include "ScreenManager.h"




void ScreenManager::processEvent(HMIEvents::HMIEvents_t event , void *ptr)
{
   switch (event)
   {
      case HMIEvents::ADD_NEW_BOOK_SELECT:
      {
          updateScreen(HMISCREENS::ADDNEWBOOK_SCREEN);
      }
      break;
      
      case HMIEvents::ADD_NEW_BOOK_CONFIRM:
      {
          database.AddNewBook(*(libBook*)ptr);
          break;
      }
   
      case HMIEvents::ADD_NEW_MEMBER_SELECT:
      {
         updateScreen(HMISCREENS::ADDMEMBER_SCREEN);
      }
      break;
      
      case HMIEvents::ADD_NEW_MEMBER_SELECT_CONFIRM:
      {
         database.AddMember(*(libMember*)ptr);
      }
      break;
   
      case HMIEvents::ISSUE_RETURN_BOOK_SELECT:
      {
         updateScreen(HMISCREENS::ISSUERETURNBOOK_SCREEN);
      }
      break;
      
      case HMIEvents::RETURN_BOOK_SELECT_CONFIRM:
         
      break;
      
      case HMIEvents::ISSUE_BOOK_SELECT_CONFIRM:
         
      break;
   
      case HMIEvents::REMOVE_BOOK_SELECT:
      {
         updateScreen(HMISCREENS::REMOVEBOOK_SCREEN);
      }
      break;
      
      case HMIEvents::REMOVE_BOOK_SELECT_CONFIRM:
      {
         database.RemoveBook(*(libBook*)ptr);
      }
      break;
      
      case HMIEvents::REMOVE_MEMBER_SELECT:
      {
         updateScreen(HMISCREENS::REMOVEMEMBER_SCREEN);
      }
      break;
      
      case HMIEvents::REMOVE_MEMBER_SELECT_CONFIRM:
      {
         database.RemoveMember(*(libMember*)ptr);
      }
      break;
   
      case HMIEvents::QUERY_BOOK_SELECT:
      {
         updateScreen(HMISCREENS::QUERYBOOK_SCREEN);
      }
      break;
     
      case HMIEvents::QUERY_BOOK_SELECT_CONFIRM:
      {
        std::map<HMISCREENS::HMIScreens_t,IScreen*>::iterator iterCurrentScreen=screenMap.find(HMISCREENS::QUERYBOOK_SCREEN);
		if(screenMap.end() != iterCurrentScreen )
		(iterCurrentScreen->second)->UpdateDataToHMI(HMIEvents::HMI_UPDATE_BOOK_QUERY_LIST, 
		                          (void*)&(database.QueryBookAvailability(*(libBook*)ptr)));
      }  
      break;
      
      case HMIEvents::PREVIOUS_SCREEN:
      {
         returnToPreviousScreen();
      }
      break;
      
      default: 
      break;
   }
}

void ScreenManager::registerScreen(HMISCREENS::HMIScreens_t screen , IScreen *ptr)
{
    screenMap.insert(std::pair<HMISCREENS::HMIScreens_t,IScreen*>(screen,ptr));
}

void ScreenManager::updateScreen(HMISCREENS::HMIScreens_t screen,bool updateScreenStack)
{
	if(screenStack.size())
    {
		std::map<HMISCREENS::HMIScreens_t,IScreen*>::iterator iterCurrentScreen=screenMap.find(screenStack.back());
		if(screenMap.end() != iterCurrentScreen )
		(iterCurrentScreen->second)->ClearScreen();
	}
	std::map<HMISCREENS::HMIScreens_t,IScreen*>::iterator iterNewScreen;
	if(updateScreenStack)
	{
	  iterNewScreen=screenMap.find(screen);
	}
	else
	{
		screenStack.pop_back();
		iterNewScreen=screenMap.find(screenStack.back());
	}
	
    if(screenMap.end() != iterNewScreen)
    {
        (iterNewScreen->second)->DrawScreen();
        if(updateScreenStack)
        screenStack.push_back(screen);
    }
}
void ScreenManager::returnToPreviousScreen()
{
   updateScreen(screenStack.back(),false);
}

void ScreenManager::start(void)
{
   updateScreen(HMISCREENS::HOME_SCREEN);
}
