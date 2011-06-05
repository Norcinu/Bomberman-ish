#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include "maths.h"

class Level;

struct node_t 
{
	int id;
	int parent_id;
	int h_score;
	int g_score;
	math::Vector2 position;

	node_t() : id(0), parent_id(0), h_score(0), g_score(0), position() {}
	
	node_t(int id_, int parent_id_, int h_, int g_, math::Vector2 pos) : id(id_),
		parent_id(parent_id_), h_score(h_), g_score(g_), position(pos) {}

	int FValue() const { return g_score + h_score; }

#ifdef _DEBUG
	friend std::ostream& operator<<(std::ostream& os, const node_t& node)
	{
		return os << node.id << " " << node.parent_id << " " << node.h_score << 
			" " << node.g_score << " " << node.position << std::endl;
	}
#endif

};

typedef std::vector<node_t>::iterator node_itor;

class AStar
{
public:
	AStar();
	AStar(Level * l);
	
	~AStar();

	int CalculateH(const math::Vector2& pos, const math::Vector2 &dest);
	int CalculateG(const math::Vector2& pos, const math::Vector2& parent_pos, const int parent_g);
	void Search(std::vector<node_t>& path, const math::Vector2& position, const math::Vector2& goal);
	
private:
	Level *level_copy;
	std::vector<node_t> open_list;
	std::vector<node_t> closed_list;
	std::vector<node_t> successors;
};

#endif
