#include "GameMenu.h"
#include "Visualisation.h"
#include "Messenger.h"

GameMenu::GameMenu(void) : renderer(nullptr), gameMessages(nullptr)
{
}

GameMenu::GameMenu(Messenger * msg, Visualisation * vis) : renderer(vis), gameMessages(msg)
{
}

GameMenu::~GameMenu(void)
{
    CleanUp();
}

void GameMenu::CleanUp()
{

}

bool GameMenu::Initialise()
{
    int id = 0;
    renderer->AddSprite(&id, "data\\bmp\\new.bmp");
    renderer->AddSprite(&id, "data\\bmp\\load.bmp");
    renderer->AddSprite(&id, "data\\bmp\\menu_arrow.bmp");

    return true;
}

void GameMenu::Update()
{

}

void GameMenu::Render()
{
    for (auto i = 0; i < renderer->GetNumberOfSprites(); i++) {
        //renderer->DrawSprite(i, math::Vector2(0,0), )
    }
}