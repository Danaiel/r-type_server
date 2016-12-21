// --- Projet RType
// Representation d'un Client.
# include "stdafx.h"
# include "WClient.hh"


// --- Constructeur ---
WClient::WClient(SOCKET id, SOCKADDR_IN info) : _idConnect(id), _Info(info), _Running(true)
{
	std::ostringstream ss;

	ss << "C" << info.sin_port;
	this->_name += ss.str();
	std::cout << "Client Reference Stocker : " << this->_name << std::endl;
}

WClient::WClient(const WClient &tmp)
{
	this->_idConnect = tmp._idConnect;
	this->_Info = tmp._Info;
	this->_name = tmp._name;
	this->_Running = tmp._Running;
}

WClient			&WClient::operator=(const WClient &tmp)
{
	if (this != &tmp)
	{
		this->_idConnect = tmp._idConnect;
		this->_Info = tmp._Info;
		this->_name = tmp._name;
		this->_Running = tmp._Running;
	}
	return (*this);
}

WClient::~WClient()
{
	this->close();
}

// --- Communication ---
std::string		WClient::Brecv(void)
{
	char		*cmsg;
	std::string	 res = "";
	int			 error;

	cmsg = new char[RECV_TAILLE];
	error = recv(this->_idConnect, cmsg, RECV_TAILLE, 0);
	if (error > 0)
	{
		std::cout << "Nombre de bytes recu: " << error << "." << std::endl;
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
		this->_Running = false;
	}
	return (res);
}

std::string		WClient::NBrecv(void)
{
	char		*cmsg;
	std::string	 res = "";
	int			 error;

	std::cout << "passe !!" << std::endl;
	cmsg = new char[RECV_TAILLE];
	error = recv(this->_idConnect, cmsg, RECV_TAILLE, 0);
	if (error > 0)
	{
		std::cout << "Nombre de bytes recu: " << error << "." << std::endl;
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
		this->_Running = false;
	}
	return (res);
}

void			WClient::Bsend(const std::string msg)
{
	char		*cmsg = (char *)msg.c_str();
	int			iResult = send(this->_idConnect, cmsg, strlen(cmsg), 0);

	if (iResult == SOCKET_ERROR)
	{
		std::cerr << "Erreur de envoie du message." << std::endl;
		this->_Running = false;
	}
	std::cout << "<< " << msg << "" << std::endl;
}

void			WClient::NBsend(const std::string msg)
{
	char		*cmsg = (char *)msg.c_str();
	int			iResult = send(this->_idConnect, cmsg, strlen(cmsg), 0);

	if (iResult == SOCKET_ERROR)
	{
		std::cerr << "Erreur de envoie du message." << std::endl;
		this->_Running = false;
	}
	std::cout << "<< " << msg << "" << std::endl;
}

// --- Fermeture ---
void			WClient::close(void)
{
	this->NBsend("CLOSE");
	this->_Running = false;
}

// --- Getteur ---
SOCKET			WClient::getIdConnect()
{
	return (this->_idConnect);
}

SOCKADDR_IN		WClient::getInfo()
{
	return (this->_Info);
}

std::string		WClient::getName()
{
	return (this->_name);
}

bool			WClient::getRunning()
{
	return (this->_Running);
}
