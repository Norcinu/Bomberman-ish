#include "MenuState.h"
#include "Engine.h"
#include "TextManager.h"
#include "Visualisation.h"

MenuState MenuState::instance;

TextManager text_manager;

MenuState::MenuState(void)
{
}


MenuState::~MenuState(void)
{
}

bool MenuState::Initialise( Engine * eng )
{
    text_manager.Initialise("data\\fonts\\consola.ttf");
    //TextManager * text_manager = new TextManager;
    //SDL_Surface * surface = eng->GetRendererPtr()->GetScreenSurface();
    text_manager.AddMessage("Fuck off.", 1,1);
    //text_manager->Render(surface);

    return true;
}

void MenuState::CleanUp(){}
void MenuState::Pause(){}
void MenuState::Resume(){}
void MenuState::HandleEvent(Engine * eng){}
void MenuState::Update(Engine * eng){}
void MenuState::Render(Engine * eng) 
{
    eng->GetRendererPtr()->BeginScene();
    SDL_Surface * surface =  eng->GetRendererPtr()->GetScreenSurface();
    text_manager.Render(surface);
    eng->GetRendererPtr()->EndScene();
}