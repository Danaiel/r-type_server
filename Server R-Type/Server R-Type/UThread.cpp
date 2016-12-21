// --- Projet RType.
// Unix Thread.
# include "UThread.h"

UThread::UThread(void) : _threadArg(nullptr), _status(false)
{
}

UThread::UThread(const UThread &tmp) : _threadRoutine(tmp._threadRoutine), _threadArg(tmp._threadArg), _hthread(tmp._hthread), _status(tmp._status)
{
}

UThread::~UThread(void)
{
	if (this->_status)
		this->ThreadStop();
}

UThread	&UThread::operator=(const UThread &tmp)
{
	if (this != &tmp)
	{
		this->_threadRoutine = tmp._threadRoutine;
		this->_threadArg = tmp._threadArg;
		this->_status = tmp._status;
		this->_hthread = tmp._hthread;
	}
	return (*this);
}

bool	UThread::getStatus() const
{
	return (this->_status);
}

void	UThread::ThreadStart(std::function<void *(void *)> routine, void *arg)
{
	if (this->_status == false)
	{
		this->_threadRoutine = routine;
		this->_threadArg = arg;
		if (pthread_create(&(this->_hthread), nullptr, &unixThreadTrampolineRoutine, this) != 0)
		{
			this->_threadRoutine = nullptr;
			this->_threadArg = nullptr;
			this->_status = false;
		}
		this->_status = true;
	}
}

void	UThread::ThreadWait(void **returnValue)
{
	if (this->_status)
	{
		if (pthread_join(this->_thread, returnValue) == 0)
		{
			this->_threadRoutine = nullptr;
			this->_threadArg = nullptr;
			this->_status = false;
		}
	}
}

void	UThread::ThreadStop()
{
	if (this->_status)
	{
		pthread_cancel(this->_thread);
		this->_status = false;
	}
}

void		UThread::internalRoutine(void)
{
	return _threadRoutine(this->_threadArg);
}

void		*unixThreadTrampolineRoutine(void *arg)
{
	return reinterpret_cast<UThread *>(arg)->internalRoutine();
}