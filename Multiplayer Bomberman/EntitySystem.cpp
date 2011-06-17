#include "EntitySystem.h"

// Had to move these here because 
// BotStates.h was whining about objects already being declared.

EntitySystem *Entity::entity_system = 0;

Entity::Entity() 
{
}

