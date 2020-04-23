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
bool Object::Load_Image(std::string filepath, SDL_Renderer* screen) {
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	if (surface != NULL) {
		texture = SDL_CreateTextureFromSurface(screen, surface);
		if (texture != NULL) {
			rect.w = surface->w;
			rect.h = surface->h;
		}	
	}
	p_object = texture;

	return p_object != NULL;
	
}
void Object::render(SDL_Renderer* des, SDL_Rect* from) {
	SDL_Rect render = { rect.x,rect.y,rect.w,rect.h };
	SDL_RenderCopy(des, p_object, from, &render);
}