#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include "maths.h"
#include "MessageEvent.h"


class Visualisation;
class Timer;
class Level;
class BaseEntity;
class Explosion;
class BombEntity;
class Messenger;

struct EntitySystem;
struct SpawnPoint_t;

const int MAX_PLAYERS = 4;
const int MAX_SPAWNPOINTS = 4;
const int MAX_BOMBS = 50; 
const int NUM_EXPLOSIONS = 25; //100
const int MAX_DRAWN_EXPLOSIONS = 10;

class World
{
public:
	World(void);
	World(Messenger * msg);
	~World(void);

	bool Initialise(const std::string& assets, Visualisation * vis);
	bool ChangeLevel(const std::string& level_name);
	bool IsCollideable(const BaseEntity* ent1, const BaseEntity* ent2) const;

	void Move(const int id, const math::Vector2& direction);
	void Action(const int id);
	void AddPlayer(const int id);
	void Update();
	void Render(Visualisation * vis) const;
	void ParseMessage(const EventMessage_t& msg);

	math::Vector2& FindFirstSpawn() const;
	void FreeSpawnPoint(const math::Vector2& position);

private:
	bool CheckBounds(const int id) const;
	void CleanUp();
	void CreateBombList(const int id);
	void CreateExplosionList(const int id);
	void ResetBomb(const int id);

private:
	std::vector<BaseEntity*> entities;
	std::vector<SpawnPoint_t*> spawns;
	std::vector<BombEntity*> bomb_list;
	std::vector<Explosion*> explosion_list;

	Timer * game_timer;
	Level * current_level;
	Messenger * messages;

	//EntitySystem entity_system;
	//Entity game_entities[MAX_PLAYERS];

	int tick_rate;
	double update_delta;

	typedef std::vector<BaseEntity*>::iterator ent_itor;
	typedef std::vector<BaseEntity*>::const_iterator const_ent_itor;
	typedef std::vector<BombEntity*>::iterator bomb_itor;
	typedef std::vector<BombEntity*>::const_iterator const_bomb_itor;
	typedef std::vector<Explosion*>::iterator explosion_itor;
	typedef std::vector<Explosion*>::const_iterator const_exposion_itor;
};			

#endif
