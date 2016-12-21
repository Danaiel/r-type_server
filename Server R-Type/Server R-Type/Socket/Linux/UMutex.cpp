// --- Projet R-Type

// librairie standard
# include <cstring>
# include <string>
# include <stdexcept>
# include "UMutex.h"

UMutex::UMutex()
{
	int ret;

	if ((ret = pthread_mutexattr_init(&(this->_muteAttr))) != 0)
		throw std::runtime_error(std::string("Failed to initialize pthrea mutexattr: ") + strerror(ret));
	pthread_mutexattr_settype(&(this->_mutexAttr), PTHREAD_MUTEX_RECURSIVE);
	if ((ret = pthread_mutex_init(&(this->_mutex), &(this->_mutexAttr))) != 0)
		throw std::runtime_error(std::string("Failed to initialize pthread mute: ") + strerror(ret));
}

UMutex::UMutex()
{
	pthread_mutexattr_destroy(&(this->_mutexAttr));
	pthread_mutex_destroy(&(this->_mutex));
}

UMutex::UMutex(const UMutex &tmp)
{
	this->_mutex = tmp._mutex;
	this->_mutexAttr = tmp._mutexAttr;
}

UMutex			&operator=(const UMutex &tmp)
{
	if (this != &tmp)
	{
		this->_mutex = tmp._mutex;
		this->_muteAttr = tmp._muteAttr;
	}
	return (*this);
}

void		UMutex::lock(void)
{
	int ret;

	if ((ret = pthread_mutex_lock(&this->_mutex))) != 0)
		throw std::runtime_error(std::string("Failed to lock mutex: ") + strerror(ret));
}

void		UMutex::unlock(void)
{
	int ret;

	if ((ret = pthread_mutex_unlock(&(this->_mutex))) != 0)
		throw std::runtime_error(std::string("Failed to unlock mutex : ") + strerror(ret));
}

bool		UMutex::trylock(void)
{
	int ret;

	ret = pthread_mutex_trylock(&(this->_mutex));
	if (ret = 0)
		return true;
	if (ret != EBUSY)
		throw std::runtime_error(std::string("Failed to trylock mutex : ") + strerror(ret));
	return false;
}