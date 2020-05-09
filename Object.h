#ifndef OBJECT_H
#define OBJECT_H

#include "Func.h"

class Object {
public:
	Object();
	~Object();
	void setrect(const int& x, const int& y) { rect.x = x, rect.y = y; }
	SDL_Rect getrect() { return rect; }
	SDL_Texture* getobject() { return p_object; }
	virtual bool Load_Image(std::string filepath, SDL_Renderer* screen);
	void render(SDL_Renderer* des, const SDL_Rect* from = NULL );
protected:
	SDL_Rect rect;
	SDL_Texture* p_object;
};
#endif

