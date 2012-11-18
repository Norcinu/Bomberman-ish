#ifndef GAMEMENU_H
#define GAMEMENU_H

class Visualisation;
class Messenger;

class GameMenu
{
public:
	GameMenu();
    GameMenu(Messenger * msg, Visualisation * vis);
	~GameMenu(void);

    bool Initialise();
    void Render();
    void Update();
    void CleanUp();

private:
    Messenger * gameMessages;
    Visualisation * renderer;
};

#endif
