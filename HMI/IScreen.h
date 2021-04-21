#ifndef ISCREEN_H
#define ISCREEN_H

#include "HMI/HMIEvents.h"

class IScreen {
public:
virtual void DrawScreen(void)=0;
virtual void ClearScreen(void)=0;
virtual void UpdateDataToHMI(HMIEvents::HMIEvents_t , void*){};
};
#endif
