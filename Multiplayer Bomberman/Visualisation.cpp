#include "Visualisation.h"
#include "Sprite.h"
#include <cassert>
#include <iostream>
#include <string>
#include <SDL_opengl.h>

#pragma warning(disable:4244)

//#define USING_OPENGL

// re-write this to accept a string describing the renderer type.
// i.e vis->RenererBackend("OpenGL") vis->RendererBackEnd("SDL")
// impl = new ImplType;

Visualisation::Visualisation(void)
{
	screen = nullptr;
	screen_width  = 512;
	screen_height = 512;
	screen_depth  = 24;
	
	full_screen = false;

	ui_rectangle.h = 32;
	ui_rectangle.w = screen_width;
	ui_rectangle.x = 0;
	ui_rectangle.y = screen_height - 32;
}

Visualisation::~Visualisation(void)
{
	SDL_FreeSurface(screen);
	Quit(0);
	SDL_Quit();
}

bool Visualisation::Initialise(const int height, const int width, bool fscreen) 
{
	screen_height = height;
	screen_width = width;
	full_screen = fscreen;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
		return false;

#ifdef USING_OPENGL
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,         32);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,      8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,     8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	screen = SDL_SetVideoMode(screen_width, screen_height, screen_depth, SDL_OPENGL);

	glEnable( GL_TEXTURE_2D );
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glViewport( 0, 0, screen_width, screen_height);
	glClear( GL_COLOR_BUFFER_BIT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0.0f, screen_width, screen_height, 0.0f, -1.0f, 1.0f);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

#else
	if (!full_screen)
		screen = SDL_SetVideoMode(screen_width, screen_height, screen_depth, 
		SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT);
	else
		screen = SDL_SetVideoMode(screen_width, screen_height, screen_depth, 
		SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT | SDL_FULLSCREEN);
#endif 

	SDL_WM_SetCaption("Steven Gleed - Bomberman Client 2010 - 2011", nullptr);
	
	return true;
}

bool Visualisation::AddSprite( int * id, const std::string& file )
{
	Sprite *spr = new Sprite;
	
	if (!spr->Load(file))
	{
		*id = -1;
		return false;
	}

	sprites.push_back(spr);
	*id = static_cast<int>(sprites.size() - 1);
	
	/*int colour_key = SDL_MapRGB(screen->format, 0, 255, 255);
	SDL_SetColorKey(spr->RawSprite(), SDL_SRCCOLORKEY | SDL_RLEACCEL, colour_key);*/
	int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(spr->RawSprite(), SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

	printf("sprite added ok. ID = %d\n", *id);
	return true;
}

void Visualisation::ClearScreen()
{
	//CalculateFPS();		

#ifdef USING_OPENGL
	glClear(GL_COLOR_BUFFER_BIT);
#else
	SDL_FillRect(SDL_GetVideoSurface(), nullptr, SDL_MapRGB(SDL_GetVideoSurface()->format, 0,0,0));
#endif
	
}

void Visualisation::ClearScreen( Uint32 colour )
{
	SDL_FillRect(screen, nullptr, colour);
}

void Visualisation::CalculateFPS()
{	
	static unsigned long lastTime = SDL_GetTicks();
	static long frames = 0;

	int newTime = SDL_GetTicks();

	if(newTime - lastTime > 1000)
	{
		unsigned long newFPS = (frames * 1000 / (newTime - lastTime));
		printf("FPS : %d\n", newFPS);
		lastTime = newTime;
		frames = 0;
	}
	frames++;
}

void Visualisation::FillRectangle( const SDL_Rect & rec, const std::string& col )
{
}

void Visualisation::Quit( const int exit_code )
{
	printf("Quitting with code : %d\n", exit_code);
}

void Visualisation::BeginScene()
{
#ifdef USING_OPENGL	
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
#else
	ClearScreen(SDL_MapRGB(screen->format, 0,0,0)); 
#endif 
}

void Visualisation::EndScene()
{
#ifdef USING_OPENGL
	SDL_GL_SwapBuffers();
#else
	SDL_Flip(screen);
#endif
	CalculateFPS();
}

void Visualisation::DrawSprite( const int id, const math::Vector2& frame, /*const */math::Vector2& pos )
{
	sprites[id]->Render(screen, frame, pos);
}

void Visualisation::DrawLine( math::Vector2& p1, math::Vector2& p2, Uint32 colour /*= 0*/ )
{
	if (colour != 0)
		printf("colour is not 0\n");

	double slope = static_cast<double>((p2.y - p1.y)) / static_cast<double>((p2.x - p1.x));
	for (int x = p1.x; x <= p2.x; x++)
	{
		int y = static_cast<int>((slope * (x - p1.x)) + p1.y);
		SetPixel(x, y, colour);
	}
}

void Visualisation::SetPixel( int x, int y, const Uint32 colour )
{
	int bpp = screen->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

	switch(bpp) {
	case 1:
		*p = colour;
		break;

	case 2:
		*(Uint16 *)p = colour;
		break;

	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
		{
			p[0] = (colour >> 16) & 0xff;
			p[1] = (colour >> 8) & 0xff;
			p[2] = colour & 0xff;
		} 
		else 
		{
			p[0] = colour & 0xff;
			p[1] = (colour >> 8) & 0xff;
			p[2] = (colour >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = colour;
		break;
	}
}

Uint32 Visualisation::GetPixel( SDL_Surface * surface, int x, int y )
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[(y * surface->w) + x];
}

void Visualisation::ClearGraphicSet()
{	
	while (!sprites.empty())
	{
		sprites.pop_back();
	}
}

void Visualisation::FillRectangle( const rec::Rectangle& p )
{
	SDL_Rect r;
	r.x = p.left;
	r.y = p.top;
	r.h = p.bottom;
	r.w = p.right;
	SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, 255, 0, 0));
}
