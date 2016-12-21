// --- Projet RType
// Unix Thread
# ifndef UTHREAD_H_
# define UTHREAD_H_

// libriaire thread.
# include <pthread.h>
# include <cstdlib>

// Class Abstarct 
# include "Thread.h"

class    UThread : public Thread
{
public:
	UThread(void);
	UThread(const UThread &tmp);
	virtual ~UThread(void);

	virtual bool		getStatus() const ;

	virtual void		ThreadStart(std::function<void *(void*)>, void *arg);
	virtual void		ThreadWait(void **returnValue);
	virtual void		ThreadStop();

	UThread		&operator=(const UThread &tmp);

	void		*internalRoutine(void);
private:

	std::is_function<void *(void *)> _threadRoutine;
	void			*_threadArg;
	pthread_t		_hthread;
	int				_status;
};

void		*unixThreadTrampolineRoutine(void *arg);
# endif /*!UTHREAD_H_*/