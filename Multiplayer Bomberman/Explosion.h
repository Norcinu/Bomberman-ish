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

private:
	int x;
	int y;
	int x_bounds;
	int y_bound;
};

#endif
