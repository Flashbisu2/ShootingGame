#include "Header.h"

Bullet::Bullet()
{
	this->speed = 7.5;
	this->ID = BULLET;
	this->live = false;
}

void Bullet::draw_bullet()
{
	al_draw_filled_circle(x,y,2,al_map_rgb(0,255,255));
	y -= speed;
}

void Bullet::fire_bullet()
{
	live = true;
}

bool Bullet::bullet_live()
{
	return live;
}

void Bullet::init_bullet(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Bullet::update_bullet()
{
	if (y <= 0)
		live = false;
}

float Bullet::get_position_x()
{
	return x;
}

float Bullet::get_position_y()
{
	return y;
}

void Bullet::dead()
{
	live = false;
}
