#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "IScreen.h"
#include "HMIEvents.h"
#include "HMIScreens.h"
#include <map>
#include <vector>

class ScreenManager
{
   public:
       ScreenManager(){}
       virtual ~ScreenManager(){}
       void registerScreen(HMISCREENS::HMIScreens_t screen , IScreen* scrPtr);
       void processEvent(HMIEvents::HMIEvents_t event , void *ptr);
       void start(void);
       void updateScreen(HMISCREENS::HMIScreens_t screen , bool updateScreenStack=true);
       void returnToPreviousScreen();
  private:
       std::vector<HMISCREENS::HMIScreens_t > screenStack;
       
       std::map<HMISCREENS::HMIScreens_t,IScreen*> screenMap;
};






#endif
