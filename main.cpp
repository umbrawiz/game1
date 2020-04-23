#include "Func.h"
#include "Object.h"
#undef main

Object background;

bool Init() {
	bool check = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Rambo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL) {
		check = false;
	}
	else {
		g_screen = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
	}
	return check;
}

bool loadbackground() {
	bool r = background.Load_Image("terra.png", g_screen);
	if (r == false) return false;
	return true;
}
int main(int argc, char* argv[]) {
	return 0;
}
