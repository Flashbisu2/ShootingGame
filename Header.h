#ifndef _HEADER_H_
#define _HEADER_H_

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>


//global variable
enum IDS{PLAYER, BULLET, ENEMY};
const float width = 400;
const float height = 1000;

class splite {
protected:
	float x;
	float y;
};

class SpaceShip:public splite {
private:
	float boundx;
	float boundy;
	int ID;
	int lives;
	int score;
	float speed;

public:
	SpaceShip(IDS whom);
	void draw_space_ship();
	float get_position_x();
	float get_position_y();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	float get_y_bound();
	float get_x_bound();
	int get_score();
	void add_score(int s);
	int get_life();
	void reduce_life();


};

class Bullet: public splite{
private:
	int ID;
	bool live;
	float speed;
public:
	Bullet();
	void draw_bullet();
	void fire_bullet();
	bool bullet_live();
	void init_bullet(float x, float y);
	void update_bullet();
	float get_position_x();
	float get_position_y();
	void dead();
};

class Meteor : public splite {
private:
	float boundx;
	float boundy;
	float speed;
	int ID;
	bool live;
public:
	Meteor();
	void init_Meteor();
	void draw_meteor();
	void update_meteor();
	bool is_meteor_alive();
	float get_bound_x();
	float get_bound_y();
	float get_position_x();
	float get_position_y();
	void dead();
};

void collision_detection(Bullet *b, int num_of_b, Meteor *m, int num_of_m, SpaceShip *s);

#else
#endif