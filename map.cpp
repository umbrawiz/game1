#include "Func.h"
#include "Object.h"
#include "map.h"

void gamemap::loadmap(std::string fname) {
	std::ifstream inp;
	inp.open(fname.c_str());
	gmap.max_h = 13*TILE_SIZE;
	gmap.max_w = 15*TILE_SIZE;
	int val;
	for (int i = 0; i < MAP_H; i++) {
		for (int j = 0; j < MAP_W; j++) {
			inp >> val;
			gmap.tile[i][j] = val;
		}
		if (inp.eof()) break;
	}
	
	gmap.start_w = 0;
	gmap.start_h = 0;
	inp.close();
}

void gamemap::loadtile(SDL_Renderer* screen) {
	char file_img[10];
	FILE* fp = NULL;

	for (int i = 0; i <2; i++) {
		sprintf_s(file_img, "map/%d.png", i);
		fopen_s(&fp, file_img, "rb");
		fclose(fp);
		tilemap[i].Load_Image(file_img, screen);
	}
}

void gamemap::draw(SDL_Renderer* screen) {
	int w1 = 0, w2 = 0, h1 = 0, h2 = 0;
	int pos_h = (gmap.start_h) / TILE_SIZE;
	w1 = (gmap.start_w % TILE_SIZE) * -1;
	w2 = w1 + SCREEN_WIDTH + (w1 == 0 ? 0 : TILE_SIZE);
	h1 = (gmap.start_h % TILE_SIZE) * -1;
	h2 = h1 + SCREEN_HEIGHT + (h1 == 0 ? 0 : TILE_SIZE);
	for (int i = h1; i < h2; i += TILE_SIZE) {
		int pos_w = (gmap.start_w) / TILE_SIZE;
		for (int j = w1; j < w2; j += TILE_SIZE) {
			int pos_h = (gmap.start_h) / TILE_SIZE;
			int val = gmap.tile[pos_w][pos_h];
			tilemap[val].setrect(j, i);
			tilemap[val].render(screen,NULL);
			pos_w++;
		}
		pos_h++;
	}

}
