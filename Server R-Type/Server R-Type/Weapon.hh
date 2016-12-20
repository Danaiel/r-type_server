#ifndef WEAPON_HH_

#pragma once

class Weapon
{
public:
	Weapon();
	Weapon(int, int);
	~Weapon();

	enum
	{
		SIMPLE,
		DOUBLE,
		TRIPLE,
		QUADRUPLE,
		FIVEFOLD
	};

	int		getType() const;
	int		getROF() const;
	void	setType(int);
	void	setROF(int);

private:
	int	rof;
	int	type;
};

#endif // !WEAPON_HH_
