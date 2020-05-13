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

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

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
#define Char_speed 0.45
#define POKE_BALL 6

static Mix_Music* g_music = NULL;
static Mix_Chunk* g_eff = Mix_LoadWAV("sound//Collect.wav");
static Mix_Music* g_menu_music = NULL;


#endif

