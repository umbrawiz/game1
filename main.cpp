#include "Func.h"
#include "Object.h"
#include "map.h"
#include "Character.h"
#undef main

Object background;

bool initSDL()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) return false;


    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("Pacman",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }

        // khoi tao che do font chu
        if (TTF_Init() == -1)
        {
            success = false;
        }

        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            success = false;
        }
    }
    return success;

}
void LoadBackground() {
	background.Load_Image("img/test.png", g_screen);
}
int main(int argc, char* argv[]) {
	if (initSDL() == false)
		return -1;

	LoadBackground();
	gamemap g_map;
	g_map.loadmap("map/mapinfo.dat");
	g_map.loadtile(g_screen);

	g_music = Mix_LoadMUS("sound//Test.mp3");

	Char player;
	player.Load_Img("img//Down.png", g_screen);
	player.animation();


	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT || (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_ESCAPE)) {
				quit = true;
			}
			player.KeyPress(g_event, g_screen);
		}

        if (Mix_PlayingMusic() == 0)
        {
            if (Mix_PlayMusic(g_music, -1) == -1)
            {
                return -1;
            }
        }

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);
		background.render(g_screen, NULL);
		Map new_map = g_map.getmap();
		player.spawn(new_map);
		g_map.ChangeMap(new_map);
		g_map.draw(g_screen);
		player.Print(g_screen);
		SDL_RenderPresent(g_screen);
		
		
	}
	return 0;
}
