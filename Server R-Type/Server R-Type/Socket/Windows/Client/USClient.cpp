// Unix Socket Client.
# include "USClient.h"

USClient::USClient(int port, std::string ip) : _ip(ip), _port(port)
{
	struct protoent	*pe;

	this->_running = false;
	pe = getprotobyname("TCP");
	if (!pe)
	{
		std::cerr << "\e[0;31mErreur sur le protocole. Nous ne pouvons pas continuer l'excution.\e[0m" << std::endl;
		exit(1);
	}

	this->_idSocket = socket(AF_INET, SOCK_STREAM/*TCP*/, pe->p_proto);
	if (this->_idSocket == -1)
	{
		std::cerr << "\e[0;31mErreur sur la creation de la socket. Nous ne pouvons pas continuer l'excution.\e[0m" << std::endl;
		exit(1);
	}
	bzero(&this->_info, sizeof(this->_info));
	this->_info.sin_family = AF_INET;
	this->_info.sin_port = htons(this->_port);
}

USClient::USClient(const USClient &tmp)
{
	this->_info = tmp._info;
	this->_idSocket = tmp._idSocket;
	this->_ip = tmp._ip;
	this->_port = tmp._port;
	this->_ServerPort = tmp._ServerPort;
	this->_running = tmp._running;
}

USClient                 &USClient::operator=(const USClient &tmp)
{
	if (this != &tmp)
	{
		this->_info = tmp._info;
		this->_idSocket = tmp._idSocket;
		this->_ip = tmp._ip;
		this->_port = tmp._port;
		this->_ServerPort = tmp._ServerPort;
		this->_running = tmp._running;
	}
	return (*this);
}

USClient::~USClient(void)
{
	this->closeSocket();
}

int						USClient::getIdSocket() const
{
	return (this->_idSocket);
}

struct sockaddr_in		USClient::getInfo() const
{
	return (this->_info);
}

std::string				USClient::getIp() const
{
	return (this->_ip);
}

bool					USClient::getRunning() const
{
	return (this->_running);
}

int						USClient::getPort() const
{
	return (this->_port);
}

int						USClient::getServerPort() const
{
	return (this->_ServerPort);
}

void					USClient::setIdSocket(int id)
{
	this->_idSocket = id;
}

void					USClient::connection()
{
	this->_info.sin_addr.s_addr = inet_addr(this->_ip.c_str());
	if (connect(this->_idSocket, (const struct sockaddr*)& this->_info, sizeof(this->_info)) == -1)
	{
		perror("");
		std::cerr << "\e[0;31mErreur sur la connection du serveur.\e[0m" << std::endl;
		this->closeSocket();
		exit(1);
	}
	this->_running = true;
	std::cout << "\e[93mConnection au Serveur: " << this->_ip << ":" << this->_port << ".\e[0m" << std::endl;
}

int						USClient::closeSocket()
{
	this->NBsend("CLOSE");
	if (close(this->_idSocket) == -1)
	{
		std::cerr << "\e[0;31mErreur de la fermeture de votre socket.\e[0m" << std::endl;
		return (-1);
	}
	this->_running = false;
	return (0);
}

/*recevoir non bloquant.*/
std::string					USClient::NBrecv(void)
{
	char			*cmsg;
	std::string		res = "";

	cmsg = new char[RECV_TAILLE];
	if (recv(this->_idSocket, cmsg, RECV_TAILLE, MSG_DONTWAIT) > 0)
		{
			res = std::string(cmsg);
			delete cmsg;
		}
	std::cout << "\e[0;35m>> " << res << "\e[0m" << std::endl;

	if (res == "CLOSE")
		this->closeSocket();
	return (res);
}

/*envoyer non bloquant.*/
void						USClient::NBsend(const std::string msg)
{
	char			*cmsg = (char *)msg.c_str();

	std::cout << "\e[0;93m<< " << msg << "\e[0m" << std::endl;
}

/*recevoir bloquant.*/
std::string					USClient::Brecv(void)
{
	char			*cmsg;
	std::string		res = "";
	
	cmsg = new char[RECV_TAILLE];
	if (recv(this->_idSocket, cmsg, RECV_TAILLE, 0) > 0)
	{
		res = std::string(cmsg);
		delete cmsg;
	}
	std::cout << "\e[0;35m>> " << res << "\e[0m" << std::endl;
	if (res == "CLOSE")
		this->closeSocket();
	return (res);
}

/*envoyer bloquant.*/
void						USClient::Bsend(const std::string msg)
{
	char			*cmsg = (char *)msg.c_str();

	write(this->_idSocket, cmsg, strlen(cmsg));
	std::cout << "\e[0;93m<< " << msg << "\e[0m" << std::endl;
}

