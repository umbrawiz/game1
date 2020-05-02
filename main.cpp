#include "Func.h"
#include "Object.h"
#include "map.h"
#undef main

Object background;

void initSDL()
{
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
}
void LoadBackground() {
	background.Load_Image("img/test.png", g_screen);
}
int main(int argc, char* argv[]) {
	initSDL();
	LoadBackground();
	gamemap g_map;
	g_map.loadmap("map/map01.dat");
	g_map.loadtile(g_screen);

	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				quit = true;
			}
		}
		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);
		background.render(g_screen, NULL);
		g_map.draw(g_screen);
		SDL_RenderPresent(g_screen);
	}
	return 0;
}
