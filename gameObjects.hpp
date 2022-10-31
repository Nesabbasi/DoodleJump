#ifndef gameObjects_HPP
#define gameObjects_HPP

#include "rsdl.hpp"

#define NORMALPLATFORM "images/normal_platform.png"
#define MOVABLEPLATFORM "images/moving_platform.png"
#define BREAKABLEPLATFORM "images/breaking_platform.png"
#define BREAKING1 "images/breaking1.png"
#define BREAKING2 "images/breaking2.png"
#define BREAKING3 "images/breaking3.png"
#define ENEMY "images/enemy.png"
#define SPRING "images/spring.png"

enum class type {
	normal_platform,
	movable_platform,
	breakable_platform,
	enemy,
	spring
};

class gameObjects {
public:
	gameObjects(int _x,int _y);
	vector<gameObjects*> get_input();
	void check_gameObjects(vector<gameObjects*> all_gameObjects,Window* win);
	void set_location(int distance);
	int get_x() { return x; }
	int get_y() { return y; }
	virtual type get_type() = 0;
protected:
	int x;
	int y;
};

class normal_platform : public gameObjects{
public:
	normal_platform(int _x, int _y);
	type get_type();
	void normal(Window *window);
};

class movable_platform : public gameObjects {
public:
	movable_platform(int _x, int _y);
	type get_type();
	void movable(Window *window);
private:
	bool moving = true;
};

class breakable_platform : public gameObjects {
public:
	breakable_platform(int _x, int _y);
	type get_type();
	void change_broken();
	void breakable(Window *window);
	int get_times() { return times; }
private:
	int is_broken = false;
	int times;
};

class enemy: public gameObjects {
public:
	enemy(int _x, int _y);
	type get_type();
	void enemies(Window *window);
};

class spring : public gameObjects {
public:
	spring(int _x, int _y);
	type get_type();
	void springs(Window* window);
};
#endif