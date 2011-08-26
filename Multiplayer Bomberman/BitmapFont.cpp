#include "BitmapFont.h"
#include "Sprite.h"

BitmapFont::BitmapFont(void) : bitmap(NULL)
{
	chars.reserve(256);
}

BitmapFont::BitmapFont(SDL_Surface * surface) : bitmap(NULL)
{
	chars.reserve(256);
}

BitmapFont::~BitmapFont(void)
{
	if (bitmap)
		delete bitmap;
}

bool BitmapFont::Initialise(const std::string& filename)
{
	//if (surface == nullptr)
		//return false;

	bitmap = new Sprite;
	if (bitmap == NULL)
		return false;

	if (!bitmap->Load(filename))
		return false;

	Uint32 bg_colour = SDL_MapRGB(bitmap->RawSprite()->format, 0, 255, 255);
	SDL_SetColorKey(bitmap->RawSprite(), SDL_SRCCOLORKEY | SDL_RLEACCEL, bg_colour);
	
	int cellW = bitmap->RawSprite()->w / 16;
    int cellH = bitmap->RawSprite()->h / 16;

    //New line variables
    int top = cellH;
    int baseA = cellH;

    //The current character we're setting
    int currentChar = 0;

    //Go through the cell rows
    for( int rows = 0; rows < 16; rows++ )
    {
        //Go through the cell columns
        for( int cols = 0; cols < 16; cols++ )
        {
            //Set the character offset
			SDL_Rect r;
			r.x=cellW * cols;
			r.y=cellH * rows;
			r.w=cellW;
			r.h=cellH;
			chars.push_back(r);
          //  chars[ currentChar ].x = cellW * cols;
           // chars[ currentChar ].y = cellH * rows;

            //Set the dimensions of the character
            //chars[ currentChar ].w = cellW;
            //chars[ currentChar ].h = cellH;

            //Find Left Side
            //Go through pixel columns
            for( int pCol = 0; pCol < cellW; pCol++ )
            {
                //Go through pixel rows
                for( int pRow = 0; pRow < cellH; pRow++ )
                {
                    //Get the pixel offsets
                    int pX = ( cellW * cols ) + pCol;
                    int pY = ( cellH * rows ) + pRow;

                    //If a non colorkey pixel is found
                    if( bitmap->get_pixel32(pX, pY) != bg_colour )
                    {
                        //Set the x offset
                        chars[ currentChar ].x = pX;

                        //Break the loops
                        pCol = cellW;
                        pRow = cellH;
                    }
                }
            }

            //Find Right Side
            //Go through pixel columns
            for( int pCol_w = cellW - 1; pCol_w >= 0; pCol_w-- )
            {
                //Go through pixel rows
                for( int pRow_w = 0; pRow_w < cellH; pRow_w++ )
                {
                    //Get the pixel offsets
                    int pX = ( cellW * cols ) + pCol_w;
                    int pY = ( cellH * rows ) + pRow_w;

                    //If a non colorkey pixel is found
                    if( bitmap->get_pixel32(pX, pY) != bg_colour )
                    {
                        //Set the width
                        chars[ currentChar ].w = ( pX - chars[ currentChar ].x ) + 1;

                        //Break the loops
                        pCol_w = -1;
                        pRow_w = cellH;
                    }
                }
            }

            //Find Top
            //Go through pixel rows
            for( int pRow = 0; pRow < cellH; pRow++ )
            {
                //Go through pixel columns
                for( int pCol = 0; pCol < cellW; pCol++ )
                {
                    //Get the pixel offsets
                    int pX = ( cellW * cols ) + pCol;
                    int pY = ( cellH * rows ) + pRow;

                    //If a non colorkey pixel is found
                    if( bitmap->get_pixel32(pX, pY) != bg_colour )
                    {
                        //If new top is found
                        if( pRow < top )
                        {
                            top = pRow;
                        }

                        //Break the loops
                        pCol = cellW;
                        pRow = cellH;
                    }
                }
            }

            //Find Bottom of A
            if( currentChar == 'A' )
            {
                //Go through pixel rows
                for( int pRow = cellH - 1; pRow >= 0; pRow-- )
                {
                    //Go through pixel columns
                    for( int pCol = 0; pCol < cellW; pCol++ )
                    {
                        //Get the pixel offsets
                        int pX = ( cellW * cols ) + pCol;
                        int pY = ( cellH * rows ) + pRow;

                        //If a non colorkey pixel is found
                        if( bitmap->get_pixel32(pX, pY) != bg_colour )
                        {
                            //Bottom of a is found
                            baseA = pRow;

                            //Break the loops
                            pCol = cellW;
                            pRow = -1;
                        }
                    }
                }
            }

            //Go to the next character
            currentChar++;
        }
    }

    //Calculate space
    space = cellW / 2;

    //Calculate new line
    new_line = baseA - top;

    //Lop off excess top pixels
    for( int t = 0; t < 256; t++ )
    {
        chars[ t ].y += top;
        chars[ t ].h -= top;
    }

	return true;
}

void BitmapFont::DrawString(int x, int y, std::string& msg, SDL_Surface * surface)
{
	 //Temp offsets
    int X = x, Y = y;

    //If the font has been built
    if( bitmap != NULL )
    {
        //Go through the text
        for( int show = 0; msg[ show ] != '\0'; show++ )
        {
            //If the current character is a space
            if( msg[ show ] == ' ' )
            {
                //Move over
                X += space;
            }
            //If the current character is a newline
            else if( msg[ show ] == '\n' )
            {
                //Move down
                Y += new_line;

                //Move back
                X = x;
            }
            else
            {
                //Get the ASCII value of the character
                int ascii = (unsigned char)msg[ show ];

                //Show the character
                //apply_surface( X, Y, bitmap, surface, &chars[ ascii ] );
				SDL_Rect offset;

				//Get offsets
				offset.x = X;
				offset.y = Y;

				//Blit
				SDL_BlitSurface( bitmap->RawSprite(), &chars[ascii], surface, &offset );
                //Move over the width of the character with one pixel of padding
                X += chars[ ascii ].w + 1;
            }
        }
    }
}
