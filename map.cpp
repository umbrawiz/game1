#include "Func.h"
#include "Object.h"
#include "map.h"

void gamemap::loadmap(std::string fname) {
	std::ifstream inp;
	inp.open(fname.c_str());
	gmap.max_h = 0;
	gmap.max_w = 0;
	int val;
	for (int i = 0; i < MAP_H; i++) {
		for (int j = 0; j < MAP_W; j++) {
			inp >> val;
			gmap.tile[i][j] = val;
			int tmp = gmap.tile[i][j];
			if (tmp > 0) {
				if (j > gmap.max_w) gmap.max_w = j;
				if (i > gmap.max_h) gmap.max_h = i;
			}
		}
		if (inp.eof()) break;
	}
	gmap.max_h = (gmap.max_h + 1) * TILE_SIZE;
	gmap.max_w = (gmap.max_w + 1) * TILE_SIZE;

	gmap.start_w = 0;
	gmap.start_h = 0;

	inp.close();
}

void gamemap::loadtile(SDL_Renderer* screen) {
	tilemap[0].Load_Image("map/0.png", screen);
	tilemap[1].Load_Image("map/1.png", screen);
	tilemap[2].Load_Image("map/2.png", screen);
	tilemap[3].Load_Image("map/3.png", screen);
	tilemap[4].Load_Image("map/4.png", screen);
	tilemap[5].Load_Image("map/5.png", screen);
	tilemap[6].Load_Image("map/6.png", screen);
	tilemap[7].Load_Image("map/7.png", screen);
}

void gamemap::draw(SDL_Renderer* screen) {
	int w1 = 0, w2 = 0, h1 = 0, h2 = 0;
	int pos_w = 0, pos_h = 0;
	pos_w = (gmap.start_w) / TILE_SIZE;

	w1 = gmap.start_w / TILE_SIZE;
	w2 = w1 + SCREEN_WIDTH;

	h1 = gmap.start_h / TILE_SIZE;
	h2 = h1 + SCREEN_HEIGHT;
	gmap.start_w = 0;
	gmap.start_h = 0;
	for (int i = h1; i < h2; i += TILE_SIZE) {
		int pos_w = (gmap.start_w) / TILE_SIZE;
		for (int j = w1; j < w2; j += TILE_SIZE) {
			int val = gmap.tile[pos_h][pos_w];
			if (val > 0) {
				tilemap[val].setrect(j, i);
				tilemap[val].render(screen);
			}
			pos_w++;
		}
		pos_h++;
	}
}

Map gamemap::getmap() {
	return gmap;
}

void gamemap::ChangeMap(Map new_map) {
	gmap = new_map;
}

void gamemap::SetRandomPBPos() {
	int x, y;
	do {
		x = rand() % 24 + 1;
		y = rand() % 16 + 1;
	} while (gmap.tile[y][x] != 3 || (x == PLAYER_SPAWN_POINT_X / TILE_SIZE && y == PLAYER_SPAWN_POINT_Y / TILE_SIZE));

	gmap.tile[y][x] = POKE_BALL;
}

void gamemap::SetRandomSPPos() {
	int x, y;
	do {
		x = rand() % 24 + 1;
		y = rand() % 16 + 1;
	} while (gmap.tile[y][x] != 3 || gmap.tile[y+1][x] == SPIKE || gmap.tile[y][x+1] == SPIKE 
		|| ( x == PLAYER_SPAWN_POINT_X/TILE_SIZE && y == PLAYER_SPAWN_POINT_Y/TILE_SIZE));

	gmap.tile[y][x] = SPIKE;
}