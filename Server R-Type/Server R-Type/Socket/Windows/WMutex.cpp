#include "..\..\stdafx.h"
#include "WMutex.hh"

WMutex::WMutex()
{
	InitializeCriticalSection(&(this->_mutex));
}

WMutex::~WMutex()
{
	DeleteCriticalSection(&(this->_mutex));
}

WMutex::WMutex(const WMutex &tmp)
{
	this->_mutex = tmp._mutex;
}

WMutex			&WMutex::operator=(const WMutex &tmp)
{
	if (this != &tmp)
	{
		this->_mutex = tmp._mutex;
	}
	return (*this);
}

void			WMutex::lock(void)
{
	EnterCriticalSection(&(this->_mutex));
}

void			WMutex::unlock(void)
{
	LeaveCriticalSection(&(this->_mutex));
}

bool			WMutex::trylock(void)
{
	if (TryEnterCriticalSection(&(this->_mutex)))
		return true;
	return false;
}