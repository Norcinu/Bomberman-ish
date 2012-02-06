#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <string>

class Explosion
{
public:
	Explosion(void);
	~Explosion(void);

	void LoadSprite(const std::string& filename);
	void DrawExplosion(const int x, const int y);
	
	bool Active() const { return active; }
	void Active(bool val) { active = val; }
	
	// draw sprite and then increase drawn rectangle after 
	// some time, when reaches maximum, start decreasing.
	// draw from the middle.
private:
	bool active;
	int x;
	int y;
	int x_bounds;
	int y_bounds;
	int sprite_id;
};

#endif
