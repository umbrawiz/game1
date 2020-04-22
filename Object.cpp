#include "Func.h"
#include "Object.h"

Object::Object() {
	p_object = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}
Object::~Object() {

}
void Object::setrect(int x, int y) {
	rect.x = x;
	rect.y = y;
}
SDL_Rect Object::getrect() {
	return rect;
}
SDL_Texture* Object:: getobject(){
	return p_object;
}
void Object::Load_Image(std::string filepath, SDL_Renderer* screen) {
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	texture = SDL_CreateTextureFromSurface(screen, surface);
	rect.w = surface->w;
	rect.h = surface->h;
	p_object = texture;
}