#ifndef ISCREEN_H
#define ISCREEN_H

class IScreen {
public:
virtual void DrawScreen(void)=0;
virtual void ClearScreen(void)=0;
};
#endif
