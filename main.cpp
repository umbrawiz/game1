#include "Func.h"
#include "Object.h"
#include "map.h"
#include "Character.h"
#include "Text.h"
#undef main

Object menu;
Object background;
Object win_background;
Object lose_background;
TTF_Font* font;
TTF_Font* menu_font;
TTF_Font* menu_font_1;

bool CheckFocus(const int& x, const int& y, const SDL_Rect& rect) {
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) return true;
    return false;
}

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

        menu_font = TTF_OpenFont("font//Andy Bold.ttf", 50);
        menu_font_1 = TTF_OpenFont("font//Andy Bold.ttf", 70);
        font = TTF_OpenFont("font//Andy Bold.ttf", 40);
        if (font != NULL && menu_font != NULL && menu_font_1 !=NULL) {
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
    win_background.Load_Image("img/win.png", g_screen);
    lose_background.Load_Image("img/lose.png", g_screen);
}
int main(int argc, char* argv[]) {
    srand(time(NULL));
	if (initSDL() == false) return -1;
    LoadBackground();
    bool playing = true;

    static Mix_Chunk* g_eff = NULL;
    g_eff = Mix_LoadWAV("sound//Collect.wav");

    
    while (playing) {
        bool win;

        bool quit = false;

        bool ready = false;
        
        bool thinking = true;

        // MAP
        gamemap g_map;
        g_map.loadmap("map/mapinfo.dat");
        g_map.loadtile(g_screen);

        for (int i = 0; i < POKEBALLNUM; i++) {
            g_map.SetRandomPBPos();
        }

        for (int i = 0; i < SPIKENUM; i++) {
            g_map.SetRandomSPPos();
        }

        // MUSIC
        g_music = Mix_LoadMUS("sound/Test.mp3");
        g_menu_music = Mix_LoadMUS("sound/g_menu.mp3");
        g_result_music = Mix_LoadMUS("sound/g_result.mp3");
        Mix_VolumeMusic(80);


        SDL_Event m_event;
        int xm = 0;
        int ym = 0;

        // PLAYER
        Char player;
        player.SetSpawnPos(PLAYER_SPAWN_POINT_X , PLAYER_SPAWN_POINT_Y);
        player.Load_Img("img/Down.png", g_screen);
        player.animation();



        // TEXT
        const int kMenuItemNum = 2;
        SDL_Rect pos_arr[kMenuItemNum];
        pos_arr[0].x = 550;
        pos_arr[0].y = SCREEN_HEIGHT - 400;

        pos_arr[1].x = 560;
        pos_arr[1].y = SCREEN_HEIGHT - 300;

        Text menu_tile[kMenuItemNum];

        std::string str1 = "Start";
        menu_tile[0].SetText(str1);
        menu_tile[0].SetColor(200,200,200);
        menu_tile[0].setrect(pos_arr[0].x, pos_arr[0].y);

        std::string str2 = "Quit";
        menu_tile[1].SetText(str2);
        menu_tile[1].SetColor(200,200,200);
        menu_tile[1].setrect(pos_arr[1].x, pos_arr[1].y);

        bool selected[kMenuItemNum] = { 0,0 };


        int score_count;
        int hp_count;

        Text score;
        score.SetColor(Text::BLACK);

        Text hp;
        hp.SetColor(Text::BLACK);


        while (!ready) {
            while (SDL_PollEvent(&g_event) != 0) {
                if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym != SDLK_ESCAPE) {
                    ready = true;
                }
                if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_ESCAPE) {
                    ready = true;
                    quit = true;
                    thinking = false;
                    playing = false;
                }
            }

            if (!Mix_PlayingMusic())
            {
                Mix_PlayMusic(g_menu_music, -1);
            }

            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);
            menu.render(g_screen, NULL);

            for (int i = 0; i < kMenuItemNum; i++) {
                menu_tile[i].LoadFromRenderText(menu_font, g_screen);
            }
            while (SDL_PollEvent(&m_event) != 0) {
                if (m_event.type == SDL_MOUSEMOTION) {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;
                    for (int i = 0; i < kMenuItemNum; i++) {
                        if (CheckFocus(xm, ym, menu_tile[i].getrect())) {
                            if (selected[i] == false) {
                                selected[i] = true;
                                menu_tile[i].SetColor(200,200,200);
                                menu_tile[i].LoadFromRenderText(menu_font, g_screen);
                            }
                        }

                        else {
                            if (selected[i] == true) {
                                selected[i] = false;
                                menu_tile[i].SetColor(Text::YELLOW);
                                menu_tile[i].LoadFromRenderText(menu_font_1, g_screen);
                            }
                        }
                    }

                }
                else if (m_event.type == SDL_MOUSEBUTTONDOWN) {
                    xm = m_event.button.x;
                    ym = m_event.button.x;
                    if (CheckFocus(xm, ym, menu_tile[0].getrect()))
                        ready = true;
                    if (CheckFocus(xm, ym, menu_tile[1].getrect()))
                        ready = true;
                        quit = true;
                        thinking = false;
                        playing = false;
                }
            }

            menu_tile[0].RenderText(g_screen, 550, SCREEN_HEIGHT - 400);
            menu_tile[1].RenderText(g_screen, 560, SCREEN_HEIGHT - 300);

            SDL_RenderPresent(g_screen);
        }
        Mix_FreeMusic(g_menu_music);
      
        while (!quit) {
            while (SDL_PollEvent(&g_event) != 0) {
                if (g_event.type == SDL_QUIT/* || (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_ESCAPE)*/) {
                    quit = true;
                }
                player.KeyPress(g_event, g_screen);
            }
            

            if (!Mix_PlayingMusic())
            {
                Mix_PlayMusic(g_music, -1);
            }


            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);
            background.render(g_screen, NULL);
            Map new_map = g_map.getmap();
            player.spawn(new_map,g_eff);

            g_map.ChangeMap(new_map);
            g_map.draw(g_screen);
            player.Print(g_screen);

            score_count = 20 - player.GetScore();
            std::string current_score = std::to_string(score_count);
            score.SetText(current_score);
            score.LoadFromRenderText(font, g_screen);
            score.RenderText(g_screen, 50, 5);
            
            hp_count = player.GetHp();
            std::string current_hp = std::to_string(hp_count);
            hp.SetText(current_hp);
            hp.LoadFromRenderText(font, g_screen);
            hp.RenderText(g_screen, SCREEN_WIDTH - 75 , 5);

            if (score_count == 0) {
                quit = true;
                win = true;
            }

            if (hp_count == 0) {
                quit = true;
                win = false;
            }

            SDL_RenderPresent(g_screen);
        }
        Mix_FreeMusic(g_music);
        
        while (thinking) {
            while (SDL_PollEvent(&g_event) != 0) {
                if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_r) {
                    thinking = false;
                }
         
                if (!Mix_PlayingMusic())
                {
                    Mix_PlayMusic(g_result_music, -1);
                }

                SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                SDL_RenderClear(g_screen);
                if (win) {
                    win_background.render(g_screen, NULL);
                }
                else lose_background.render(g_screen, NULL);
                SDL_RenderPresent(g_screen);
            }
        }

        Mix_FreeMusic(g_result_music);

    }
	return 0;
}
