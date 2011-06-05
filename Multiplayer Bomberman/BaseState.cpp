#include "BaseState.h"
#include "Engine.h"

void BaseState::ChangeState( Engine * eng, BaseState * state )
{
	eng->ChangeState(state);
}
