#ifndef BASESTATE_H
#define BASESTATE_H

class Engine;

class BaseState
{
public:
	virtual ~BaseState(void) {}

	virtual bool Initialise(Engine * eng) = 0;
	virtual void CleanUp() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void HandleEvent(Engine * eng) = 0;
	virtual void Update(Engine * eng) = 0;
	virtual void Render(Engine * eng) = 0;

	void ChangeState(Engine * eng, BaseState * state);

protected:
	BaseState(void) : change_state(false) {}
	bool change_state;
};

#endif
