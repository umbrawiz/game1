#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Func.h"
#include "Object.h"

class Char:public Object {
public:
	Char();
	~Char();

	bool Load_Img(std::string path, SDL_Renderer* screen);
	void Print(SDL_Renderer* screen);
	void KeyPress(SDL_Event ev, SDL_Renderer* screen);
	void animation();
	void mapcheck(Map& map);
	void spawn(Map& map);

	enum movement {
		move_right = 0,
		move_left = 1,
		move_up = 2,
		move_down = 3,
	};

private:
	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int frame_w;		
	int frame_h;

	SDL_Rect frame[4];
	InputFK ip;

	int g_frame;
	int status;
};

#endif
