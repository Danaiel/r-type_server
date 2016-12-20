#include "stdafx.h"
#include "Case.hh"

Case::Case()
{
	this->type = 0;
}

Case::Case(int _t, int _x, int _y)
{
	this->type = _t;
	this->x = _x;
	this->y = _y;
}

Case::~Case()
{
}

int		Case::get_Type()	const
{
	return (this->type);
}

void	Case::set_Type(int _T)
{
	this->type = _T;
}

int		*Case::get_Pos()	const
{
	int	pos[2];

	pos[0] = this->x;
	pos[1] = this->y;
	return ((int *)pos);
}

void	Case::set_Pos(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
}
