#ifndef MAP_H_
#define MAP_H_

#include "Func.h"
#include "Object.h"

class tilemap : public Object {
public:
	tilemap() {

	}
};

class gamemap {
public:
	gamemap() {

	}
	void loadmap(std::string fname);
	void loadtile(SDL_Renderer* screen);
	void draw(SDL_Renderer* screen);
	Map gmap;
	tilemap tilemap[10];

};
#endif 

