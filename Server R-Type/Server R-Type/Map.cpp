#include "stdafx.h"
#include "Map.hh"

Map::Map()
{
}

Map::~Map()
{
}

void	Map::new_map(std::list<Case> *_m)
{
	this->map = _m;
}

void	Map::new_map(std::string f)
{
	std::ifstream ifs;
	char	buff[256];
	int		x = 0, y = 0;

	this->map = new std::list<Case>;

	ifs.open(f.c_str(), std::ifstream::in);
	if (ifs.is_open())
	{
		while (ifs.getline(buff, 256))
			for (int i = 0; i < 256; i++)
			{
				if (buff[i] == '\n')
				{
					x++;
					y = 0;
				}
				else
					this->map->push_back(Case::Case(buff[i] - '0', x, y));
			}
		ifs.close();
	}
}

std::list<Case>	*Map::get_map() const
{
	return (this->map);
}
