#include"gameObjects.hpp"
#include"program.hpp"

gameObjects::gameObjects(int _x, int _y) {
	x = _x;
	y = _y;
}

normal_platform::normal_platform(int _x, int _y)
	:gameObjects(_x,_y) {
}

movable_platform::movable_platform(int _x, int _y)
	: gameObjects(_x, _y) {
}

breakable_platform::breakable_platform(int _x, int _y)
	: gameObjects(_x, _y) {
	times = 0;
	is_broken = false;
}

enemy::enemy(int _x, int _y)
	:gameObjects(_x, _y){
}

spring::spring(int _x, int _y)
	: gameObjects(_x, _y) {
}

type normal_platform::get_type() {
	return type::normal_platform;
}

type movable_platform::get_type() {
	return type::movable_platform;
}

type breakable_platform::get_type() {
	return type::breakable_platform;
}

type enemy::get_type() {
	return type::enemy;
}

type spring::get_type() {
	return type::spring;
}

void breakable_platform::change_broken() {
	is_broken = true;
}

void normal_platform::normal(Window *window) {
	window->draw_img(NORMALPLATFORM, Rectangle(x, y, 75, 22));
}

void movable_platform::movable(Window *window) {
	window->draw_img(MOVABLEPLATFORM, Rectangle(x, y, 75, 22));
	if (moving) {
		x += 2;
		if (x >= 325)
			moving = false;
	}
	if (!moving) {
		x -= 2;
		if (x <= 0)
			moving = true;
	}
}

void breakable_platform::breakable(Window *window) {
	if (!is_broken)
		window->draw_img(BREAKABLEPLATFORM, Rectangle(x, y, 75, 22));
	else if (is_broken) 
		times++;
	if (times < 5)
		window->draw_img(BREAKABLEPLATFORM, Rectangle(x, y, 75, 22));
	else if (times < 7)
		window->draw_img(BREAKING1, Rectangle(x, y, 75, 22));
	else if (times < 9)
		window->draw_img(BREAKING2, Rectangle(x, y, 75, 22));
	else if (times < 11)
		window->draw_img(BREAKING3, Rectangle(x, y, 75, 22));
}

void enemy::enemies(Window *window) {
	window->draw_img(ENEMY, Rectangle(x, y, 85, 115));
}

void spring::springs(Window* window) {
	window->draw_img(SPRING, Rectangle(x, y, 35, 29));
}

void gameObjects::set_location(int distance) {
	y += distance;		
}

void gameObjects::check_gameObjects(vector<gameObjects*> gameObject,Window* win) {
	for (int i = 0; i < gameObject.size(); i++) {
		if (gameObject[i]->get_type() == type::normal_platform)
			dynamic_cast<normal_platform*>(gameObject[i])->normal(win);
		else if (gameObject[i]->get_type() == type::movable_platform)
			dynamic_cast<movable_platform*>(gameObject[i])->movable(win);
		else if (gameObject[i]->get_type() == type::breakable_platform)
			dynamic_cast<breakable_platform*>(gameObject[i])->breakable(win);
		else if (gameObject[i]->get_type() == type::enemy)
			dynamic_cast<enemy*>(gameObject[i])->enemies(win);
		else if (gameObject[i]->get_type() == type::spring)
			dynamic_cast<spring*>(gameObject[i])->springs(win);
	}
}

vector<gameObjects*> gameObjects::get_input() {
	vector<gameObjects*>gameObject;
	ifstream inputFile("map.txt");
	string type;
	int number_of_entities, x, y;
	inputFile >> number_of_entities;
	for (int i = 0; i < number_of_entities; i++) {
		inputFile >> x;
		inputFile >> y;
		inputFile >> type;
		if (type == "platform") {
			gameObject.push_back(new normal_platform(5 * x / 8 - 37, 640 - (5 * y / 8 + 22)));
		}
		else if (type == "mplatform") {
			gameObject.push_back(new movable_platform(5 * x / 8 - 37, 640 - (5 * y / 8 + 22)));
		}
		else if (type == "bplatform") {
			gameObject.push_back(new breakable_platform(5 * x / 8 - 37, 640 - (5 * y / 8 + 22)));
		}
		else if (type == "enemy") {
			gameObject.push_back(new enemy(5 * x / 8 - 42, 640 - (5 * y / 8 + 115)));
		}
		else if (type == "spring") {
			gameObject.push_back(new spring(5 * x / 8 - 17, 640 - (5 * y / 8 + 29)));
		}
	}
	inputFile.close();
	return gameObject;
}