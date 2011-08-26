#ifndef VISUALISATION_H
#define VISUALISATION_H

#include <string>
#include <vector>
#include <cassert>
#include <SDL/SDL.h>
#include "maths.h"
#include "Rectangle.h"

class Sprite;

class Visualisation 
{
public:
	Visualisation(void);
	~Visualisation(void);

	bool Initialise(const int height, const int width, bool fscreen=false);
	bool AddSprite(int * id, const std::string& file); 
	bool IsEmpty() const { return sprites.empty(); }

	void ClearScreen();
	void ClearScreen(Uint32 colour);
	void FillRectangle(const SDL_Rect & rec, const std::string& col); 
	void SetPixel(int x, int y, const Uint32 colour);
	
	void CalculateFPS();
	void Quit(const int exit_code);
	
	void ClearGraphicSet();
	void DrawSprite(const int id, const math::Vector2& frame, /*const*/ math::Vector2& pos);
	void DrawLine(math::Vector2& p1, math::Vector2& p2, Uint32 colour = 0);
	void FillRectangle(const rec::Rectangle& p);

	void BeginScene();
	void EndScene();
	
	Uint32 GetPixel(SDL_Surface * surface, int x, int y);
	SDL_Surface * GetScreenSurface() const { return screen; }
	
private:
	SDL_Surface * screen;
	bool full_screen;
	int screen_width;
	int screen_height;
	int screen_depth;
	std::vector<Sprite*> sprites;
	SDL_Rect ui_rectangle;
};

#endif
