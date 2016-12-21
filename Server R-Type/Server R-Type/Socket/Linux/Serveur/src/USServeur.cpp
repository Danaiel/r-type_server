// --- Projet RType
// Unix Socket Serveur.
# include "USServeur.hh"

// --- Constructeur ---
USServeur::USServeur(int port) : _port(port)
{
	struct protoent	*pe;

	pe = getprotobyname("TCP");
	if (!pe)
	{
		std::cerr << "\e[0;31mErreur sur le protocole.\e[0m" << std::endl;
		exit(1);
	}

	this->_idSocket = socket(AF_INET, SOCK_STREAM/*TCP*/, pe->p_proto);
	if (this->_idSocket == -1)
	{
		std::cerr << "\e[0;31mErreur sur la creation de la socket.\e[0m" << std::endl;
		exit(1);
	}
	bzero(&this->_Info, sizeof(this->_Info));
	this->_Info.sin_addr.s_addr = INADDR_ANY;
	this->_Info.sin_family = AF_INET; // Renseigne la structure sockaddr_in avec les informations locales du serveur.
	this->_Info.sin_port = htons(this->_port);
	this->_Running = false;
}

USServeur::USServeur(const USServeur &tmp)
{
	this->_Info = tmp._Info;
	this->_idSocket = tmp._idSocket;
	this->_port = tmp._port;
	this->_Running = tmp._Running;
	this->_listClients = tmp._listClients;
}

USServeur::~USServeur(void)
{
	this->removeAllListClient();
	this->closeSocket();
}

USServeur                 &USServeur::operator=(const USServeur &tmp)
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

void			USServeur::connection()
{
	int iResult;

	if (this->_Running == false)
	{
		iResult = bind(this->_idSocket, (const struct sockaddr *)&this->_Info, sizeof(this->_Info));
		if (iResult == -1)
		{
			perror("");
			std::cerr << "\e[0;31mErreur sur la connection du client.\e[0m" << std::endl;
			this->closeSocket();
			std::cerr << "!Fermeture du programme.!" << std::endl;
			exit(1);
		}

		std::cout << "Socket attache avec succes !" << std::endl;

		if (listen(this->_idSocket, 40) == -1)
		{
			std::cerr << "\e[0;31mErreur sur la creation de listen.\e[0m" << std::endl;
			this->closeSocket();
			std::cerr << "!Fermeture du programme. !" << std::endl;
			exit(1);
		}

		std::cout << "Socket placee en ecoute passive ..." << std::endl;
		this->_Running = true;
	}
}

int				USServeur::acceptServeur()
{
	struct sockaddr_in	_InfoClient;
	int				_idConnect;
	socklen_t		in_size = sizeof(_InfoClient);
	int				iRes = 0;

	if (this->_Running == true)
	{
		_idConnect = accept(this->_idSocket, (struct sockaddr *)&_InfoClient, &in_size);
		if (_idConnect == -1)
		{
			std::cerr << "\e[0;31mErreur sur l'acceptation du client.\e[0m" << std::endl;
		}
		else
		{
			iRes = this->addClient(_idConnect, _InfoClient);
			std::cout << "[Accept Client]" << _InfoClient.sin_port << "." << std::endl;
		}
	}
	return (iRes - 1);
}

int			USServeur::closeSocket()
{
	if (this->_Running == true)
	{
		if (close(this->_idSocket) == -1)
		{
			std::cerr << "\e[0;31mErreur de la fermeture de votre socket.\e[0m" << std::endl;
			return (-1);
		}
		this->_Running = false;
	}
	return (0);
}

void			*USServeur::ThreadacceptServeur()
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

void				*uniThreadAcceptServeur(USServeur *arg)
{
	USServeur *serveur = (USServeur *)arg;
	serveur->ThreadacceptServeur();
	return NULL;
}

// --- Communication ---
void			USServeur::NBsendto(int id, std::string msg)
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

void			USServeur::Bsendto(int id, std::string msg)
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

std::string		USServeur::NBrecv(int id)
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

std::string		USServeur::Brecv(int id)
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

// --- Gestion de la liste ---
int				USServeur::removelistClient(int id)
{
	if ((int)this->_listClients.size() > id)
	{
		this->_listClients[id]->close();
		this->_listClients.erase(this->_listClients.begin() + id);
		return (0);
	}
	return (-1);
}

int				USServeur::removelistClient(std::string name)
{
	std::vector<UClient *>::iterator it;
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

void			USServeur::removeAllListClient()
{
	std::vector<UClient *>::iterator it;
	for (it = this->_listClients.begin(); it != this->_listClients.end(); it++)
	{
		(*it)->close();
	}
	this->_listClients.clear();
}

int				USServeur::addClient(int id, struct sockaddr_in info)
{
	this->_listClients.push_back(new UClient(id, info));
	this->printListClient();
	return (this->_listClients.size());
}

void					USServeur::printListClient() const
{
	if (this->_Running == true)
	{
		for (int i = 0; i < (int)this->_listClients.size(); i++)
		{
			std::cout << "Client [" << i << "] :" << this->_listClients[i]->getName() << std::endl;
		}
	}
}

// --- Getteur ---
struct sockaddr_in	USServeur::getInfoServeur() const
{
	return (this->_Info);
}

int			USServeur::getSocketServeur() const
{
	return (this->_idSocket);
}

int			USServeur::getPort() const
{
	return (this->_port);
}

bool		USServeur::getRunning() const
{
	return (this->_Running);
}

int			USServeur::getNbClient() const
{
	return (this->_listClients.size());
}
