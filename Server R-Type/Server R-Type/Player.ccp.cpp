#include "stdafx.h"
#include "Player.hh"

Player::Player()
{
	this->life = 3;
	this->x = 0;
	this->y = 0;
	this->weapon = Weapon::Weapon();
}

Player::~Player()
{
}

int		Player::getLife() const
{
	return (this->life);
}

Weapon	Player::getWeapon() const
{
	return (this->weapon);
}

float	*Player::getPos() const
{
	float pos[2];

	pos[0] = this->x;
	pos[1] = this->y;
	return ((float*)pos);
}

void	Player::setLife(int _l)
{
	this->life = _l;
}

void	Player::setWeapon(Weapon _w)
{
	this->weapon = _w;
}

void	Player::setPos(float _x, float _y)
{
	this->x = _x;
	this->y = _y;
}

float	Player::getSpeed() const
{
	return (this->speed);
}

void	Player::setSpeed(float _s)
{
	this->speed = _s;
}