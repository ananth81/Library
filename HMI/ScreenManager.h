#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <map>
#include <vector>
#include "IScreen.h"
#include "HMIEvents.h"
#include "HMIScreens.h"
#include "SQliteDB/sqliteDB.h"

class ScreenManager
{
   public:
       ScreenManager(LibSQLiteDB& db):database(db){}
       virtual ~ScreenManager(){}
       void registerScreen(HMISCREENS::HMIScreens_t screen , IScreen* scrPtr);
       void processEvent(HMIEvents::HMIEvents_t event , void *ptr);
       void start(void);
       void updateScreen(HMISCREENS::HMIScreens_t screen , bool updateScreenStack=true);
       void returnToPreviousScreen();
  private:
       std::vector<HMISCREENS::HMIScreens_t > screenStack;

       std::map<HMISCREENS::HMIScreens_t,IScreen*> screenMap;
       LibSQLiteDB& database;
};






#endif
