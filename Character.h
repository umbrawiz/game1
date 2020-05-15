#ifndef CHARACTER_H
#define CHARACTER_H

#include "Func.h"
#include "Object.h"
#include "map.h"


struct InputFK {
	int left;
	int right;
	int up;
	int down;
};

class Char:public Object {
public:
	Char();
	~Char();

	bool Load_Img(std::string path, SDL_Renderer* screen);
	void Print(SDL_Renderer* screen);
	void KeyPress(SDL_Event ev, SDL_Renderer* screen);
	void SetSpawnPos(int _x_pos, int _y_pos);
	void animation();
	void mapcheck(Map& map , Mix_Chunk* g_eff);
	void spawn(Map& map , Mix_Chunk* g_eff);
	void IncreaseScore();
	void DecreaseHp();
	void Col() {
		is_col = true;
	}
	int GetScore();
	int GetHp();
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

	int score;

	int hp;

	bool is_col;
};

#endif
