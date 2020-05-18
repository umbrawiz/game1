

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


bool initSDL()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (ret < 0) return false;


    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("Formerly Known As PACMANNNNNN",
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

        if (font != NULL && menu_font != NULL && menu_font_1 != NULL) {
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
    menu.Load_Image("img//terra.png", g_screen);
    background.Load_Image("img//white.png", g_screen);
    win_background.Load_Image("img//win.png", g_screen);
    lose_background.Load_Image("img//lose.png", g_screen);
    g_icon = IMG_Load("img//g_icon.png");
}

void Free() {
    background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit;
    SDL_QUIT;
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    if (initSDL() == false) return -1;
    LoadBackground();

    SDL_SetWindowIcon(g_window, g_icon);

    bool playing = true;

    static Mix_Chunk* g_eff = NULL;
    static Mix_Chunk* g_eff_1 = NULL;

    g_eff = Mix_LoadWAV("sound//Collect.wav");
    g_eff_1 = Mix_LoadWAV("sound//g_eff_1.wav");


    while (playing)
    {
        bool quit = false;
        bool thinking = true;

        int ret = SDLCommonFunc::ShowMenu(g_screen, font, menu_font_1, menu_font);
        if (ret == 1)
        {
            quit = true;
            thinking = false;
            playing = false;
        }

        

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
        g_result_music = Mix_LoadMUS("sound/g_result.mp3");
        Mix_VolumeMusic(64);

        // PLAYER
        Char player;
        player.Load_Img("img/Right.png", g_screen);
        player.SetSpawnPos(PLAYER_SPAWN_POINT_X, PLAYER_SPAWN_POINT_Y);
        player.animation();

        int score_count;
        int hp_count;

        Text score;
        score.setColor(Text::BLACK_TEXT);

        Text hp;
        hp.setColor(Text::BLACK_TEXT);

        Text result;
        result.setColor(255,255,0);


        bool is_focus = false;
        int idx = -1;

        while (!quit)
        {
            while (SDL_PollEvent(&g_event) != 0) {
                if (g_event.type == SDL_QUIT) {
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
            player.spawn(new_map, g_eff, g_eff_1);

            g_map.ChangeMap(new_map);
            g_map.draw(g_screen);
            player.Print(g_screen);

            score_count = 20 - player.GetScore();
            std::string current_score = std::to_string(score_count);
            score.SetText(current_score);
            score.loadFromRenderedText(font, g_screen);
            score.RenderText(g_screen, 50, 5);

            hp_count = player.GetHp();
            std::string current_hp = std::to_string(hp_count);
            hp.SetText(current_hp);
            hp.loadFromRenderedText(font, g_screen);
            hp.RenderText(g_screen, SCREEN_WIDTH - 75, 5);

            if (score_count == 0) {
                quit = true;
            }

            if (hp_count == 0) {
                quit = true;
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
                if (score_count == 0) {
                    win_background.render(g_screen, NULL);
                }
                else if(hp_count == 0) lose_background.render(g_screen, NULL);

                std::string result_msg = "Press R to continue";
                result.SetText(result_msg);
                result.loadFromRenderedText(font, g_screen);
                result.RenderText(g_screen, 440, SCREEN_HEIGHT - 50);

                SDL_RenderPresent(g_screen);
            }
        }
        Mix_FreeMusic(g_result_music);
    }

    Free();

    return 0;
}
