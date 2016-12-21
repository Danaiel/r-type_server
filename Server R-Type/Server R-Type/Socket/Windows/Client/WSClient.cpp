// Windows Socket Client.
//# include "stdafx.h"
# include "WSClient.h"

WSClient::WSClient(int port, std::string ip) : _ip(ip), _port(port)
{
	WSADATA	WSAData;
	int		error;

	error = WSAStartup(MAKEWORD(2, 0), &WSAData);
	if (error)
		exit(1);
	this->_idSocket = socket(AF_INET, SOCK_STREAM/*TCP*/, IPPROTO_TCP);
	if (this->_idSocket == INVALID_SOCKET)
	{
		std::cerr << "Erreur sur la creation de la socket." << std::endl;
		exit(1);
	}
	this->_info.sin_family = AF_INET;
	this->_info.sin_port = htons(this->_port);
	this->_running = false;
}

WSClient::WSClient(const WSClient &tmp)
{
	this->_info = tmp._info;
	this->_idSocket = tmp._idSocket;
	this->_ip = tmp._ip;
	this->_port = tmp._port;
	this->_ServerPort = tmp._ServerPort;
	this->_running = tmp._running;
}


WSClient 			&WSClient::operator=(const WSClient &tmp)
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

WSClient::~WSClient(void)
{
	this->closeSocket();
}

SOCKET				WSClient::getIdSocket() const
{
	return (this->_idSocket);
}

SOCKADDR_IN			WSClient::getInfo() const
{
	return (this->_info);
}

std::string			WSClient::getIp() const
{
	return (this->_ip);
}
bool				WSClient::getRunning() const
{
	return (this->_running);
}

int					WSClient::getPort() const
{
	return (this->_port);
}
int					WSClient::getServerPort() const
{
	return (this->_ServerPort);
}

void				WSClient::setIdSocket(SOCKET id)
{
	this->_idSocket = id;
}

void				WSClient::connection()
{
	//this->_info.sin_addr.s_addr = inet_addr (this->_ip.c_str());
	inet_pton(AF_INET, this->_ip.c_str(), &this->_info.sin_addr);
	if (connect(this->_idSocket, (SOCKADDR *)& this->_info, sizeof(this->_info)) == SOCKET_ERROR)
	{
		std::cerr << "Erreur sur la connection du serveur." << std::endl;
		this->closeSocket();
		exit(1);
	}
	this->_running = true;
	std::cout << "Connection au Serveur: " << this->_ip << ":" << this->_port << "." << std::endl;
}

int					WSClient::closeSocket()
{
	this->NBsend("CLOSE");
	if (closesocket(this->_idSocket) == SOCKET_ERROR)
	{
		std::cerr << "Erreur de la fermeture de votre socket." << std::endl;
		return (-1);
	}
	this->_running = false;
	WSACleanup();
	return (0);
}

/*recevoir non bloquant.*/
std::string			WSClient::NBrecv(void)
{
	char		*cmsg;
	std::string		res = "";
	int			error;

	cmsg = new char[RECV_TAILLE];

	error = recv(this->_idSocket, cmsg, RECV_TAILLE, 0);
	if (error > 0)
	{
		std::cout << "Bytes received: " << error << "." << std::endl;
		res = std::string(cmsg);
		res.substr(0, error);
		std::cout << ">> " << res << std::endl;
	}
	else if (error == 0)
		std::cerr << "Connection closed." << std::endl;
	else
		std::cerr << "Recv failed with error: " << WSAGetLastError() << "." << std::endl;
	delete cmsg;

	if (res == "CLOSE")
	{
		this->closeSocket();
	}
	return (res);
}


/*recevoir bloquant.*/
std::string			WSClient::Brecv(void)
{
	char		*cmsg;
	std::string		res = "";
	int			error;

	cmsg = new char[RECV_TAILLE];

	error = recv(this->_idSocket, cmsg, RECV_TAILLE, 0);
	if (error > 0)
	{
		std::cout << "Bytes received: " << error << "." << std::endl;
		res = std::string(cmsg);
		res = res.substr(0, error);
		std::cout << ">> " << res << std::endl;
		
	}
	else if (error == 0)
		std::cerr << "Connection closed." << std::endl;
	else
		std::cerr << "Recv failed with error: " << WSAGetLastError() << "." << std::endl;
	delete cmsg;

	if (res == "CLOSE")
	{
		this->closeSocket();
	}
	return (res);
}


/*envoyer non bloquant.*/
void			WSClient::NBsend(const std::string msg)
{
	char *cmsg = (char *)msg.c_str();
	int res;

	res = send(this->_idSocket, cmsg, strlen(cmsg), 0);
	if (res == SOCKET_ERROR)
	{
		std::cerr << "Erreur de envoie du message." << std::endl;
		this->closeSocket();
		exit(1);
	}
	std::cout << "<< " << msg << std::endl;
}

/*envoyer bloquant.*/
void			WSClient::Bsend(const std::string msg)
{
	char		*cmsg = (char *)msg.c_str();
	int			res;
	res = send(this->_idSocket, cmsg, strlen(cmsg), 0);

	if (res == SOCKET_ERROR)
	{
		std::cerr << "Erreur de envoie du message." << std::endl;
		this->closeSocket();
		exit(1);
	}
	std::cout << "<< " << msg << std::endl;
}
