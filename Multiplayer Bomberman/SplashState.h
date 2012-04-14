#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include "BaseState.h"

class Engine;
class Timer;

class SplashState : public BaseState
{
public:
	SplashState();
	~SplashState(void);

	bool Initialise(Engine * eng);
	void CleanUp();
	void Pause();
	void Resume();
	void HandleEvent(Engine * eng);
	void Update(Engine * eng);
	void Render(Engine * eng);

	static SplashState* GetInstance() { return &instance; }

private:
	static SplashState instance;
	int splash_sprite_id;
	unsigned int splash_run_time;
	Timer * running_timer;
};

#endif
