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
	char file_img[20];
	FILE* fp = NULL;

	for (int i = 0; i < MAX_TILE; i++) {
		sprintf_s(file_img, "map/%d.png", i);
		fopen_s(&fp, file_img, "rb");
		if (fp == NULL) {
			continue;
		}
		fclose(fp);
		tilemap[i].Load_Image(file_img, screen);
	}
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