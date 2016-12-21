// --- Projet RType
// Windows Thread
# include "stdafx.h"
# include "WThread.h"

WThread::WThread(void) : _threadArg(nullptr), _threadReturnValue(nullptr), _hthread(nullptr), _status(false)
{
}

WThread::WThread(const WThread &tmp) : _threadArg(tmp._threadArg), _threadReturnValue(tmp._threadReturnValue), _hthread(tmp._hthread), _status(tmp._status)
{
}

WThread::~WThread()
{
	if (this->_status == true)
		this->ThreadStop();
}

WThread			&WThread::operator=(const WThread &tmp)
{
	if (this != &tmp)
	{
		this->_hthread = tmp._hthread;
		this->_threadArg = tmp._threadArg;
		this->_threadReturnValue = tmp._threadReturnValue;
		this->_status = tmp._status;
	}
	return (*this);
}

bool			WThread::getStatus() const
{
	return (this->_status);
}

void		WThread::ThreadStart(std::function<void *(void *)> routine, void *arg)
{
	if (this->_status == false)
	{
		this->_threadRoutine = routine;
		this->_threadArg = arg;

		this->_hthread = CreateThread(NULL, 0, &winThreadTrampolineRoutine, this, 0, NULL);
		if (this->_hthread == NULL)
		{
			std::cerr << "\e[0;31mErreur de la creation du Thread.\e[0m" << std::endl;
			this->_threadRoutine = nullptr;
			this->_threadArg = nullptr;
			this->_status = false;
		}
		else
		{
			std::cout << "\e[0;32mThread Crée. \e[0m" << std::endl;
			this->_status = true;
		}
	}
}

void		WThread::ThreadWait(void **returnValue)
{
	if (this->_status)
	{
		DWORD  ret = WaitForSingleObject(this->_hthread, INFINITE);

		if (ret != WAIT_FAILED)
		{
			if (returnValue != nullptr)
				*returnValue = this->_threadReturnValue;
			this->cleanUp();
		}
	}
}

void		WThread::ThreadStop()
{
	if (this->_status)
	{
		if (TerminateThread(this->_hthread, EXIT_SUCCESS))
			this->cleanUp();
	}
}

DWORD WINAPI	WThread::internalRoutine(void)
{
	this->_threadReturnValue = this->_threadRoutine(_threadArg);
	return EXIT_SUCCESS;
}

void			WThread::cleanUp(void)
{
	CloseHandle(this->_hthread); 
	this->_hthread = nullptr;
	this->_threadArg = nullptr;
	this->_threadReturnValue = nullptr;
	this->_status = false;
}

DWORD WINAPI		winThreadTrampolineRoutine(LPVOID arg)
{
	return reinterpret_cast<WThread *>(arg)->internalRoutine();
}