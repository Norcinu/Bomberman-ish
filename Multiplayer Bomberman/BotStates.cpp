#include "BotStates.h"
#include "BotEntity.h"

namespace entityFSM
{
	WanderState::WanderState(void)
	{
	}

	WanderState::~WanderState(void)
	{
	}

	WanderState* WanderState::GetInstance()
	{
		static WanderState instance;
		return &instance;
	}

	void WanderState::Enter(BotEntity * owner)
	{
	}

	void WanderState::Execute(BotEntity * owner)
	{
	}

	void WanderState::Exit(BotEntity * owner)
	{
	}

	// Idle state.

	IdleState::IdleState()
	{
	}

	IdleState::~IdleState()	
	{
	}
	
	IdleState * IdleState::GetInstance()
	{
		IdleState instance;
		return &instance;
	}

	void IdleState::Enter(BotEntity * owner)
	{
	}

	void IdleState::Execute(BotEntity * owner)
	{
	}

	void IdleState::Exit(BotEntity * owner)
	{
	}
}