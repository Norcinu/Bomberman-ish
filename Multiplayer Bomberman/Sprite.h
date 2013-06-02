#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_opengl.h>
#include <string>
#include "maths.h"

//#define USING_OPENGL

class Sprite
{
public:
	Sprite();
	Sprite(SDL_Surface * surface);
	Sprite(SDL_Surface * surface, int fwidth, int fheight);
	~Sprite();

	bool Load(const std::string& filename);
	void Render(SDL_Surface * screen, const math::Vector2& frame, math::Vector2& position);
	SDL_Rect SpriteRectangle() const { return rec; }
	SDL_Surface * RawSprite() const { return sprite; }

	Uint32 GetPixel32(int x, int y);

	int GetWidth() const { return sprite->clip_rect.w; }
	int GetHeight() const { return sprite->clip_rect.h; }
    std::string GetName() const { return name; }

private:
	SDL_Surface * sprite;
	
	SDL_Rect rec; //position
	SDL_Rect source;//whole image
	
	//int number_of_frames;
	int frame_width;
	int frame_height;

    std::string name;

#ifdef USING_OPENGL
	GLuint texture;
	GLenum texture_format;
	GLint  nOfColors;
#endif
};

#endif
