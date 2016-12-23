#ifndef SERVER_HH_
#define SERVER_HH_

#pragma once

#include	"Socket\Mutex.hh"
#include	"Socket\Thread.hh"


# ifdef WIN32
#include	"Socket\Windows\WMutex.hh"
#include	"Socket\Windows\WThread.hh"
#include	"Socket\Windows\Client\SClient.h"
#include	"Socket\Windows\Client\WSClient.h"
#include	"Socket\Windows\Serveur\SServeur.hh"
#include	"Socket\Windows\Serveur\WClient.hh"
#include	"Socket\Windows\Serveur\WSServeur.hh"

# else // WIN32
/*
#include	"Socket\Linux\UMutex.hh"
#include	"Socket\Linux\UThread.hh"
#include	"Socket\Linux\Client\inc\SClient.h"
#include	"Socket\Linux\Client\inc\USClient.h"
#include	"Socket\Linux\Client\inc\USClient.h"
#include	"Socket\Windows\Client\USClient.h"
#include	"Socket\Linux\Serveur\inc\SServeur.hh"
#include	"Socket\Linux\Serveur\inc\UClient.hh"
#include	"Socket\Linux\Serveur\inc\USServeur.hh"
*/
#endif // WIN32

#endif // !SERVER_HH_
