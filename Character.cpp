#include "Object.h"
#include "Character.h"

Char::Char() {
	g_frame = 0;
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	y_val = 0;
	frame_w = 0;
	frame_h = 0;
	status = -1;
}

Char::~Char() {

}

bool Char::Load_Img(std::string path, SDL_Renderer* screen) {
	bool r = Object::Load_Image(path, screen);
	if (r==true) {
		frame_w = rect.w/FRAME_COUNT;
		frame_h = rect.h;

	}
	return r;
}

void Char::animation() {
	if (frame_w > 0 & frame_h > 0) {
		for (int i = 0; i < FRAME_COUNT; i++) {
			frame[i].x = i * frame_w;
			frame[i].y = 0;
			frame[i].w = frame_w;
			frame[i].h = frame_h;
		}

	}

}

void Char::Press(SDL_Event ev, SDL_Renderer* screen) {
	if (ev.type == SDL_KEYDOWN) {
		switch (ev.key.keysym.sym) {
		case SDLK_RIGHT: {
			status = move_right;
			ip.right = 1;
		}
					   break;
		case SDLK_LEFT: {
			status = move_left;
			ip.left = 1;
		}
					  break;
		case SDLK_UP: {
			status = move_up;
			ip.up = 1;

		}
					break;
		case SDLK_DOWN: {
			status = move_down;
			ip.down = 1;
		}
					  break;
		}
	}
	else if (ev.type == SDL_KEYUP) {

	}
}

void Char::Print(SDL_Renderer* screen) {
	if (status = move_right) {
		Load_Img("img//Right.png", screen);
	}

	else if (status = move_left) {
		Load_Img("img//Left.png", screen);
	}

	else if (status = move_up) {
		Load_Img("img//Up.png", screen);
	}

	else if(status = move_down){
		Load_Img("img//Down.png", screen);
	}

	if (ip.right == 1 || ip.left == 1 || ip.up == 1 || ip.down == 1) {
		g_frame++;
	}

	else {
		g_frame = 0;
	}

	rect.x = x_pos;
	rect.y = y_pos;

	SDL_Rect* pos = &frame[g_frame];
	SDL_Rect render = { rect.x,rect.y,frame_w,frame_h };

	SDL_RenderCopy(screen, p_object, pos, &render);

}

