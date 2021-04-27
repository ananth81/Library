#ifndef SCREEN_H
#define SCREEN_H

#include "ScreenManager.h"
#include "HMIEvents.h"
#include "HMIScreens.h"
#include "IScreen.h"
class Screen : public IScreen
{
   public:

      Screen(ScreenManager& screenMgr):screenManager(screenMgr)
      {
      }
     virtual ~Screen(){}
   protected:
      ScreenManager& screenManager;

};


#endif
