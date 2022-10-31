#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "rsdl.hpp"
#include "maincharacter.hpp"
#include "gameObjects.hpp"

#define BACKGROUND "images/background.png"
#define SCORE "images/score.png"
#define FINISH "images/finish.png"

class program {
public:
	program();
	void start();
	void end();
	void set_window(Window* win) { window = win; }
	void check_screen(vector<gameObjects*>&gameObjects,int &max);
	void head_check();
	void score(int distance);
private:
	Window* window;
	maincharacter *player;
	gameObjects *gameObject;
	bool key_press;
	bool is_head_right = true;
	int high_score=0;
	int distance = 0;
};
#endif

