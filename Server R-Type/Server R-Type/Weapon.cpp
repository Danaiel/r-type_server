#include "stdafx.h"
#include "Weapon.hh"

Weapon::Weapon()
{
	this->rof = 5;
	this->type = Weapon::SIMPLE;
}

Weapon::Weapon(int _rof, int _type)
{
	this->rof = _rof;
	this->type = _type;
}

Weapon::~Weapon()
{
}

int		Weapon::getType() const
{
	return (this->type);
}

int		Weapon::getROF() const
{
	return (this->rof);
}

void	Weapon::setType(int _type)
{
	this->type = _type;
}

void	Weapon::setROF(int _rof)
{
	this->rof = _rof;
}