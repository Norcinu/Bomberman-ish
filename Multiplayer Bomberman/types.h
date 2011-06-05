#ifndef TYPES_H
#define TYPES_H

typedef enum 
{
	PLAYER_1 = 1,
	PLAYER_2,
	PLAYER_3,
	PLAYER_4,
	//DESTRUCTIBLE,
	//SOLID,
	PICKUP,
	NONE
} EntitySide;

typedef enum
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
} EntityDirection;

#endif
