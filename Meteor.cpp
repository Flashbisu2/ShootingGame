#include "Header.h"

Meteor::Meteor() {
	this->ID = ENEMY;
	boundx = 70;
	boundy = 70;
	speed = 6;
	live = false;
	x = 0;
	y = 0;
}

void Meteor::init_Meteor()
{
	live = true;
	//srand(time(NULL));
	x = rand() % 390 + 5;
	y = 5;
}
void Meteor::draw_meteor() {
	if (live) {
		al_draw_circle(x, y, 35, al_map_rgb(200, 200, 100), 2);
		al_draw_filled_circle(x, y, 33, al_map_rgb(100, 200, 100));
		y += speed;
	}
}
void Meteor::update_meteor() {
	if (y > height)
		live = false;
}

bool Meteor::is_meteor_alive()
{
	return live;
}

float Meteor::get_bound_x()
{
	return boundx;
}

float Meteor::get_bound_y()
{
	return boundy;
}

float Meteor::get_position_x()
{
	return x;
}

float Meteor::get_position_y()
{
	return y;
}

void Meteor::dead()
{
	live = false;
}
