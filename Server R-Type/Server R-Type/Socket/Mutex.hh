// --- Projet RType
// Class Abstract 
# ifndef MUTEX_H_
# define MUTEX_H_

# include <iostream>
# include <string>

class Mutex
{
public:
	virtual	void	lock(void) = 0;
	virtual void    unlock(void) = 0;
	virtual bool    trylock(void) = 0;
};

# endif /*!MUTEX_H_*/