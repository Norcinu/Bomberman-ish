#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>

struct TextInfo
{
    int position_x;
    int position_y;
    std::string message;
    SDL_Color font_colour;
    SDL_Color background_colour;
    
    TextInfo(const std::string& msg, int x, int y) : 
        message(msg), position_x(x), position_y(y) {}
};

class TextManager
{
public:
    TextManager(void);
    ~TextManager(void);

    void AddMessage(const std::string& msg, int x, int y);
    void PrintAllUiText();
    void UpdateUiText(const std::string& new_message);
    void Render(SDL_Surface * screen);
    bool Initialise(const std::string& font_file);
    int GetFontSize() const { return font_size; }
    void SetFontSize(int val) { font_size = val; }

private:
   std::vector<TextInfo*> ui_text;
   TTF_Font * font;
   int font_size;
   
private:
    typedef std::vector<TextInfo*>::iterator text_info_itor;
    typedef std::vector<TextInfo*>::const_iterator text_info_const_itor;
};                   

#endif
