#ifndef MAP_H_

#pragma once
#include <list>
#include <string>
#include <iostream>
#include <istream>
#include <fstream>

#include "Case.hh"

class Map
{
public:
	Map();
	~Map();

	void			new_map(std::list<Case>*);
	void			new_map(std::string);
	std::list<Case>	*get_map() const;

private:
	std::list<Case>	*map;

};

#endif // !MAP_H_
