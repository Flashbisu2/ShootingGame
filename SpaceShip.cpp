#include "Header.h"

SpaceShip::SpaceShip(IDS whom)
{
	this->x = width/2;
	this->y = height -40;
	lives = 3;
	speed = 3.7;
	ID = whom;
	boundx = 15;
	boundy = -35;
	score = 0;
}

void SpaceShip::draw_space_ship()
{
	al_draw_filled_rectangle(x + 9, y - 30, x + 12, y, al_map_rgb(255, 0, 255));
	al_draw_filled_rectangle(x - 9, y - 30, x - 12, y, al_map_rgb(255, 0, 255));
	al_draw_filled_triangle(x - 15, y, x, y - 35, x + 15, y, al_map_rgb(255, 255, 255));
}

void SpaceShip::move_down() {
	if(y <= height)
	this->y += this->speed;
}
void SpaceShip::move_up() {
	if(y + boundy>= 0)
	this->y -= this->speed;
}
void SpaceShip::move_right() {
	if (x + boundx + 5 <= width)
	this->x += this->speed;
}
void SpaceShip::move_left() {
	if(x - boundx - 5>= 0)
	this->x -= this->speed;
}
float SpaceShip::get_position_x() {
	return this->x;
}
float SpaceShip::get_position_y() {
	return this->y;
}
float SpaceShip::get_y_bound() {
	return boundy;
}

float SpaceShip::get_x_bound()
{
	return boundx;
}

int SpaceShip::get_score()
{
	return score;
}

void SpaceShip::add_score(int s)
{
	score += s;
}

int SpaceShip::get_life()
{
	return lives;
}

void SpaceShip::reduce_life()
{
	lives--;
}



