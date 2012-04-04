#include "TextManager.h"
#include <iostream>
#include <cassert>

TextManager::TextManager(void) : font(nullptr), font_size(12)
{
}

TextManager::~TextManager(void)
{
    for(text_info_itor it = ui_text.begin(); it != ui_text.end(); ++it)
    {
        delete *it;
    }

    TTF_CloseFont(font);
    TTF_Quit();

    font = nullptr;
}

bool TextManager::Initialise( const std::string& font_file )
{
    TTF_Init();
    font = TTF_OpenFont(font_file.c_str(), font_size);
    
    if (font == nullptr)
    {
        std::cerr << "Error opening font file : " << font_file << std::endl;
        return false;
    }

    return true;
}

void TextManager::AddMessage( const std::string& msg, int x, int y )
{
    TextInfo * info = new TextInfo(msg, x, y);
    info->font_colour.r = 0;
    info->font_colour.g = 128;
    info->font_colour.b = 0;
    if (!info) 
        std::cerr << "Error creating new text message : " << msg << std::endl;
    
    ui_text.push_back(info);
}

void TextManager::Render(SDL_Surface * screen)
{
    assert (screen != nullptr);

    SDL_Surface * text_area;
    SDL_Rect position;

    for (text_info_const_itor it = ui_text.begin(); it != ui_text.end(); ++it)
    {
        text_area = TTF_RenderText_Shaded(font, (*it)->message.c_str(),  
            (*it)->font_colour, (*it)->background_colour);
    
       /* text_area = TTF_RenderText_Blended(font, (*it)->message.c_str(),  
            (*it)->font_colour);*/

        position.x = (*it)->position_x;
        position.y = (*it)->position_y;

        SDL_BlitSurface(text_area, NULL, screen, &position);
    }
}

