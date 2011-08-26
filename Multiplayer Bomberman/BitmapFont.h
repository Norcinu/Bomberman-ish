#ifndef BITMAPFONT_H
#define BITMAPFONT_H

#include <SDL/SDL.h>
#include <string>
#include <vector>

class Sprite;

//re-write this using a map.
class BitmapFont
{
public:
	BitmapFont(void);
	BitmapFont(SDL_Surface *surface);
	~BitmapFont(void);

	bool Initialise(const std::string& filename);
	void DrawString(int x, int y, std::string& msg, SDL_Surface * surface);

private:
	//SDL_Surface * bitmap;
	Sprite * bitmap;
	int new_line;
	int space;
	//std::map<char, SDL_Rect> chars;
	//SDL_Rect chars[256];
	std::vector<SDL_Rect> chars;
};

#endif
