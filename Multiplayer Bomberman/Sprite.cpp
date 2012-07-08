#include "Sprite.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <SDL_opengl.h>
#include "Common.h"

#pragma warning(disable:4244)

inline int ConvertStringToInt(const std::string& s)
{
	return atoi(s.c_str());
}

Sprite::Sprite() : sprite(nullptr), frame_height(32), frame_width(32)
{
}

Sprite::Sprite(SDL_Surface * surface) : sprite(surface), frame_height(32), frame_width(32)
{
}

Sprite::Sprite(SDL_Surface * surface, int fwidth, int fheight) : sprite(surface), 
	frame_width(fwidth), frame_height(fheight)
{
}

Sprite::~Sprite() 
{
	printf("deleting sprite\n");
	if (sprite) 
	{
		SDL_FreeSurface(sprite);
		sprite = nullptr;
	}

#ifdef USING_OPENGL
	glDeleteTextures(1, &texture);
#endif
}

bool Sprite::Load( const std::string& filename )
{
	std::fstream config(filename.c_str());
	if (!config)
	{
		std::cout << "Error opening sprite config file : " << filename << std::endl;
		return false;
	}

	std::string line;
	std::vector<std::string> description;
	int start_frame;
	
	while(std::getline(config, line)) 
	{
		size_t pos = line.find(" ")+1;
        
        // check for comments
        if (line[0] == '#')
            continue;
        
        std::string temp = line.substr(pos);
		description.push_back(temp);
	}

	config.close();

	sprite = SDL_LoadBMP(description[0].c_str());	
	frame_width = ConvertStringToInt(description[1]);
	frame_height = ConvertStringToInt(description[2]);
	start_frame = ConvertStringToInt(description[3]);
    name = common::FStripPathAndExtension(description[0]);
    
	if (sprite == nullptr) 
		return false;

	Uint32 colourkey = SDL_MapRGB(sprite->format, 255, 0, 255);
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colourkey);

#ifdef _DEBUG
	printf ("sprite w = %d.\n", sprite->clip_rect.w);
	printf ("sprite h = %d.\n", sprite->clip_rect.h);
	printf ("sprite x = %d.\n", sprite->clip_rect.x);
	printf ("sprite y = %d.\n", sprite->clip_rect.y);
#endif

	source.h = frame_height;
	source.w = frame_width;

#pragma region OPENGL_LOAD
#ifdef USING_OPENGL
	nOfColors = sprite->format->BytesPerPixel;
	if (nOfColors == 4)     // contains an alpha channel
	{
		if (sprite->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	} else if (nOfColors == 3)     // no alpha channel
	{
		if (sprite->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	} else {
		printf("warning: the image is not truecolor..  this will probably break\n");
		// this error should not go unhandled
	}

	// Have OpenGL generate a texture object handle for us
	glGenTextures( 1, &texture );

	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, texture );

	// Set the texture's stretching properties
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, sprite->w, sprite->h, 0,
		texture_format, GL_UNSIGNED_BYTE, sprite->pixels );
#endif
#pragma endregion OPENGL_LOAD

	return true;
}

void Sprite::Render( SDL_Surface * screen, const math::Vector2& frame, /*const*/ math::Vector2& position )
{
	assert(screen);

#ifndef USING_OPENGL
	if (position.x < 0)
		position.x = 0.f;

	if (position.x >  640-frame_width) 
		position.x = 640-frame_width;

	if (position.y < 0)
		position.y = 0.f;

	if (position.y >  480-frame_height)
		position.y =  480-frame_height;
	
	rec.x = static_cast<int>(position.x);
	rec.y = static_cast<int>(position.y);

	source.x = static_cast<int>(frame.x);
	source.y = static_cast<int>(frame.y);

	SDL_BlitSurface(sprite, &source, screen, &rec);

#pragma region OPENGL_RENDERING
#else USING_OPENGL
	glLoadIdentity();
	glTranslatef(rec.x, rec.y, 0 ); // was position
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glBegin(GL_QUADS); 
		//Bottom-left vertex (corner)
		glTexCoord2i(0,0);
		glVertex2i(source.x, source.y); // source.x, source.y
		//Bottom-right vertex (corner)
		glTexCoord2i(1,0);
		glVertex2i(source.x+frame_width, source.y);
		//Top-right vertex (corner)
		glTexCoord2i(1,1);
		glVertex2i(source.x+frame_width, source.y+frame_height);
		//Top-left vertex (corner)
		glTexCoord2i(0,1);
		glVertex2i(source.x, source.y+frame_height);
	glEnd();
    glLoadIdentity();
#endif
#pragma endregion OPENGL_RENDERING

}

Uint32 Sprite::GetPixel32(int x, int y)
{
    Uint32 *pixels = (Uint32 *)sprite->pixels;
    return pixels[ (y * sprite->w)  + x ];
}