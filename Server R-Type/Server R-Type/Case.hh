#ifndef CASE_HH_

#pragma once

enum
{
	VIDE,
	START,
	END,
	MUR
};

class Case
{
public:
	Case();
	Case(int, int, int);
	~Case();

	int		get_Type() const;
	void	set_Type(int);
	int		*get_Pos() const;
	void	set_Pos(int, int);

private:
	int		type;
	int		x;
	int		y;
};

#endif // !CASE_HH_
