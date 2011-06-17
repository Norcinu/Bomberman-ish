#include "BotEntity.h"
#include "Visualisation.h"
#include "BotStates.h"
#include "State.h"
#include "StateMachine.h"

BotEntity::BotEntity(void)
{
	/*state_machine = new entityFSM::StateMachine<BotEntity>(this);
	state_machine->ChangeState(entityFSM::WanderState::GetInstance());*/
}


BotEntity::~BotEntity(void)
{
	delete state_machine;
}

void BotEntity::DoAnimation()
{
}

void BotEntity::OnCollision(const BaseEntity * ent)
{
}

void BotEntity::Update()
{
}

void BotEntity::Render(const double dt, Visualisation * vis)
{

}