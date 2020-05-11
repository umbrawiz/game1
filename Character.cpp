#include "Object.h"
#include "Character.h"

Char::Char() {
	g_frame = 0;
	x_pos = 600;
	y_pos = 350;
	x_val = 0;
	y_val = 0;
	frame_w = 0;
	frame_h = 0;
	status = NULL;
	ip.down = 0;
	ip.up = 0;
	ip.left = 0;
	ip.right = 0;
}

Char::~Char() {

}

bool Char::Load_Img(std::string path, SDL_Renderer* screen) {
	bool r = Object::Load_Image(path, screen);
	if (r == true) {
		frame_w = rect.w / FRAME_COUNT;
		frame_h = rect.h;

	}
	return r;
}

void Char::animation() {
	for (int i = 0; i < FRAME_COUNT; i++) {
		frame[i].x = i * frame_w;
		frame[i].y = 0;
		frame[i].w = frame_w;
		frame[i].h = frame_h;
	}
}

void Char::KeyPress(SDL_Event ev, SDL_Renderer* screen) {
	if (ev.type == SDL_KEYDOWN) {
		switch (ev.key.keysym.sym) {
		case SDLK_RIGHT: {
			status = move_right;
			ip.right = 1;
			ip.left = 0;
			ip.down = 0;
			ip.up = 0;
		}
					   break;
		case SDLK_d : {
			status = move_right;
			ip.right = 1;
			ip.left = 0;
			ip.down = 0;
			ip.up = 0;
		}
					   break;
		case SDLK_LEFT: {
			status = move_left;
			ip.right = 0;
			ip.left = 1;
			ip.down = 0;
			ip.up = 0;
		}
					  break;
		case SDLK_a: {
			status = move_left;
			ip.right = 0;
			ip.left = 1;
			ip.down = 0;
			ip.up = 0;
		}
					  break;
		case SDLK_UP: {
			status = move_up;
			ip.right = 0;
			ip.left = 0;
			ip.down = 0;
			ip.up = 1;

		}
		case SDLK_w: {
			status = move_up;
			ip.right = 0;
			ip.left = 0;
			ip.down = 0;
			ip.up = 1;

		}
					break;
		case SDLK_DOWN: {
			status = move_down;
			ip.right = 0;
			ip.left = 0;
			ip.down = 1;
			ip.up = 0;
		}
					  break;
		case SDLK_s: {
			status = move_down;
			ip.right = 0;
			ip.left = 0;
			ip.down = 1;
			ip.up = 0;
		}
					  break;
		}
	}
	else if (ev.type == SDL_KEYUP) {
		switch (ev.key.keysym.sym) {
		case SDLK_RIGHT: {
			ip.right = 0;
			ip.left = 0;
			ip.down = 0;
			ip.up = 0;
		}
					   break;
		case SDLK_d: {
			ip.right = 0;
			ip.left = 0;
			ip.down = 0;
			ip.up = 0;
		}
					   break;
		case SDLK_LEFT: {
			ip.left = 0;
			ip.left = 0;
			ip.down = 0;
			ip.up = 0;
		}
					  break;
		case SDLK_a: {
			ip.left = 0;
			ip.left = 0;
			ip.down = 0;
			ip.up = 0;
		}
					  break;
		case SDLK_UP: {
			ip.up = 0;
			ip.left = 0;
			ip.down = 0;
			ip.up = 0;

		}
					break;
		case SDLK_w: {
			ip.up = 0;
			ip.left = 0;
			ip.down = 0;
			ip.up = 0;

		}
					break;
		case SDLK_DOWN: {
			ip.down = 0;
			ip.left = 0;
			ip.down = 0;
			ip.up = 0;
		}
					  break;
		case SDLK_s: {
			ip.down = 0;
			ip.left = 0;
			ip.down = 0;
			ip.up = 0;
		}
					  break;
		}
	}
}

void Char::Print(SDL_Renderer* screen) {
	if (status == move_right) {
		Load_Img("img/Right.png", screen);
	}

	else if (status == move_left) {
		Load_Img("img/Left.png", screen);
	}

	else if (status == move_up) {
		Load_Img("img/Up.png", screen);
	}

	else if(status == move_down){
		Load_Img("img/Down.png", screen);
	}

	if (ip.right == 1 || ip.left == 1 || ip.up == 1 || ip.down == 1) {
		g_frame++;
	}

	else {
		g_frame = 0;
	}
	if (g_frame >= 4) g_frame = 0;

	rect.x = x_pos;
	rect.y = y_pos;

	SDL_Rect* pos = &frame[g_frame];
	Object::render(screen, pos);

}

void Char::mapcheck(Map& map) {
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + frame_w - 1.1 ) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + frame_h - 1.1 ) / TILE_SIZE;
		
	if (x1 >= 0 && x2 < MAP_W && y1 >= 0 && y2 < MAP_H) {
		if (x_val > 0) {
			if (map.tile[y1][x2] == 6 || map.tile[y2][x2] == 6) {
				map.tile[y1][x2] = 3;
				map.tile[y2][x2] = 3;
				Mix_PlayChannel(-1, g_eff, 0);
			}
			else if (map.tile[y1][x2] != 3 || map.tile[y2][x2] != 3) {
				x_pos = x2 * TILE_SIZE;
				x_pos -= frame_w + 1.1;
				x_val = 0;	
				if (y_pos < 0) {
					y_pos = 0;
				}
			}
		}
		else if (x_val < 0) {
			if (map.tile[y1][x1] == 6 || map.tile[y2][x1] == 6) {
				map.tile[y1][x1] = 3;
				map.tile[y2][x1] = 3;
				Mix_PlayChannel(-1, g_eff, 0);
			}
			else if (map.tile[y1][x1] != 3 || map.tile[y2][x1] != 3) {
				x_pos = (x1 + 1.1) * TILE_SIZE;
				x_val = 0;
				if (y_pos < 0) {
					y_pos = 0;
				}
			}
		}
	}

	x1 = x_pos / TILE_SIZE;
	x2 = (x_pos + frame_w) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + frame_h - 1.1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_W && y1 >= 0 && y2 < MAP_H) {
		if (y_val > 0) {
			if (map.tile[y2][x1] == 6 || map.tile[y2][x2] == 6) {
				map.tile[y2][x1] = 3;
				map.tile[y2][x2] = 3;
				Mix_PlayChannel(-1, g_eff, 0);
			}
			else {
				if (map.tile[y2][x1] != 3 || map.tile[y2][x2] != 3) {
					y_pos = y2 * TILE_SIZE;
					y_pos -= (frame_h + 1.1);
					y_val = 0;	
					if (y_pos < 0) {
						y_pos = 0;
					}
				}
			}
		}

		else if (y_val < 0) {
			if (map.tile[y1][x1] == 6 || map.tile[y1][x2] == 6) {
				map.tile[y1][x1] = 3;
				map.tile[y1][x2] = 3;
				Mix_PlayChannel(-1, g_eff, 0);
			}
			else {
				if (map.tile[y1][x1] != 3 || map.tile[y1][x2] != 3) {
					y_pos = (y1 + 1.1) * TILE_SIZE;
					y_val = 0;
					if (y_pos < 0) {
						y_pos = 0;
					}
				}
			}
		}
	}
	x_pos += x_val;
	y_pos += y_val;

	if (x_pos < 0) {
		x_pos = 0;
	}

}

void Char::spawn(Map& map) {
	x_val = 0;
	y_val = 0;

	if (ip.right == 1) {
		x_val += Char_speed;
	}
	else if (ip.left == 1) {
		x_val -= Char_speed;
	}
	else if (ip.up == 1) {
		y_val -= Char_speed;
	}
	else if (ip.down == 1) {
		y_val += Char_speed;
	}

	mapcheck(map);
}

