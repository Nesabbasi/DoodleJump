#include"program.hpp"

program::program() {
	Window* window = new Window(400,640,"DoodleJump");
	player = new maincharacter(window,565,300);
	set_window(window);
}

void program::score(int distance) {
	high_score += distance;
	window->draw_img(SCORE, Rectangle(0, 0, 400, 60));
	window->show_text(to_string(high_score), Point(20, 0), BLACK, "DoodleJump.ttf", 40);

}

void program::check_screen(vector<gameObjects*>&gameObjects,int &max) {
	if (player->get_y() + 77 <= 320) {
		distance = 320 - (player->get_y() + 77);
		for (int i = 0; i < gameObjects.size(); i++) {
			gameObjects[i]->set_location(distance);
			if (gameObjects[i]->get_y() >= 640)
				gameObjects.erase(gameObjects.begin() + i);
		}
		player->set_location(distance);
	}
	else if (player->get_y() + 77 > 320 && high_score<320) {
		max = 640 - (player->get_y() + 77);
		if (high_score < max) {
			max = 640 - (player->get_y() + 77);
			high_score = max;
		}
	}
}

void program::head_check() {
	if (is_head_right == true)
		window->draw_img(RIGHTCHAR, Rectangle(player->get_x(), player->get_y(), 77, 75));
	else
		window->draw_img(LEFTCHAR, Rectangle(player->get_x(), player->get_y(), 77, 75));
}

void program::end() {
	while (true) {
		window->clear();
		window->draw_img(BACKGROUND);
		window->draw_img(FINISH);
		window->show_text(to_string(high_score), Point(160, 520), BLACK, "OpenSans.ttf", 40);
		window->update_screen();
		if (window->has_pending_event()) {
			Event e = window->poll_for_event();
			if (e.get_type() == Event::KEY_PRESS)
				break;
			if (e.get_type() == Event::QUIT)
				exit(0);
		}
	}
}

void program::start() {
	vector<gameObjects*>gameObjects= gameObject->get_input();
	int max = 0;
	while (true) {
		window->draw_img(BACKGROUND);
		gameObject->check_gameObjects(gameObjects,window);
		check_screen(gameObjects,max);
		player->hit_platforms(gameObjects);
		player->hit_enemies(gameObjects);
		player->hit_springs(gameObjects);
		head_check();
		player->speed();
		if (player->check_lost()) { break; }
		score(distance);
		player->moving(key_press, is_head_right);
		window->update_screen();
		delay(20);
	}
	end();
}
