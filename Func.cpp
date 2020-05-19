#include "Func.h"
#include "Text.h"

SDL_Event m_event;

bool SDLCommonFunc::CheckFocus(const int& x, const int& y, SDL_Rect rect)
{
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}

int SDLCommonFunc::ShowMenu(SDL_Renderer* screen, TTF_Font* font, TTF_Font* font_big, TTF_Font* font_small)
{
    int ret = -1;
    int xm = 0;
    int ym = 0;
    static Mix_Chunk* g_menu_tick = Mix_LoadWAV("sound//Menu_Tick.wav");
    g_menu_music = Mix_LoadMUS("sound/g_menu.mp3");

    if (font == NULL || font_big == NULL || font_small == NULL)
    {
        return -1;
    }
    
    // TEXT
    const int kMenuItemNum = 2;
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 550;
    pos_arr[0].y = SCREEN_HEIGHT - 400;

    pos_arr[1].x = 555;
    pos_arr[1].y = SCREEN_HEIGHT - 330;

    Text menu_tile[kMenuItemNum];

    std::string str1 = "Start";
    menu_tile[0].SetText(str1);
    menu_tile[0].setColor(200, 200, 200);

    std::string str2 = "Quit";
    menu_tile[1].SetText(str2);
    menu_tile[1].setColor(200, 200, 200);

    bool selected[kMenuItemNum] = { 0,0 };

    bool ready = false;


    bool is_focus = false;
    int idx = -1;

    Object gBackground;
    gBackground.Load_Image("img//terra.png", screen);

    if ( !Mix_PlayingMusic() ) {
        Mix_PlayMusic(g_menu_music,-1);
    }

    while (!ready)
    {
        while (SDL_PollEvent(&m_event) != 0) {
            if (m_event.type == SDL_MOUSEMOTION) {
                xm = m_event.motion.x;
                ym = m_event.motion.y;
                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (CheckFocus(xm, ym, pos_arr[i]))
                    {
                        if (selected[i] == false) {
                            selected[i] = true;
                            menu_tile[i].setColor(255, 255, 0);
                            Mix_PlayChannel(-1, g_menu_tick, 0);
                            is_focus = true;
                            idx = i;
                        }
                    }

                    else
                    {
                        if (selected[i] == true)
                        {
                            selected[i] = false;
                            menu_tile[i].Free();
                            menu_tile[i].setColor(200, 200, 200);
                            is_focus = false;
                            idx = i;
                        }
                    }
                }

            }
            else if (m_event.type == SDL_MOUSEBUTTONDOWN)
            {
                xm = m_event.button.x;
                ym = m_event.button.y;
                if (CheckFocus(xm, ym, pos_arr[0]))
                {
                    ready = true;
                    ret = 0;
                    break;
                }

                if (CheckFocus(xm, ym, pos_arr[1]))
                {
                    ready = true;
                    ret = 1;
                    break;
                }
            }
        }

        if (idx == -1)
        {
            for (int i = 0; i < kMenuItemNum; i++)
            {
                menu_tile[i].Free();
                menu_tile[i].loadFromRenderedText(font_small, screen);

                pos_arr[i].w = menu_tile[i].getWidth();
                pos_arr[i].h = menu_tile[i].getHeight();
            }
        }
        else
        {
            if (is_focus == true)
            {
                if (idx == 0)
                {
                    menu_tile[0].Free();
                    menu_tile[1].Free();
                    menu_tile[0].loadFromRenderedText(font_big, screen);
                    menu_tile[1].loadFromRenderedText(font_small, screen);

                    pos_arr[0].w = menu_tile[0].getWidth();
                    pos_arr[0].h = menu_tile[0].getHeight();

                    pos_arr[1].w = menu_tile[1].getWidth();
                    pos_arr[1].h = menu_tile[1].getHeight();
                }
                else
                {
                    menu_tile[1].Free();
                    menu_tile[0].Free();
                    menu_tile[1].loadFromRenderedText(font_big, screen);
                    menu_tile[0].loadFromRenderedText(font_small, screen);

                    pos_arr[0].w = menu_tile[0].getWidth();
                    pos_arr[0].h = menu_tile[0].getHeight();

                    pos_arr[1].w = menu_tile[1].getWidth();
                    pos_arr[1].h = menu_tile[1].getHeight();
                }
            }
            else
            {
                menu_tile[0].Free();
                menu_tile[1].Free();
                menu_tile[0].loadFromRenderedText(font_small, screen);
                menu_tile[1].loadFromRenderedText(font_small, screen);

                pos_arr[0].w = menu_tile[0].getWidth();
                pos_arr[0].h = menu_tile[0].getHeight();

                pos_arr[1].w = menu_tile[1].getWidth();
                pos_arr[1].h = menu_tile[1].getHeight();
            }
        }

        gBackground.render(screen, NULL);

        menu_tile[0].RenderText(screen, 550, SCREEN_HEIGHT - 400);
        menu_tile[1].RenderText(screen, 555, SCREEN_HEIGHT - 330);


        SDL_RenderPresent(screen);
    }
    Mix_FreeMusic(g_menu_music);
    return ret;
}
