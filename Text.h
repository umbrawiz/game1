#ifndef  TEXT_H
#define TEXT_H

#include "Func.h"
#include "Object.h"

class Text : public Object{
public:
	Text();
	~Text();

	enum color {
		RED = 0,
		WHITE = 1,
		BLACK = 2,
		GRAY = 3,
		SILVER = 4,
		YELLOW = 5,
	};

	bool LoadText(std::string path);
	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);

	void RenderText(SDL_Renderer* screen, int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE , SDL_Rect* clip = NULL);
	void SetText(const std::string& text) { text_val = text; }
	std::string GetText() const { return text_val; }
	void Free();

private:
	std::string text_val;
	SDL_Color text_clr;
	SDL_Texture* texture;
	int width;
	int height;

};

#endif

