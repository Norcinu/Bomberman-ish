#include "PlayerEntity.h"
#include "EntityImpl.h"
#include "Visualisation.h"

PlayerEntity::PlayerEntity(void) //: impl(new EntityImpl_t)
{
	impl = new EntityImpl_t;
}

PlayerEntity::PlayerEntity(const EntityImpl_t& ei) // : impl(new EntityImpl_t(ei))
{
	impl = new EntityImpl_t(ei);
}

PlayerEntity::~PlayerEntity(void)
{
	//delete impl;
}
 
void PlayerEntity::Update()
{
	if (impl->health <= 0)
	{
		impl->active = false;
	}
}

void PlayerEntity::Render(const double dt, Visualisation * vis)
{
	if (impl->active) {
		vis->DrawSprite(impl->graphic_id, impl->animation_position, impl->position);
		//vis->DrawRectangle(impl->collision_box);
	}
}

void PlayerEntity::OnCollision(const BaseEntity *ent)
{

}

// 1  2  3  4   5   6   7   8
// 0 32 64 96 128 160 192 224 
void PlayerEntity::DoAnimation()
{
	if (impl->direction == LEFT)
	{
		if (impl->animation_position.x == 192)
			impl->animation_position.x = 224;
		else
			impl->animation_position.x = 192;
	}

	if (impl->direction == RIGHT)
	{
		if ( impl->animation_position.x == 64 )
			impl->animation_position.x = 96;
		else
			impl->animation_position.x = 64;
	}
	
	if (impl->direction == BACKWARD)
	{
		if ( impl->animation_position.x == 128 )
			impl->animation_position.x = 160;
		else
			impl->animation_position.x = 128;
	}
	
	if (impl->direction == FORWARD)
	{
		if ( impl->animation_position.x == 0 )
			impl->animation_position.x = 32;
		else
			impl->animation_position.x = 0;
	}
}
