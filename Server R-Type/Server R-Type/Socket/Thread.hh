// --- Projet RType
# ifndef THREAD_H_
# define THREAD_H_

// librairie standard.
# include <windows.h>
# include <iostream>
# include <string>
# include <functional>


class Thread
{
public:
	virtual bool			getStatus() const = 0;
	virtual void			ThreadStart(std::function<void *(void *)> routine, void *) = 0;
	virtual void			ThreadWait(void **returnValue) = 0;
	virtual void			ThreadStop() = 0;
};

#endif /*!THREAD_H_*/
