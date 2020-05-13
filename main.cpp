#include "Func.h"
#include "Object.h"
#include "map.h"
#include "Character.h"
#include "Text.h"
#undef main

Object menu;
Object background;
TTF_Font* font;
TTF_Font* menu_font;

bool initSDL()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (ret < 0) return false;


    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("Pacman",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

        if (TTF_Init() == -1)
        {
            success = false;
        }

        menu_font = TTF_OpenFont("font//Andy Bold.ttf", 70);
        font = TTF_OpenFont("font//Andy Bold.ttf", 50);
        if (font != NULL && menu_font != NULL) {
            success = true;
        }

        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            success = false;
        }
    }
    return success;

}
void LoadBackground() {
    menu.Load_Image("img/terra.png", g_screen);
	background.Load_Image("img/white.png", g_screen);
}
int main(int argc, char* argv[]) {
	if (initSDL() == false) return -1;
    LoadBackground();
	gamemap g_map;
	g_map.loadmap("map/mapinfo.dat");
	g_map.loadtile(g_screen);

	g_music = Mix_LoadMUS("sound/Test.mp3");
    g_menu_music = Mix_LoadMUS("sound/g_menu.mp3");
    Mix_VolumeMusic(80);

	Char player;
    player.SetSpawnPos(600, 350);
	player.Load_Img("img/Down.png", g_screen);
	player.animation();

    int score_count;
    Text score;
    score.SetColor(Text::BLACK);

    Text menu_tile;
    menu_tile.SetColor(Text::WHITE);
    

	bool quit = false;
    
    bool ready = false;
   
    while(!ready){
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_KEYDOWN) {
                ready = true;
            }
            if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }

        if (Mix_PlayingMusic() == 0)
        {
            if (Mix_PlayMusic(g_menu_music, -1) == -1)
            {
                return -1;
            }
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        menu.render(g_screen, NULL);

        std::string str = "Press any key to continue";
        menu_tile.SetText(str);
        menu_tile.LoadFromRenderText(menu_font, g_screen);
        menu_tile.RenderText(g_screen, 280 , SCREEN_HEIGHT - 100);

        SDL_RenderPresent(g_screen);
    }
    Mix_FreeMusic(g_menu_music);

    

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

        score_count = player.GetScore();
        std::string current_score = std::to_string(score_count);
        score.SetText(current_score);
        score.LoadFromRenderText(font, g_screen);
        score.RenderText(g_screen, 0, 0);

		SDL_RenderPresent(g_screen);
	
	}

   

	return 0;
}
