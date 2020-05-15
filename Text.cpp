#include "Text.h"

Text::Text() {
	text_clr.r = 0;
	text_clr.g = 0;
	text_clr.b = 0;
	texture = NULL;
}

Text::~Text() {

}

bool Text::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text_val.c_str(), text_clr);
	if (surface) {
		texture = SDL_CreateTextureFromSurface(screen, surface);
		width = surface->w;
		height = surface->h;
		SDL_FreeSurface(surface);
	}
	return texture != NULL;
}

void Text::Free() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void Text::SetColor(Uint8 red, Uint8 green, Uint8 blue) {
	text_clr.r = red;
	text_clr.g = green;
	text_clr.b = blue;
}

void Text::SetColor(int type) {
	if (type == RED) {
		text_clr.r = 255;
		text_clr.g = 0;
		text_clr.b = 0;
	}
	else if (type == WHITE) {
		text_clr.r = 255;
		text_clr.g = 255;
		text_clr.b = 255;
	}
	else if (type == BLACK) {
		text_clr.r = 0;
		text_clr.g = 0;
		text_clr.b = 0;
	}
	else if (type == GRAY) {
		text_clr.r = 128;
		text_clr.g = 128;
		text_clr.b = 128;
	}
	else if (type == SILVER) {
		text_clr.r = 192;
		text_clr.g = 192;
		text_clr.b = 192;
	}
	else if (type == YELLOW) {
		text_clr.r = 230;
		text_clr.g = 230;
		text_clr.b = 0;
	}
}

void Text::RenderText(SDL_Renderer* screen, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Rect* clip) {
	SDL_Rect renderquad = { x,y,width,height };
	if (clip != NULL) {
		renderquad.w = clip->w;
		renderquad.h = clip->h;
	}
	SDL_RenderCopyEx(screen, texture, clip, &renderquad, angle, center, flip);
}


