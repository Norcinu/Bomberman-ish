#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "basestate.h"

class Engine;

class MenuState : public BaseState
{
public:
    MenuState(void);
    ~MenuState(void);

    bool Initialise(Engine * eng);
	void CleanUp();
	void Pause();
	void Resume();
	void HandleEvent(Engine * eng);
	void Update(Engine * eng);
	void Render(Engine * eng);

    static MenuState* GetInstance() {return &instance;}
private:
    static MenuState instance;
};

#endif 
