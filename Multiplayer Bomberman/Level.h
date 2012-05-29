#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <string>
#include <vector>
#include "maths.h"
#include "Rectangle.h"

typedef unsigned int Uint32;

struct tile_t
{
	bool is_walkable;
	int id;
	math::Vector2 pos;
	Uint32 tile_state;
	rec::Rectangle collision_box;

	bool PositionPredicate(const math::Vector2& rhs) const
	{
		return pos == rhs;
	}
};

template <class Tile>
struct TileComparison_t
{
	bool operator()(const Tile& t1, const Tile& t2)
	{
		return t1.pos == t2.pos;
	}
};

enum TILE_STATES
{
	BRICK = 0x01,
	DESTROYABLE = 0x02,
	IS_DESTROYED = 0x04,
	NOT_DESTROYABLE = 0x08,
	SPAWN_POINT = 0x16,
	EMPTY = 0x32
};

struct SpawnPoint_t
{
	bool is_available;
	math::Vector2 position;

	SpawnPoint_t(math::Vector2& pos) : is_available(true), position(pos) {}
	
	bool ComparePosition(const math::Vector2& rhs) const
	{
		return position == rhs;
	}
};

class Visualisation; 

class Level
{
public:
	Level();
	Level(int tw, int th, int ntw, int nth);
	Level(Level * copy);

	bool LoadData(const std::string& filename, const int first_sprite, const int second_sprite );
	~Level();
	
	void Render(Visualisation * vis);
	bool IsWalkable(const math::Vector2& position);
	bool IsValidTile(const int x, const int original) const;
	bool CheckTile(const math::Vector2& tile_position, rec::Rectangle& ent_rec);
	
	void SurroundingTiles(std::vector<tile_t*>& s, const math::Vector2& tile_position);
	math::Vector2 TileDimensions() { return math::Vector2(tile_width, tile_height); }
	math::Vector2& DestinationTile(const math::Vector2 destination);
	math::Vector2 GetRandomWalkableTile();

	void GetSpawnPoints(std::vector<SpawnPoint_t*>& sp);
	void SetTileState(const math::Vector2& position, Uint32 new_states);

	math::Vector2 GetCameraPosition() const { return camera_position; }

	typedef std::vector<tile_t*>::iterator tile_itor;

private:
	std::vector<tile_t*> tiles;
	std::vector<SpawnPoint_t*> spawn_points;
	int tile_width;
	int tile_height;
	int num_tiles_wide;
	int num_tiles_high;
	int max_width;
	int max_height;
	math::Vector2 camera_position;
};

#endif
