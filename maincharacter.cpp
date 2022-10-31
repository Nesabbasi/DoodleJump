#include"maincharacter.hpp"

maincharacter::maincharacter(Window *win,int _y,int _vy) {
	window = win;
	y = _y;
	vy = _vy;
	vx = 0;
	x = 161;
}

void maincharacter::speed() {
	y -= vy*0.02;
	vy -= 500* 0.02;
}

bool maincharacter::check_lost() {
	if (y > 640) {
		return true;
	}
	else if (hitt_enemy == true) {
		return true;
	}
	return false;
}

void maincharacter::set_speed() {
	vy = 300;
}

void maincharacter::hit_enemy() {
	hitt_enemy = true;
}

void maincharacter::set_spring_speed() {
	vy = 600;
}

void maincharacter::set_location(int distance) {
	y += distance;
}

void maincharacter::hit_platforms(vector<gameObjects*>&platforms){
	for (int i = 0; i < platforms.size(); i++) {
		if (vy <= 0 && (x <(platforms[i]->get_x() + 42)) &&
			((x + 45)>(platforms[i]->get_x())) &&
			((y + PLAYER_HEIGHT)>(platforms[i]->get_y())) &&
			((y + PLAYER_HEIGHT)<(platforms[i]->get_y() + PLAT_HEIGHT))) {
			if (platforms[i]->get_type() != type::breakable_platform && 
				platforms[i]->get_type() != type::enemy && 
				platforms[i]->get_type() != type::spring)
				set_speed();
			else if (platforms[i]->get_type() == type::breakable_platform) {
				dynamic_cast<breakable_platform*>(platforms[i])->change_broken();
			}
			break;
		}
	}
}

void maincharacter::hit_enemies(vector<gameObjects*>&enemies) {
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->get_type() == type::enemy) {
			if ((x < (enemies[i]->get_x() + ENEMY_WIDTH)) &&
				((x + 70)>(enemies[i]->get_x())) &&
				(y < (enemies[i]->get_y() + ENEMY_HEIGHT)) &&
				((y + PLAYER_HEIGHT) > (enemies[i]->get_y()))) {
				enemies.erase(enemies.begin() + i);
				hit_enemy();
			}
		}
	}
}

void maincharacter::hit_springs(vector<gameObjects*>&springs) {
	for (int i = 0; i < springs.size(); i++) {
		if (springs[i]->get_type() == type::spring) {
			if ((x < (springs[i]->get_x()+ 17)) &&
				((x + 45) > (springs[i]->get_x())) &&
				((y + PLAYER_HEIGHT) < springs[i]->get_y() + SPRING_HEIGHT) &&
				((y + PLAYER_HEIGHT) > springs[i]->get_y())) {
				set_spring_speed();
			}
		}
	}
}

void maincharacter::check_horizontal_range() {
	x += vx;
	if (x + vx >= 362)
		x = -38;
	if (x + vx <= -38)
		x = 362;
}

void maincharacter::right_move(bool& is_head_right) {
	window->draw_img(RIGHTCHAR, Rectangle(x, y, 77, 75));
	is_head_right = true;
	vx = 5;
}

void maincharacter::left_move(bool& is_head_right) {
	window->draw_img(LEFTCHAR, Rectangle(x, y, 77, 75));
	is_head_right = false;
	vx = -5;
}

void maincharacter::key__press(Event event, bool& is_head_right) {
	char pressedChar;
	pressedChar = event.get_pressed_key();
	if (pressedChar == 'd') {
		right_move(is_head_right);
	}
	if (pressedChar == 'a') {
		left_move(is_head_right);
	}
}

void maincharacter::key__release() {
	vx = 0;
}

void maincharacter::moving(bool& key_press,bool& is_head_right) {
	while (window->has_pending_event()) {
		Event event = window->poll_for_event();
		if (event.get_type() == Event::QUIT)
			exit(0);
		if (event.get_type() == Event::KEY_PRESS) {
			key_press = true;
		}
		if (event.get_type() == Event::KEY_RELEASE) {
			key_press = false;
		}
		if (key_press) {
			key__press(event, is_head_right);
		}
		if (!key_press) {
			key__release();
		}
	}
	check_horizontal_range();
}
