#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "BaseState.h"

class World;

class PlayState :	public BaseState
{
public:	
	PlayState();
	~PlayState(void);

	bool Initialise(Engine * eng);
	void CleanUp();
	void Pause();
	void Resume();
	void HandleEvent(Engine * eng);
	void Update(Engine * eng);
	void Render(Engine * eng);

	static PlayState* GetInstance() { return &instance; }

private:
	static PlayState instance;
};

#endif
