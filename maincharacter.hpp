#ifndef MAINCHARACTER_HPP
#define MAINCHARACTER_HPP

#include "rsdl.hpp"
#include"gameObjects.hpp"

#define RIGHTCHAR "images/right.png"
#define LEFTCHAR "images/left.png"
#define PLAT_WIDTH 75
#define PLAT_HEIGHT 22
#define SPRING_WIDTH 35
#define SPRING_HEIGHT 29
#define ENEMY_WIDTH 85
#define ENEMY_HEIGHT 115
#define PLAYER_WIDTH 77
#define PLAYER_HEIGHT 75

class maincharacter {
public:
	maincharacter(Window*win, int _y, int _vy);
	void speed();
	void moving(bool &key_press, bool &head_side);
	void set_speed();
	void set_spring_speed();
	void set_location(int distance);
	bool check_lost();
	void hit_enemy();
	void right_move(bool& is_head_right);
	void left_move(bool& is_head_right);
	void check_horizontal_range();
	void hit_platforms(vector<gameObjects*>&platforms);
	void hit_enemies(vector<gameObjects*>&enemies);
	void hit_springs(vector<gameObjects*>&springs);
	void key__press(Event event, bool& is_head_right);
	void key__release();
	int get_x() { return x; }
	int get_y() { return y; }
	int get_vy() { return vy; }
	int get_vx() { return vx; }
private:
	Window *window;
	gameObjects *gameObject;
	breakable_platform *broken;
	int x;
	int y;
	int vx;
	int vy;
	bool hitt_enemy=false;
};


#endif 
