# ifndef  UMUTEX_H_
# define  UMUTEX_H_

# include <pthread.h>
# include <cstring>
# include <string>
# include <stdexcept>

# include "Mutex.h"

class UMutex : public Mutex
{
public:
	UMutex();
	UMutex(const UMutex &tmp);

	virtual void		lock(void);
	virtual void		unlock(void);
	virtual bool		trylock(void);

	UMutex				&operator=(const UMutex &tmp);
private:
	pthread_mutex_t     _mutex;
	pthread_mutexattr_t _mutexAttr;
};

# endif /*!UMUTEX_H_*/