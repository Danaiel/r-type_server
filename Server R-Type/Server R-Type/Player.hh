#ifndef Player_HH_

#include "Weapon.hh"

#pragma once

class Player
{
public:
	Player();
	~Player();

	int		getLife() const;
	Weapon	getWeapon() const;
	float	*getPos() const;
	float	getSpeed() const;

	void	setLife(int);
	void	setWeapon(Weapon);
	void	setPos(float, float);
	void	setSpeed(float);

private:
	float	x, y, speed;
	Weapon	weapon;
	int		life;
};

#endif // !Player_HH_

