#include "Func.h"
#include "Object.h"
#include "map.h"
#undef main

Object background;

void initSDL()
{
	g_window = SDL_CreateWindow("Rambo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
}

int main(int argc, char* argv[]) {
	initSDL();
	gamemap g_map;
	g_map.loadmap("map/mapinfo.dat");
	g_map.loadtile(g_screen);

	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&g_event) == 1) {
			if (g_event.type = SDL_MOUSEBUTTONUP) {
				quit = true;
			}
		}
		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);
		background.render(g_screen, NULL);
		g_map.draw(g_screen);
		SDL_RenderPresent(g_screen);
	}
	return 0;
}
