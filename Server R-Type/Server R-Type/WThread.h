// --- Projet RType
// Windows Thread
# ifndef WTHREAD_H_
# define WTHREAD_H_

// libriaire thread.
# include <Windows.h>

// Class Abstarct 
# include "Thread.h"

class    WThread : public Thread
{
public:
	WThread(void);
	WThread(const WThread &tmp);
	~WThread(void);

	virtual bool		getStatus() const;
	virtual void		ThreadStart(std::function<void *(void *)> routine , void *);
	virtual void		ThreadWait(void **returnValue);
	virtual void		ThreadStop();

	WThread		&operator=(const WThread &tmp);

	DWORD	WINAPI	internalRoutine(void);

private:

	void		cleanUp(void);

	std::function<void *(void *)>   _threadRoutine;
	void		*_threadArg;
	void		*_threadReturnValue;
	HANDLE		_hthread;
	bool		_status;
};

DWORD WINAPI	winThreadTrampolineRoutine(LPVOID arg);

# endif /*!WTHREAD_H_*/