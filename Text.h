#ifndef  TEXT_H
#define TEXT_H

#include "Func.h"
#include "Object.h"

class Text
{
public:
    Text(void);
    ~Text(void);

    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };

    bool loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen);
    void Free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(int type);

    void RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    void SetText(const std::string& text) { str_val = text; }
    std::string GetText() const { return str_val; }

private:
    std::string str_val;
    SDL_Color text_color;
    SDL_Texture* texture;
    int width;
    int height;

};
#endif

