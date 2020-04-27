#ifndef FUNC_H_
#define FUNC_H_

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
static SDL_Event g_event ;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

#define TILE_SIZE 50
#define MAP_W 16
#define MAP_H 12

struct Map {
	int start_w;
	int start_h;
	int max_w;
	int max_h;
	char fname[100];
	int tile[MAP_H][MAP_W];
};

#endif