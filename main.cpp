#include "Func.h"
#include "Object.h"
#include "map.h"
#include "Character.h"
#undef main

Object background;

void initSDL()
{
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
}
//void LoadBackground() {
	//background.Load_Image("img/test.png", g_screen);
//}
int main(int argc, char* argv[]) {
	initSDL();
	//LoadBackground();
	gamemap g_map;
	g_map.loadmap("map/mapinfo.dat");
	g_map.loadtile(g_screen);
	
	Char player;
	player.Load_Img("img//Up.png", g_screen);
	player.animation();

	Map game_map = g_map.gmap;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT || (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_ESCAPE)) {
				quit = true;
			}
			player.KeyPress(g_event, g_screen);
		}
		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		//SDL_RenderClear(g_screen);
		background.render(g_screen, NULL);
		player.spawn(game_map);
		g_map.draw(g_screen);
		player.Print(g_screen);
		SDL_RenderPresent(g_screen);
	}
	return 0;
}
