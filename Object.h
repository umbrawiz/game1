#ifndef OBJECT_H_
#define OBJECT_H_

#include "Func.h"

class Object {
public:
	Object();
	~Object();
	void setrect(const int& x, const int& y) {
		rect.x = x;
		rect.y = y;
	}
	SDL_Rect getrect();
	SDL_Texture* getobject() ;
	bool Load_Image(std::string filepath, SDL_Renderer* screen);
	void render(SDL_Renderer* des, SDL_Rect* from /*= NULL */);
protected:
	SDL_Rect rect;
	SDL_Texture* p_object;
};
#endif

