// --- Projet RType
// Unix Socket Serveur.
# include "stdafx.h"
# include "WSServeur.hh"


// --- Constructeur ---
WSServeur::WSServeur(int port) : _port(port)
{
	WSADATA WSADATA; // Variable initialisé par WSAStartup. 
	int error = WSAStartup(MAKEWORD(2, 0), &WSADATA);
	if (error)
	{
		std::cerr << "Erreur avec WSAStartup." << std::endl;
		std::cerr << "!Fermeture du programme.!" << std::endl;
		exit(1);
 	}

	this->_idSocket = socket(AF_INET, SOCK_STREAM/*TCP*/, 0); // 0 indique que l'on utilisera par défaut associé à SOCK_STREAM soit TCP.
	if (this->_idSocket == INVALID_SOCKET)
	{
		std::cerr << "Erreur sur la creation de la socket." << std::endl;
		std::cerr << "!Fermeture du programme.!" << std::endl;
		WSACleanup();
		exit(1);
	}
	this->_Info.sin_addr.s_addr = INADDR_ANY;
	this->_Info.sin_family = AF_INET; // Renseigne la structure sockaddr_in avec les informations locales du serveur.
	this->_Info.sin_port = htons(this->_port);
	this->_Running = false;
}

WSServeur::WSServeur(const WSServeur &tmp)
{
	this->_Info = tmp._Info;
	this->_idSocket = tmp._idSocket;
	this->_port = tmp._port;
	this->_Running = tmp._Running;
	this->_listClients = tmp._listClients;
}

WSServeur::~WSServeur()
{
	this->removeAllListClient();
	this->closeSocket();
}

WSServeur			&WSServeur::operator=(const WSServeur &tmp)
{
	if (this != &tmp)
	{
		this->_Info = tmp._Info;
		this->_idSocket = tmp._idSocket;
		this->_port = tmp._port;
		this->_Running = tmp._Running;
		this->_listClients = tmp._listClients;
	}
	return (*this);
}

// --- Méthode Socket.

void				WSServeur::connection()
{
	int iResult;

	if (this->_Running == false)
	{
		iResult = bind(this->_idSocket, (SOCKADDR *)&this->_Info, sizeof(this->_Info));
		if (iResult == SOCKET_ERROR)
		{
			std::cerr << "Erreur bind socket :" << WSAGetLastError() << "." << std::endl;
			this->closeSocket();
			std::cerr << "!Fermeture du programme.!" << std::endl;
			exit(1);
		}

		std::cout << "Socket attachee avec succes !" << std::endl;

		if (listen(this->_idSocket, 0) == SOCKET_ERROR)
		{
			std::cerr << "Erreur list socket : " << WSAGetLastError() << "." << std::endl;
			this->closeSocket();
			std::cerr << "!Fermeture du programme.!" << std::endl;
			exit(1);
		}

		std::cout << "Socket placee en ecoute passive ..." << std::endl;
		this->_Running = true;
	}
}

int				WSServeur::acceptServeur()
{
	SOCKADDR_IN		_InfoClient;
	SOCKET			_idConnect;
	int				in_size = sizeof(_InfoClient);
	int				iRes = 0;

	if (this->_Running == true)
	{
		_idConnect = accept(this->_idSocket, (SOCKADDR *)&_InfoClient, &in_size);
		if (_idConnect == INVALID_SOCKET)
		{
			std::cerr << "Erreur sur l'acceptation du client : " << WSAGetLastError() << "." << std::endl;
		}
		else
		{
			iRes = this->addClient(_idConnect, _InfoClient);
			std::cout << "[Accept Client]" << _InfoClient.sin_port << "." << std::endl;
		}
	}
	return (iRes - 1);
}

int					WSServeur::closeSocket()
{
	if (this->_Running == true)
	{
		if (closesocket(this->_idSocket) == SOCKET_ERROR)
		{
			std::cerr << "Erreur de la fermeture de votre socket." << std::endl;
			return (-1);
		}

		this->_Running = false;
		WSACleanup();
	}
	return (0);
}

void				*WSServeur::ThreadacceptServeur()
{
	if (this->_Running == true)
	{
		std::cout << "Demarrage du Thread Accept Client." << std::endl;
		while ((this->_Running) == true)
		{
			this->acceptServeur();
		}
		std::cout << "Quit du thread Accept Client." << std::endl;
	}
	return NULL;
}

void				*winThreadacceptServeur(WSServeur *server)
{
	server->acceptServeur();
	return NULL;
}

// --- Communication ---
void				WSServeur::NBsendto(int id, std::string msg)
{
	if (this->_Running == true)
	{
		if ((int)this->_listClients.size() > id)
		{
			if (this->_listClients[id]->getRunning() == true)
				this->_listClients[id]->NBsend(msg);
			else
				this->removelistClient(id);
		}
	}
}

void				WSServeur::Bsendto(int id, std::string msg)
{
	if (this->_Running == true)
	{
		if ((int)this->_listClients.size() > id)
		{
			if (this->_listClients[id]->getRunning() == true)
				this->_listClients[id]->Bsend(msg);
			else
				this->removelistClient(id);
		}
	}
}

std::string			WSServeur::NBrecv(int id)
{
	std::string msg;
	if (this->_Running == true)
	{
		if ((int)this->_listClients.size() > id)
		{
			if (this->_listClients[id]->getRunning() == true)
				msg = this->_listClients[id]->NBrecv();
			else
				this->removelistClient(id);
		}
	}
	return (msg);
}

std::string			WSServeur::Brecv(int id)
{
	std::string msg;
	if (this->_Running == true)
	{
		if ((int)this->_listClients.size() > id)
		{
			if (this->_listClients[id]->getRunning() == true)
				msg = this->_listClients[id]->Brecv();
			else
				this->removelistClient(id);
		}
	}
	return (msg);
}

// --- Gestion de la liste ---
int					WSServeur::removelistClient(int id)
{
	
	if ((int)this->_listClients.size() > id)
	{
		this->_listClients[id]->close();
		this->_listClients.erase(this->_listClients.begin() + id);
		return (0);
	}
	return (-1);
}

int					WSServeur::removelistClient(std::string name)
{

	std::vector<WClient *>::iterator it;
	for (it = this->_listClients.begin(); it != this->_listClients.end(); it++)
	{
		if ((*it)->getName() == name)
		{
			(*it)->close();
			this->_listClients.erase(it);
			return (0);
		}
	}
	return (-1);
}

void				WSServeur::removeAllListClient()
{
	std::vector<WClient *>::iterator it;
	for (it = this->_listClients.begin(); it != this->_listClients.end(); it++)
	{
		(*it)->close();
	}
	this->_listClients.clear();
}

int					WSServeur::addClient(SOCKET id, SOCKADDR_IN info)
{
	this->_listClients.push_back(new WClient(id, info));
	this->printListClient();
	return (this->_listClients.size());
}

void				WSServeur::printListClient() const
{
	if (this->_Running == true)
	{
		for (int i = 0; i < (int)this->_listClients.size(); i++)
		{
			std::cout << "Client [" << i << "] " << this->_listClients[i]->getName() << std::endl;
		}
	}
}

// --- Getteur ---
SOCKADDR_IN			WSServeur::getInfoServeur() const
{
	return (this->_Info);
}

SOCKET				WSServeur::getSocketServeur() const
{
	return (this->_idSocket);
}

int					WSServeur::getPort() const
{
	return (this->_port);
}

bool				WSServeur::getRunning() const
{
	return (this->_Running);
}

int					WSServeur::getNbClient() const
{
	return (this->_listClients.size());
}