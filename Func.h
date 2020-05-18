#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <time.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static SDL_Surface* g_icon = NULL;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;	

#define TILE_SIZE 50
#define MAP_W 24
#define MAP_H 16
#define FRAME_COUNT 4
#define Char_speed 0.5
#define POKE_BALL 6
#define SPIKE 5
#define BLANK 3
#define POKEBALLNUM 20
#define SPIKENUM 10
#define PLAYER_SPAWN_POINT_X 600
#define PLAYER_SPAWN_POINT_Y 350
#define KNOCK_BACK_DISTANCE 15

static Mix_Music* g_music = NULL;
static Mix_Music* g_menu_music = NULL;
static Mix_Music* g_result_music = NULL;

namespace SDLCommonFunc
{
    int ShowMenu(SDL_Renderer* screen, TTF_Font* font, TTF_Font* font_big, TTF_Font* font_small);
    bool CheckFocus(const int& x, const int& y, SDL_Rect rect);
}


#endif

