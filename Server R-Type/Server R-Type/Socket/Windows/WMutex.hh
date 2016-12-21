# ifndef WMUTEX_H_
# define WMUTEX_H_

# include <Windows.h>
# include "Mutex.h"

class WMutex : public Mutex
{
public:
	WMutex();
	~WMutex();
	WMutex(const WMutex &tmp);

	virtual void		lock(void);
	virtual void		unlock(void);
	virtual bool		trylock(void);

	WMutex			&operator=(const WMutex &tmp);
private:
	CRITICAL_SECTION		_mutex;
};
# endif /*!WMUTEX_H_*/