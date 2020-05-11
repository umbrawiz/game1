#ifndef MAP_H_
#define MAP_H_

#include "Func.h"
#include "Object.h"

#define MAX_TILE 20

class gamemap {
public:
	gamemap() { ; }
	~gamemap() { ; }
	void loadmap(std::string fname);
	void loadtile(SDL_Renderer* screen);
	void draw(SDL_Renderer* screen);
	Map getmap();
	void ChangeMap(Map new_map);
	Map gmap;
	Object tilemap[MAX_TILE];

};
#endif 
