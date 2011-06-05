#ifndef PLAYERSTATES_H
#define PLAYERSTATES_H

#include "State.h"

class BotEntity;

namespace entityFSM
{
	class WanderState : public entityFSM::State<BotEntity>
	{
	public:
		~WanderState(void);

		static WanderState * GetInstance();
		void Enter(BotEntity * owner);
		void Execute(BotEntity * owner);
		void Exit(BotEntity * owner);
	
	private:
		WanderState(void);
		WanderState(const WanderState& rhs);
		WanderState& operator=(const WanderState& rhs);
	};

	class IdleState : public entityFSM::State<BotEntity>
	{
	public:
		~IdleState();

		static IdleState * GetInstance();
		void Enter(BotEntity * owner);
		void Execute(BotEntity * owner);
		void Exit(BotEntity * owner);

	private:
		IdleState();
		IdleState(const IdleState& rhs);
		IdleState& operator=(const IdleState& rhs);
	};
}

#endif
