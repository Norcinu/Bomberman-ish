#ifndef ENTITYIMPL_H
#define ENTITYIMPL_H

#include "maths.h"
#include "Rectangle.h"
#include "Level.h"
#include "types.h"

struct EntityImpl_t
{
	bool active;
	bool moving;

	int id;
	int graphic_id;
	int animation_frame;
	int health;

	EntitySide side;
	EntityDirection direction;

	math::Vector2 position;
	math::Vector2 previous_position;
	math::Vector2 animation_position;

	rec::Rectangle collision_box;
	Level * level_copy;

	EntityImpl_t() : active(false), moving(false), id(0), graphic_id(0), animation_frame(0), side(NONE), health(100),
		direction(FORWARD), position(), previous_position(), collision_box(), animation_position(), level_copy(new Level) {}

	EntityImpl_t(const EntityImpl_t& e) : active(e.active), moving(e.moving), id(e.id), graphic_id(e.graphic_id), 
		animation_frame(e.animation_frame), side(e.side), direction(e.direction), position(e.position), health(e.health),
		previous_position(e.previous_position), collision_box(e.collision_box), animation_position(e.animation_position),
		level_copy(e.level_copy) {}

	~EntityImpl_t() 
	{
		/*if (level_copy)
			delete level_copy*/;
	}
};

#endif
