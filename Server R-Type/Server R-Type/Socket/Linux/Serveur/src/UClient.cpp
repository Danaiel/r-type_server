// --- Projet RType
// Representation d'un Client
# include "UClient.hh"

// --- Constructeur ---
UClient::UClient(int id, struct sockaddr_in info) : _idConnect(id), _Info(info), _Running(true)
{
	std::ostringstream ss;

	ss << "C" << info.sin_port;
	this->_name += ss.str();
	std::cout << "Client Reference Stocker : " << this->_name << std::endl;
}

UClient::UClient(const UClient &tmp)
{
	this->_idConnect = tmp._idConnect;
	this->_Info = tmp._Info;
	this->_name = tmp._name;
	this->_Running = tmp._Running;
}

UClient			&UClient::operator=(const UClient &tmp)
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

UClient::~UClient(void)
{
	this->close();
}

// --- Communication ---

std::string			UClient::Brecv(void)
{
	char			*cmsg;
	std::string		res = "";
	int error = 0;

	cmsg = new char[RECV_TAILLE];
	error = recv(this->_idConnect, cmsg, RECV_TAILLE, MSG_DONTWAIT);
	if (error > 0)
	{
		res = std::string(cmsg);
		delete cmsg;
		std::cout << "\e[0;35m>> " << res << "\e[0m" << std::endl;
	}
	else
		std::cerr << "Erreur recv" << std::endl;
	return (res);
}

std::string			UClient::NBrecv(void)
{
	char			*cmsg;
	std::string		res = "";
	int error = 0;

	cmsg = new char[RECV_TAILLE];
	error = recv(this->_idConnect, cmsg, RECV_TAILLE, MSG_DONTWAIT);
	if (error > 0)
	{
		res = std::string(cmsg);
		delete cmsg;
		std::cout << "\e[0;35m>> " << res << "\e[0m" << std::endl;
	}
	else
		std::cerr << "Erreur recv" << std::endl;
	return (res);
}

void				UClient::Bsend(const std::string msg)
{
	char			*cmsg = (char *)msg.c_str();

	write(this->_idConnect, cmsg, strlen(cmsg));
	std::cout << "\e[0;93m<< " << msg << "\e[0m" << std::endl;
}

void				UClient::NBsend(const std::string msg)
{
	char			*cmsg = (char *)msg.c_str();

	write(this->_idConnect, cmsg, strlen(cmsg));
	std::cout << "\e[0;93m<< " << msg << "\e[0m" << std::endl;
}

// --- Fermeture ---

void				UClient::close(void)
{
	this->NBsend("CLOSE");
	this->_Running = false;
}

// --- Getteur ---
int				UClient::getIdConnect()
{
	return (this->_idConnect);
}

struct sockaddr_in			UClient::getInfo()
{
	return (this->_Info);
}

std::string					UClient::getName()
{
	return (this->_name);
}

bool						UClient::getRunning()
{
	return (this->_Running);
}
