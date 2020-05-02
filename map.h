#ifndef MAP_H_
#define MAP_H_

#include "Func.h"
#include "Object.h"

#define MAX_TILE 10

class tilemap : public Object {
public:
	tilemap() { ; }
	~tilemap() { ; }
};

class gamemap {
public:
	gamemap() { ; }
	~gamemap() { ; }
	void loadmap(std::string fname);
	void loadtile(SDL_Renderer* screen);
	void draw(SDL_Renderer* screen);
	Map gmap;
	tilemap tilemap[MAX_TILE];

};
#endif 

